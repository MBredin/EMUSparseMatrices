#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

//Print matrix operations and solution
#define SANITY 0

//System Specs
#define CORES 8

//Constants for random generated matrix
#define RANDRANGE 10

struct timeval tval_before, tval_after, tval_result;

void Generate(double *splitData, int threads, long *rParams);
void Compress(int id, double *stamat, double *data, int *index, long pointer, int threads, long *rParams);
void Solution(int id, double *data, int *ind, int *ptr, double *x, double *sol, int threads, long rowDim);
double** readMat(char *fileName);
double** coo2Csr(int *dims, int *rowInd, int *colInd, double *values);
unsigned long long* csrPresetTest(long threads, char fileName[50]);
unsigned long long* csrRandomTest(long threads, long *rParams);

static __inline__ unsigned long long rdtsc(void){
	unsigned hi, lo;
	__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

unsigned long long* csrRandomTest(long threads, long *rParams){
	unsigned long long starttime, endtime, comCyc, solCyc;
	unsigned long long *timesOut = malloc(2 * sizeof(unsigned long long));
	//Child Tracking
	pid_t pid;
	//Thread Array
	long *coreId = malloc(CORES * sizeof(long));
	for(int i = 0; i < CORES; i++)
		coreId[i] = i;
	//Initialize the vector to be multiplied
        double *x = malloc(rParams[0] * sizeof(double));
        for(int i = 0; i < rParams[0]; i++)
                x[i] = (i%RANDRANGE)+1;

	//Set up a shared memory matrix
	//3rd dimension defines the row chunk
	double *splitData;
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	splitData =  mmap(NULL, rParams[0]*rParams[0]*sizeof(double), protection, visibility, 0, 0);
	//Matrix Generation
	Generate(splitData, threads, rParams);
	//printf("Program is continuing to the compression algorithm\n");

	//Matrix Compression
	gettimeofday(&tval_before, NULL);
	starttime = rdtsc();

	int cnt = 0;
	int rowSplit = rParams[0] / (CORES * threads);
	double *data;
	int *index;
	int *pointer;
	pointer =  mmap(NULL, (rParams[0]+1)*sizeof(int), protection, visibility, 0, 0);
	pointer[0] = 0;
	
	cnt = 0;
	for(int i = 0; i < rParams[0]; i++){
		for(int j = 0; j < rParams[0]; j++){
			if(splitData[i * rParams[1] + j] != 0){
				cnt++;
			}
		}
		pointer[i+1] = cnt;
	}

	data =  mmap(NULL, pointer[rParams[0]]*sizeof(double), protection, visibility, 0, 0);
	index =  mmap(NULL, pointer[rParams[0]]*sizeof(int), protection, visibility, 0, 0);

	for(int i = 0; i < CORES; i++){
		pid = fork();
		if(pid != 0){
			//Parent is idle
		}
		//Process is child, execute the function
		else{
			//printf("Child Spawned: %d PID: %d\n", i, getpid());
			for(int j = 0; j < threads; j++)
				cilk_spawn Compress(i * threads + j, splitData, data, index, pointer[(i * threads + j) * rowSplit], threads, rParams);
			exit(0);
		}
	}
	for(int i = 0; i < CORES; i++)
		wait(NULL);
	//printf("Program is continuing to the solution algorithm\n");

	endtime = rdtsc();
	comCyc = endtime - starttime;
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
        long compTime = (long int)tval_result.tv_usec;

	//Solution
	gettimeofday(&tval_before, NULL);
	starttime = rdtsc();
	double *solution = mmap(NULL, rParams[0]*sizeof(double), protection, visibility, 0, 0);
	
	for(int i = 0; i < CORES; i++){
		pid = fork();
		if(pid != 0){
			//Parent is idle
		}
		//Process is child, execute the function
		else{
			//printf("Child Spawned: %d PID: %d\n", i, getpid());
			for(int j = 0; j < threads; j++)
				Solution(i * threads + j, data, index, pointer, x, solution, threads, rParams[0]);
			exit(0);
		}
	}
	for(int i = 0; i < CORES; i++)
		wait(NULL);
	//printf("Program is continuing to the solution algorithm\n");

	//printf("Solution has completed\n");
	endtime = rdtsc();
	solCyc = endtime - starttime;
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
        long execTime = (long int)tval_result.tv_usec;

	timesOut[0] = comCyc;
	timesOut[1] = solCyc;

	return(timesOut);
}

void Generate(double *splitData, int threads, long *rParams){
	double randNum;
	for(int i = 0; i < rParams[0]; i++){
		for(int j = 0; j < rParams[0]; j++){
			randNum = rand() % RANDRANGE;
			if(randNum/RANDRANGE >= (double)rParams[1]/100.0)
				splitData[i * rParams[0] + j] = rand() % RANDRANGE;
			else
				splitData[i * rParams[0] + j] = 0;
		}
	}
	return;
}

void Compress(int id, double *stamat, double *data, int *index, long pointer, int threads, long *rParams){
	int rowSplit = rParams[0] / (CORES * threads);
	int rowStart = rowSplit * id;
	int rowEnd = rowStart + rowSplit;
	double rowPer, colPer, matRow, randNum;
	long cnt = 0;
	for(int i = rowStart; i < rowEnd; i++){
		for(int j = 0; j < rParams[0]; j++){
			if(stamat[i * rParams[0] + j] != 0){
				data[pointer] = stamat[i * rParams[0] + j];
				index[pointer] = j;
				pointer++;
			}
		}
	}
}

void Solution(int id, double *data, int *ind, int *ptr, double *x, double *sol, int threads, long rowDim){
	int splits = CORES * threads;
	int rowSplit = rowDim / splits;
	int rowStart = rowSplit * id;
	if(rowSplit % splits > id){
		rowStart += id;
		rowSplit++;
	}
	else{
		rowStart += rowSplit % splits;
	}
	if(id != 0)
		rowStart--;
	int rowEnd = rowStart + rowSplit;
	int sanity = 0;
	//printf("Start: %d Stop: %d\n", rowStart, rowEnd);
	for(int i = rowStart; i < rowEnd; i++){
		sol[i] = 0;
		//printf("Range --> start: %d --- end: %d\n", ptr[i], ptr[i+1]);
		for(int j = ptr[i]; j < ptr[i+1]; j++){
			sol[i] += data[j] * x[ind[j]];
			sanity++;
			//printf("row %d: Solution: %lf\n", i, sol[i]);
		}
	}
	//printf("ID: %d --> Item Count: %d\n", id, sanity);
	return;
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
	//Define output for cycles and times
	unsigned long long *timesOut = malloc(2 * sizeof(unsigned long long));
	unsigned long long starttime, endtime, comCyc, solCyc;
	//Create double pointer for return arrays
	double **coo_set = malloc(4 * sizeof(double *));
	
	//Invoke funcion
	coo_set = readMat(fileName);

	//Unpack data
	int *dims = malloc(3 * sizeof(int));
	for(int i = 0; i < 3; i++)
		dims[i] = (int)coo_set[0][i];
	printf("Sizes: %d %d %d\n", dims[0], dims[1], dims[2]);
	int *colInd = malloc(dims[2] * sizeof(int));
	int *rowInd = malloc(dims[2] * sizeof(int));
	double *values = malloc(dims[2] * sizeof(double));
	for(int i = 0; i < dims[2]; i++){
		colInd[i] = coo_set[1][i];
		rowInd[i] = coo_set[2][i];
		values[i] = coo_set[3][i];
	}

	//Check if threads excede number of rows and correct
	if(threads * CORES > dims[0]){
		printf("Thread count too large, terminating program...\n");
		printf("   Threads: %ld Dim: %d", threads, dims[0]);
		exit(1);
		//threads = dims[0];
	}
	
	//Child Tracking
	pid_t pid;
	//Thread Array
	long *coreId = malloc(CORES * sizeof(long));
	for(int i = 0; i < CORES; i++)
		coreId[i] = i;
	//Initialize the vector to be multiplied
        double *x = malloc(dims[0] * sizeof(double));
        for(int i = 0; i < dims[0]; i++)
                x[i] = (i%RANDRANGE)+1;

	//Convert data to CSR format
	double **csr_set = malloc(3 * sizeof(double *));
	csr_set = coo2Csr(dims, rowInd, colInd, values);

	//Free COO dataset
	free(colInd);
	free(rowInd);
	free(values);

	//Set up a shared memory matrices
	//3rd dimension defines the row chunk
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	int *rowPtr;
	values =  mmap(NULL, (dims[2])*sizeof(double), protection, visibility, 0, 0);
	rowPtr =  mmap(NULL, (dims[0]+1)*sizeof(int), protection, visibility, 0, 0);
	rowInd =  mmap(NULL, (dims[2])*sizeof(int), protection, visibility, 0, 0);

	//Unpack CSR data	
	for(int i = 0; i < dims[0] + 1; i++){
		rowPtr[i] = (int)csr_set[0][i];
	}
	for(int i = 0; i < dims[2]; i++){
		rowInd[i] = (int)csr_set[1][i];
		values[i] = csr_set[2][i];
	}

//	for(int i = 0; i < dims[2]; i++){
//		printf("%9.8lf | %8d ", values[i], rowInd[i]);
//		if(i <= dims[0]){
//			printf("| %8d", rowPtr[i]);
//		}
//		printf("\n");
//	}

	//Solution
	gettimeofday(&tval_before, NULL);
	starttime = rdtsc();
	double *solution = mmap(NULL, dims[0]*sizeof(double), protection, visibility, 0, 0);
	
	for(int i = 0; i < CORES; i++){
		pid = fork();
		if(pid != 0){
			//Parent is idle
		}
		//Process is child, execute the function
		else{
			//printf("Child Spawned: %d PID: %d\n", i, getpid());
			for(int j = 0; j < threads; j++){
				Solution(i * threads + j, values, rowInd, rowPtr, x, solution, threads, dims[0]);
			}
			exit(0);
		}
	}
	for(int i = 0; i < CORES; i++)
		wait(NULL);
	//printf("Program is continuing to the solution algorithm\n");
	
//	for(int i = 0; i < dims[0]; i++)
//		printf("%lf\n", solution[i]);
	//printf("Solution has completed\n");
	endtime = rdtsc();
	solCyc = endtime - starttime;

	timesOut[0] = 0;
	timesOut[1] = solCyc;

	return(timesOut);
}

int main(int argc, char** argv){
	int threads, preset, matdim, sparsity;
	
	if(argc != 5){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		//Set number of threads
		threads = atoi(argv[1]);
		//set file name
		preset = atoi(argv[2]);
		//Set Mat. dimension
		matdim = atoi(argv[3]);
		//Set sparsity value (0 - 100)
		sparsity = atoi(argv[4]);
	}
	printf("Starting Program with %d\n", threads);
	printf("   Preset Matrix: %d\n", preset);
	printf("   Matrix Dimension (if not preset): %d\n", matdim);
	printf("   Matrix Sparsity (if no preset): %d%% \n\n", sparsity);

	//Define Parameters for generated matrix (0 - matrix dimension (square matrix), 1 - sparsity (0 - 100))
	long rParams[2] = {matdim, sparsity};
	unsigned long long *hold = malloc(2 * sizeof(unsigned long long));
	//Run Trials, sum totals for average
	char fileName[50] = "494_bus.mtx";
	if(preset == 1){
		hold = csrPresetTest(2, fileName);
		printf("(Preset Matrix): Solution Time: %llu\n\n", hold[1]);
	}
	else{
		hold = csrRandomTest(2, rParams);
		printf("(Generated Matrix): \n   Compression Average: %llu \n   Solution Average: %llu\n\n", hold[0], hold[1]);
	}
}
