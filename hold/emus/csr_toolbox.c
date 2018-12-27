#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>

//Print matrix operations and solution
#define SANITY 0

//System Specs
#define NODELETS 8
#define MATDIM 16 //512, 1024, 2048, 4096, 8192, 16384

//Constants for random generated matrix
#define SPARSITY 0.9
#define RANDRANGE 10

double **Generate(long *nodeId, long threads, long *rParams);
int csrCompress(long *nodeId, double **emuRows, double **data, int **index, int **pointer, long threads, long *rParams);
//long* csrSpMV(long *nodeId, long threads, long *loc_data, long *loc_ind, long *loc_ptr);
double* csrSpMV(long *nodeId, long threads, int rowSplit, double *loc_data, int *loc_ind, int *loc_ptr);
unsigned long long* csrRandomTest(long threads, long *dims);
unsigned long long* csrPresetTest(long threads, char *fileName);
double** readMat(char *fileName);
double** coo2Csr(int *dims, int *rowInd, int *colInd, double *values);
int csrSplit(long *nodeId, int *dims, int start, int stop, double *values, int *rowInd, int *rowPtr, double **loc_values, int **loc_rowInd, int **loc_rowPtr);

struct timeval tval_before, tval_after, tval_result;

//replicated repVect *repSpMV;
replicated long SpMVlen;
replicated double *repSpMV;

void fill_SpMV(void *ptr, long node){
	double *gto = (double *)ptr;

	//unsigned long len = (sizeof(gto) - sizeof(struct repVect)) / sizeof(double);
	for(int i = 0; i < SpMVlen; i++)
		gto[i] = (i%RANDRANGE)+1;
}

double *alloc_SpMV(int len){
	double *mr = mw_mallocrepl(SpMVlen * sizeof(double));
	mw_replicated_init_generic(mr, fill_SpMV);

	return mr;
}


/*
 * Function: timesOut = csrTest(threads)
 * Description: This function will generate a randomized matrix, compress the data into
 * 		CSR format, and run an SpMV on the compressed data. The compression and 
 * 		solution stages of the code are timed and will be returned
 * Input Argument:
 *	threads -> The number of threads the user would like to run on each nodelet
 * Output Argument:
 *	An array containg the cycles it took to complete the compression and solution
 */
unsigned long long* csrRandomTest(long threads, long *rParams){
	//Check if threads excede number of rows and correct
	if(threads > rParams[0]){
		printf("Thread count too large, terminating program...\n");
		exit(1);
		//threads = dims[0];
	}

	//Define output for cycles and times
	unsigned long long *timesOut = malloc(2 * sizeof(unsigned long long));
	unsigned long long starttime, endtime, comptime, soltime;

	//Define dimensions of the matrix for testing
	mw_replicated_init(&SpMVlen, rParams[0]);

	//Define some randomized vector to multiply a matrix by
	double *tempX = alloc_SpMV(rParams[0]);
	mw_replicated_init((long *)&repSpMV, (long)tempX);

	
	//run through each thread and assigned a nodelet ID to each
	long *nodes = mw_malloc1dlong(threads * sizeof(long *));
	for(int i = 0; i < threads; i++)
		nodes[i] = i;
	
	//Allocated space for matrix, split across the nodelets
	double **splitData[threads];

	//Matrix Generation
	for(int i = 0; i < threads; i++){
		splitData[i] = cilk_spawn Generate(&nodes[i], threads, rParams);
	}
	cilk_sync;

	//Matrix Compression
	starttiming();
	starttime = CLOCK();

	//Allocated space for compressed data
	double *data[threads];
	int *index[threads];
	int *pointer[threads];
	int ptrSize[threads];
	
	//Compress the matrix
	for(int i = 0; i < threads; i++){
		ptrSize[i] = cilk_spawn csrCompress(&nodes[i], splitData[i], &data[i], &index[i], &pointer[i], threads, rParams);
	}
	cilk_sync;

	//Grab the time compression took
	endtime = CLOCK();
	comptime = endtime - starttime;
	
	//Allocate space for the solution to an SpMV
	starttime = CLOCK();
	double *solution[threads];

	//Perform the SpMV

	for(int i = 0; i < threads; i++){
		solution[i] =  cilk_spawn csrSpMV(&nodes[i], ptrSize[i], threads, data[i], index[i], pointer[i]);
	}
	cilk_sync;

	//Grab how long it took to complete the SpMV
	endtime = CLOCK();
	soltime = endtime - starttime;

	timesOut[0] = comptime;
	timesOut[1] = soltime;
	return(timesOut);
}

/*
 * Function: matrix = Generate(nodeId, threads)
 * Description: This function will generate a randomized sparse matrix of and evenly 
 * 		distrubte the rows of said matrix across the given nodelets
 * Input Argument:
 * 	nodeId -> The ID for the nodelets that will be performing the operation
 *	threads -> The total number of threads that will spawned through the system
 * Output Argument:
 *	A 2-Dimensional array that contains the entirety of the generated matrix
 */
double **Generate(long *nodeId, long threads, long *rParams){
	//Migrate thread to the relevent nodelet
	MIGRATE(&nodeId);
	
	//Define the number of rows each thread is responsible for
	int rowSplit = rParams[0] / threads;
	double rowPer, colPer, matRow, randNum;

	//Allocate space for the matrix
	double **emuRows = malloc(rowSplit * sizeof(double *));
	for(int j = 0; j < rowSplit; j++){
		emuRows[j] = malloc(rParams[0] * sizeof(double));
	}
		
	
	//Define values for the matrix
	for(int i = 0; i < rowSplit; i++){
		matRow = i + (*nodeId * rowSplit);
		rowPer = (double)(matRow) / (double)rParams[0];
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)rParams[0];
			randNum = rand() % RANDRANGE;
			if(randNum/RANDRANGE >= (double)rParams[1]/100.0)
				emuRows[i][j] = (double) (rand() % RANDRANGE);
			else
				emuRows[i][j] = 0;
			
		}
	}
	return(emuRows);
}

/*
 * Function: csrComprss(nodeId, emuRows, data, index, pointer, threads)
 * Description: This function will compress an input matrix into CSR format. This function
 * operates under the assumption that the matrix data being compressed has already been split
 * amongst the relevent nodelets. 
 * Input Argument:
 * 	nodeId -> The ID for the nodelets that will be performing the operation
 *	threads -> The number of threads that will spawned on each given nodelet
 *	emuRows -> A two dimensional array that contains the original matrix. 
 * 		this matrix should already be split amongst the nodelets
 *	data -> An array of the given compressed non-zeros values allocated to the 
 *		relevent nodelet
 *	index -> An array of indexs relevent to the CSR compressed matrix allocated
 *		to the relevent nodelet 
 *	pointer -> An array containing the count for the row pointer values in
 *		the CSR compression method allocated to the relevent nodelet
 * Output Argument:
 *	An array that contains the results of the SpMV for CSR compressed data
 */
int csrCompress(long *nodeId, double **emuRows, double **data, int **index, int **pointer, long threads, long *rParams){
	//Migrate the thread to the relevent nodelet
	MIGRATE(nodeId);
	//Define the number of rows that will be distrubuted for each thread
	int rowSplit = rParams[0] / threads;
	long cnt = 0;

	//Run through the matrix section and count the number of non-zero values present
	for(int i = 0; i < rowSplit; i++){
		for(int j = 0; j < rParams[0]; j++){
			if(emuRows[i][j] != 0){
				cnt++;
			}
		}
	}
	
	//Allolcate space for the compressed data
	double* loc_data = malloc(cnt * sizeof(double));
	int* loc_ind = malloc(cnt * sizeof(int));
	int* loc_ptr = malloc((rowSplit+1) * sizeof(int));
	loc_ptr[0] = 0;

	cnt = 0;
	//Compress the matrix into CSR format
	for(int i = 0; i < rowSplit; i++){
		for(int j = 0; j < rParams[0]; j++){
			if(emuRows[i][j] != 0){
				loc_data[cnt] = emuRows[i][j];
				loc_ind[cnt] = j;	
				cnt++;
			}
		}
		loc_ptr[i+1] = cnt;
	}
	
	//Give the memory addressed of the localized compressed data back to the main function
	*data = loc_data;
	*index = loc_ind;
	*pointer = loc_ptr;
	return((int)rowSplit+1);
}

/*
 * Function result = csrSpMV(*nodeId, threads, data, index, pointer)
 * Desription: This function takes compressed data in the form of CSR
 * 		and will output a solution for a sprase matrix vector 
 * 		multiplcation. This fuction assumes that data has
 * 		been split amongst nodelets, and that a vector for 
 * 		multiplication has been replicated across the system.
 * Input Argument:
 * 	nodeId -> The ID for the nodelets that will be performing the operation
 *	threads -> The number of threads that will spawned on each given nodelet
 *	data -> An array of the given compressed non-zeros values allocated to the 
 *		relevent nodelet
 *	index -> An array of indexs relevent to the CSR compressed matrix allocated
 *		to the relevent nodelet 
 *	pointer -> An array containing the count for the row pointer values in
 *		the CSR compression method allocated to the relevent nodelet
 * Output Argument:
 *	An array that contains the results of the SpMV for CSR compressed data
 */
double* csrSpMV(long *nodeId, long threads, int rowSplit, double *loc_data, int *loc_ind, int *loc_ptr){
	MIGRATE(nodeId);
	//Define an array for the solution of the SpMV
	double *loc_sol = malloc((rowSplit-1) * sizeof(double));

	//Loop through the row pointer array
	for(int i = 0; i < rowSplit-1; i++){
		//Initialize current solution column to 0
		loc_sol[i] = 0;
		//Loop through relevent non-zero values and perform SpMV
		for(int j = loc_ptr[i]; j < loc_ptr[i+1]; j++){
			loc_sol[i] += loc_data[j] * repSpMV[loc_ind[j]];
		}
	}
	return(loc_sol);
}

/* Function readMat(fileName)
 * Description: This file will take a file name in the form of a string and read in the relevent matrix data.
 * 		All data read in will be in COO format and returned as such. Function is meant to read .mtx
		file extensions from the Florida State Sparse Matrix collection. 
 * Inputs:
 * 	fileName --> A string with the file name for the desired MTX file to be read. 
 * Outputs:
 * 	coo_set --> Matrix of pointers for relevent values
 * 		[0][0,1,2] --> Dimesions of matrix rows, dimension of column, number of non-zero values
 * 		[1][0 - n] --> column index array for COO compressed data
 * 		[2][0 - n] --> row index array for COO compressed data
 * 		[3][0 - n] --> values array for COO compressed data
 *
 */
double** readMat(char *fileName){
	//Relevent variables for reading files
	FILE *fMat;

	//Buffer varaibles for reading in files
	char *lineBuff =  NULL;
	size_t buffSize = 0;
	double *hold = malloc(3 * sizeof(double));

	//Define output arrays in COO format
	double *dims = malloc(3 * sizeof(double));
	double *colInd;
	double *rowInd;
	double *values;

	//Flags and counters
	int cooInd = 0;
	int dimFlag = 1;

	//Read file
	///char fileName[50] = "494_bux.mtx";
	fMat = fopen(fileName, "r");
	if(!fMat){
		printf("Failed to open file, terminating program...");
		exit(1);
	}

	//Loop through file until EOF is reached
	while(getline(&lineBuff, &buffSize, fMat) != EOF){
		//Check first character of linebuffer, throw out line if it is a description line
		if(lineBuff[0] == '%'){
			//lineBuff = malloc(buffSize * sizeof(char));
			//buffSize = 0;
		}
		//buffer contains relevent data
		else{
			sscanf(lineBuff, "%lf %lf %lf", &hold[0], &hold[1], &hold[2]);
			//If the first line of data is being read in, it contains 
			//matrix dimensions and non-zero count, read it in seperately
			if(dimFlag == 1){
				//Fill in matrix dimension and non-zero counts
				dimFlag = 0;
				for(int i = 0; i < 3; i++){
					dims[i] = (double)hold[i];
				}
				//Allocate memory for COO compressed data
				//printf("Non-Zeros: %lf\n", dims[2]);
				colInd = malloc((int)dims[2] * sizeof(double *));
				rowInd = malloc((int)dims[2] * sizeof(double *));
				values = malloc((int)dims[2] * sizeof(double *));
			}
			//Populate COO compressed data arrays with relevent values
			else{
				colInd[cooInd] = hold[0] - 1;
				rowInd[cooInd] = hold[1] - 1;
				values[cooInd] = hold[2];
				//printf("Test: %lf, %lf, %lf\n", hold[0], hold[1], hold[2]);
				//printf("Test: %lf, %lf, %lf\n", coo_comp[1][cooInd], coo_comp[2][cooInd], coo_comp[3][cooInd]);
				//printf("Iteration: %d, Buffer: %d\n", cooInd, buffSize);
				cooInd++;
			}
		}
	}
	fclose(fMat);

	//Define the return array with all relevent values
	double **coo_comp = malloc(4 * sizeof(double *));
	coo_comp[0] = dims;
	coo_comp[1] = colInd;
	coo_comp[2] = rowInd;
	coo_comp[3] = values;

	//Return compressed data
	return(coo_comp);
}


/* Function csrSplit(nodeId, dims, rowInd, colInd, values)
 * Description: This function will take data compressed in CSr format and evenly distribute the data 
 * 		amongst the avaible nodelets. The data is split according to the row pointer array.  
 * Inputs:
 * 	nodeId --> The id of the current nodelet
 * 	dims --> An array input that contains the dimensions of the matrix and the could of all non-zero values
 * 	rowInd --> An array input that contains the row indecies for all non-zeros values
 * 	colInd --> An array input that contains the column indecies for all non-zeros values
 * 	values --> An array input that contains the non-zero values present in the matrix
 * Outputs:
 * 	interval --> Returns size of the rowPtr chunk
 *
 */
int csrSplit(long *nodeId, int *dims, int start, int stop, double *values, int *rowInd, int *rowPtr, double **loc_values, int **loc_rowInd, int **loc_rowPtr){
	//Migrate the thread to the relevent nodelet
	MIGRATE(nodeId);

	//Define necessary variables for the row index
	int interval = stop - start + 1;
	int* hold_rowPtr = malloc(interval * sizeof(int));
	int cnt = 1;
	int prevEnd = rowPtr[start-1];
	hold_rowPtr[0] = 0;

	//Create the pointer array
	for(int i = start; i < stop; i++){
		hold_rowPtr[cnt] = rowPtr[i] - prevEnd;
		cnt++;
	}


	//Create arrays for local values and row Index
	MIGRATE(nodeId);
	double* hold_values = mw_localmalloc((rowPtr[stop-1] - rowPtr[start-1]) * sizeof(double), nodeId);
	int* hold_rowInd = mw_localmalloc((rowPtr[stop-1]-rowPtr[start-1]) * sizeof(int), nodeId);
	cnt = 0;

	//split up relevent data
	for(int i = rowPtr[start-1]; i < rowPtr[stop-1]; i++){
		hold_values[cnt] = values[i];
		hold_rowInd[cnt] = rowInd[i];
		cnt++;
	}

	//Copy Addresses for split data
	*loc_values = hold_values;
	*loc_rowInd = hold_rowInd;
	*loc_rowPtr = hold_rowPtr;
	return(interval);

}

/* Function coo2csr(dims, rowInd, colInd, values)
 * Description: This function will take input data compressed in COO format and return the data compressed
 * 		into CSR format.  
 * Inputs:
 * 	dims --> An array input that contains the dimensions of the matrix and the could of all non-zero values
 * 	rowInd --> An array input that contains the row indecies for all non-zeros values
 * 	colInd --> An array input that contains the column indecies for all non-zeros values
 * 	values --> An array input that contains the non-zero values present in the matrix
 * Outputs:
 * 	csr_set --> Matrix of pointers for relevent values
 * 		[0][0,1,2] --> Dimesions of matrix rows, dimension of column, number of non-zero values
 * 		[1][0 - n] --> column index array for CSR compressed data
 * 		[2][0 - n] --> row by row non-zero count array for CSR compressed data
 * 		[3][0 - n] --> values array for CSR compressed data
 *
 */
double** coo2Csr(int *dims, int *rowInd, int *colInd, double *values){
	//The row pointer array will have a size of 1 plus the 
	double *rowPointer = malloc((dims[0] + 1) * sizeof(double));
	for(int i = 0; i < dims[0]; i++){
		rowPointer[i] = 0;
	}

	//Loop through every non-zero value
	for(int i = 0; i < dims[2]; i++){
		//Grab the row index of the non-zero value and increment all values greater than that by 1
		for(int j = rowInd[i] + 1; j <= dims[0]; j++){
			rowPointer[j]++;
		}
	}

	//Allocate data for ordered values and index arrays
	double *ord_values = malloc(dims[2] * sizeof(double));
	double *ord_index = malloc(dims[2] * sizeof(double));
	int cnt = 0;

	//Sort array into CSR format
	for(int i = 0; i < dims[0] + 1; i++){
		for(int j = rowPointer[i]; j < rowPointer[i+1]; j++){
			for(int k = 0; k < dims[2]; k++){
				if(rowInd[k] == i){
					ord_index[cnt] = (double)rowInd[k];
					ord_values[cnt] = (double)values[k];
					cnt++;
					break;
				}
			}
		}
	}

	//Define the return array with all relevent values
	double **csr_comp = malloc(3 * sizeof(double *));
	csr_comp[0] = rowPointer;
	csr_comp[1] = ord_index;
	csr_comp[2] = ord_values;

	return(csr_comp);
}

/*
 * Function: timesOut = csrPresetTest(threads)
 * Description: This function will read in a predefined compressed matrix, convert
		it to CSR format and run an SpMV on the compressed data. The 
		compression and solution stages of the code are timed and will be returned
 * Input Argument:
 *	threads -> The number of threads the user would like to run on each nodelet
 * Output Argument:
 *	An array containg the cycles it took to complete the compression and solution
 */
unsigned long long* csrPresetTest(long threads, char fileName[50]){
	printf("Threads: %ld\n", threads);
	//Define output for cycles and times
	unsigned long long *timesOut = malloc(2 * sizeof(unsigned long long));
	unsigned long long starttime, endtime, splittime, soltime;
	//Create double pointer for return arrays
	double **coo_set = malloc(4 * sizeof(double *));
	
	//Invoke funcion
	coo_set = readMat(fileName);

	//Unpack data
	int *dims = malloc(3 * sizeof(int));
	for(int i = 0; i < 3; i++)
		dims[i] = (int)coo_set[0][i];
	int *colInd = malloc(dims[2] * sizeof(int));
	int *rowInd = malloc(dims[2] * sizeof(int));
	double *values = malloc(dims[2] * sizeof(double));
	for(int i = 0; i < dims[2]; i++){
		colInd[i] = coo_set[1][i];
		rowInd[i] = coo_set[2][i];
		values[i] = coo_set[3][i];
	}

	//Check if threads excede number of rows and correct
	if(threads > dims[0]){
		printf("Thread count too large, terminating program...\n");
		printf("   Threads: %d Dim: %lf", threads, dims[0]);
		exit(1);
		//threads = dims[0];
	}

	//run through each thread and assigned a nodelet ID to each
	long *nodes = mw_malloc1dlong(threads * sizeof(long *));
	for(int i = 0; i < threads; i++)
		nodes[i] = i;
	
	mw_replicated_init(&SpMVlen, dims[0]);

	//Define some randomized vector to multiply a matrix by
	double *tempX = alloc_SpMV(dims[0]);
	mw_replicated_init((long *)&repSpMV, (long)tempX);


	//Convert data to CSR format
	double **csr_set = malloc(3 * sizeof(double *));
	csr_set = coo2Csr(dims, rowInd, colInd, values);

	//Free COO dataset
	free(colInd);
	free(rowInd);
	free(values);

	//Unpack CSR data	
	rowInd = malloc(dims[2] * sizeof(int));
	int *rowPtr = malloc((dims[0]+1) * sizeof(int));
	values = malloc(dims[2] * sizeof(double));
	for(int i = 0; i < dims[0] + 1; i++){
		rowPtr[i] = (int)csr_set[0][i];
	}
	for(int i = 0; i < dims[2]; i++){
		rowInd[i] = (int)csr_set[1][i];
		values[i] = csr_set[2][i];
	}


	starttiming();
	starttime = CLOCK();
	//Split data up amongst nodelets
	int *ptrSize = malloc(threads * sizeof(int));
	double *loc_values[threads];
	int *loc_rowInd[threads];
	int *loc_rowPtr[threads];
//	printf("Rows: %ld Columns: %ld Non-Zeros: %ld\n",dims[0],dims[1],dims[2]);
//	printf("Floating rows: %ld\n", dims[0]%threads);
	int start = 1;
	int stop = 0;
	for(int i = 0; i < threads; i++){
		stop = start + ((dims[0])/threads) + ((dims[0]) % threads - i > 0);
		ptrSize[i] = cilk_spawn csrSplit(&nodes[i], dims, start, stop, values, rowInd, rowPtr, &loc_values[i], &loc_rowInd[i], &loc_rowPtr[i]);
		//printf("PtrSize: %ld\n", ptrSize[i]);
		//printf("loc_Ptr: %ld\n\n", loc_rowPtr[i][ptrSize[i]]);
		start = stop;
	}
	cilk_sync;

	//Grab the time compression took
	endtime = CLOCK();
	splittime = endtime - starttime;

	//for(int i = 0; i < dims[0]+1; i++)
	//	printf("%ld\n", rowPtr[i]);

//	for(int j = 0; j < threads; j++){
//		int range = loc_rowPtr[j][ptrSize[j]-1] - loc_rowPtr[j][0];
//		printf("Nodelet: %ld Range: %ld\n", j, range);
//		for(int i = 0; i < range; i++){
//			if(i < ptrSize[j])
//				printf("%15.9lf | %8ld | %8ld \n", loc_values[j][i], loc_rowInd[j][i], loc_rowPtr[j][i]);
//			else
//				printf("%15.9lf | %8ld |\n", loc_values[j][i], loc_rowInd[j][i]);
//		}
//	}



	starttime = CLOCK();
	double *solution[threads];
	for(int i = 0; i < threads; i++){
		printf("Spawned: %d", i);
		solution[i] =  cilk_spawn csrSpMV(&nodes[i], threads, ptrSize[i], loc_values[i], loc_rowInd[i], loc_rowPtr[i]);
	}
	cilk_sync;

	//Grab the time compression took
	endtime = CLOCK();
	soltime = endtime - starttime;

	
//	printf("Solution: \n");
//	int tempCnt = 0;
//	for(int i = 0; i < threads; i++){
//		printf("Nodelet: %ld\n",i);
//		for(int j = 0; j < (ptrSize[i]-1); j++){
//			printf("|%lf|\n", solution[i][j]);
//			tempCnt++;
//		}
//	}
//	printf("Final Size: %ld", tempCnt);

	timesOut[0] = splittime;
	timesOut[1] = soltime;

	return(timesOut);
}

int main(int argc, char** argv){
	long threads, preset, matdim, sparsity;
	
	if(argc != 5){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		//Set number of threads
		threads = NODELETS * (long)atoi(argv[1]);
		//set file name
		preset = (long)atoi(argv[2]);
		//Set Mat. dimension
		matdim = (long)atoi(argv[3]);
		//Set sparsity value (0 - 100)
		sparsity = (long)atoi(argv[4]);
	}
	printf("Starting Program with %d\n", threads/NODELETS);
	printf("   Preset Matrix: %d\n", preset);
	printf("   Matrix Dimension (if not preset): %d\n", matdim);
	printf("   Matrix Sparsity (if no preset): %d%% \n\n", sparsity);

	//Define Parameters for generated matrix (0 - matrix dimension (square matrix), 1 - sparsity (0 - 100))
	long rParams[2] = {matdim, sparsity};
/*
	double preSolAvg = 0;
	double preSplitAvg = 0;
	double genSolAvg = 0;
	double genCompAvg = 0;
*/
	unsigned long long *hold = malloc(2 * sizeof(unsigned long long));
/*	
	//Open an output file for the results
	FILE *fp;
	fp = fopen("Output.txt", "w");

	//Backup data values
	FILE *fpData;
	fpData = fopen("data.csv","w");
	fprintf(fpData, "preSplit, preSol, genComp, preComp\n");
*/
	//Run Trials, sum totals for average
	char fileName[50] = "circuit_2.mtx";
//	for(int i = 0; i < trials; i++){
	if(preset == 1){
		hold = csrPresetTest(threads, fileName);
		printf("(Preset Matrix): \n   Split Cycles: %ld \n   Solution Cycles: %ld\n\n", hold[0], hold[1]);
	}
	else{
		hold = csrRandomTest(threads, rParams);
		printf("(Generated Matrix): \n   Compression Cycles: %ld \n   Solution Cycles: %ld\n\n", hold[0], hold[1]);
	}
/*
	//Compute average
	genCompAvg = genCompAvg / (double)trials;
	genSolAvg = genSolAvg / (double)trials;
	preSplitAvg = preSplitAvg / (double)trials;
	preSolAvg = preSolAvg / (double)trials;
*/
//	printf("(Preset Matrix): \n   Compression Average: %lf \n   Solution Average: %lf\n\n", hold[0], hold[1]);
//	printf("(Generated Matrix): \n   Compression Average: %lf \n   Solution Average: %lf\n\n", hold[0], hold[1]);
//	fclose(fp);
//	fclose(fpData);


}
