#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>
//#include "readMat.c"

//Print matrix operations and solution
#define SANITY 0

//System Specs
#define NODELETS 8
#define MATDIM 16384 //512, 1024, 2048, 4096, 8192, 16384

//Constants for random generated matrix
#define SPARSITY 0.9
#define RANDRANGE 10

struct timeval tval_before, tval_after, tval_result;

//Replicate vector across each nodelet
replicated long *repx;

//Set values in vector to be multiplied
void fill_x(void *ptr, long node){
	long *gto = (long *)ptr;

	for(int i = 0; i < MATDIM; i++)
		gto[i] = (i%RANDRANGE)+1;
}

//Allocate memory for vector
long *alloc_x(void){
	long *mr = mw_mallocrepl(MATDIM * sizeof(long));
	mw_replicated_init_generic(mr, fill_x);

	return mr;
}

long **Generate(long *nodeId, long threads);
void csrCompress(long *nodeId, long **emuRows, long **data, long **index, long **pointer, long threads);
long* csrSpMV(long *nodeId, long threads, long *loc_data, long *loc_ind, long *loc_ptr);

int main(int argc, char** argv){
	long threads = 0;
	if(argc != 2){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		threads = NODELETS * atoi(argv[1]);
	}
	unsigned long long starttime, endtime, comptime, soltime;
	long *tempX = alloc_x();
	mw_replicated_init((long *)&repx, (long)tempX);
	
	long *nodes = mw_malloc1dlong(threads * sizeof(long *));
	for(int i = 0; i < threads; i++)
		nodes[i] = i;
	#if SANITY	
		for(int i = 0; i < threads; i++){
			MIGRATE(&nodes[i]);
			printf("Node %ld: [", nodes[i]);
			for(int j = 0; j < MATDIM; j++){
				printf("%3ld", repx[j]);
			}
			printf("End Node: %ld}\n", NODE_ID());
		}
	#endif
	
	
	long **splitData[threads];
	//Matrix Generation
	//starttiming();
	for(int i = 0; i < threads; i++){
		splitData[i] = cilk_spawn Generate(&nodes[i], threads);
	}
	cilk_sync;

	//Matrix Compression
	starttiming();
	starttime = CLOCK();
	long *data[threads];
	long *index[threads];
	long *pointer[threads];
	
	for(int i = 0; i < threads; i++){
		cilk_spawn csrCompress(&nodes[i], splitData[i], &data[i], &index[i], &pointer[i], threads);
	}
	cilk_sync;
	endtime = CLOCK();
	comptime = endtime - starttime;
	
	long *solution[threads];
	//SpMV
	starttime = CLOCK();
	for(int i = 0; i < threads; i++){
		solution[i] =  cilk_spawn csrSpMV(&nodes[i], threads, data[i], index[i], pointer[i]);
	}
	cilk_sync;
	endtime = CLOCK();
	soltime = endtime - starttime;

	//Sanity Check
	#if SANITY
		int nodeRows = MATDIM / threads;
		int cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < threads; i++){
			if(i == threads-1)
				nodeRows += MATDIM % threads;
			for(int j = 0; j < nodeRows; j++){
				printf("|");
				for(int k = 0; k < MATDIM; k++){
					printf("%3ld", splitData[i][j][k]);
					if(splitData[i][j][k] != 0)
						cnt++;
				}
				printf("|\n");
			}
		}
		printf("DENSITY: %d%%\n", (int)(100.0 * (double)cnt/(MATDIM*MATDIM)));
		printf("Solution: \n");
		for(int i = 0; i < threads; i++)
			for(int j = 0; j < nodeRows; j++)
				printf("|%8ld|\n", solution[i][j]);
		printf("\n");
	#endif
	printf("Matrix Size: %d\nThreads per Core: %d\n", MATDIM, threads);
	printf("Compression Cycles: %ld\n", comptime);
	printf("Solution Cycles: %ld\n\n", soltime);
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
long **Generate(long *nodeId, long threads){
	//Migrate thread to the relevent nodelet
	MIGRATE(&nodeId);
	
	//Define the number of rows each thread is responsible for
	int rowSplit = MATDIM / threads;
	double rowPer, colPer, matRow, randNum;

	//Allocate space for the matrix
	long **emuRows = malloc(rowSplit * sizeof(long *));
	for(int j = 0; j < rowSplit; j++){
		emuRows[j] = malloc(MATDIM * sizeof(long));
	}
		
	
	//Define values for the matrix
	for(int i = 0; i < rowSplit; i++){
		matRow = i + (*nodeId * rowSplit);
		rowPer = (double)(matRow) / (double)MATDIM;
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)MATDIM;
			randNum = rand() % RANDRANGE;
			if(randNum/RANDRANGE >= SPARSITY)
				emuRows[i][j] = rand() % RANDRANGE;
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
void csrCompress(long *nodeId, long **emuRows, long **data, long **index, long **pointer, long threads){
	//Migrate the thread to the relevent nodelet
	MIGRATE(nodeId);
	//Define the number of rows that will be distrubuted for each thread
	int rowSplit = MATDIM / threads;
	long cnt = 0;

	//Run through the matrix section and count the number of non-zero values present
	for(int i = 0; i < rowSplit; i++){
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){
				cnt++;
			}
		}
	}
	
	//Allolcate space for the compressed data
	long* loc_data = malloc(cnt * sizeof(long));
	long* loc_ind = malloc(cnt * sizeof(long));
	long* loc_ptr = malloc((rowSplit+1) * sizeof(long));
	loc_ptr[0] = 0;

	cnt = 0;
	//Compress the matrix into CSR format
	for(int i = 0; i < rowSplit; i++){
		for(int j = 0; j < MATDIM; j++){
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
long* csrSpMV(long *nodeId, long threads, long *loc_data, long *loc_ind, long *loc_ptr){
	//Define the number of rows that each thread will be responsible for handling
	int rowSplit = MATDIM / threads;

	//Define an array for the solution of the SpMV
	long *loc_sol = malloc(rowSplit * sizeof(long));

	//Loop through the row pointer array
	for(int i = 0; i < rowSplit; i++){
		//Initialize current solution column to 0
		loc_sol[i] = 0;
		//Loop through relevent non-zero values and perform SpMV
		for(int j = loc_ptr[i]; j < loc_ptr[i+1]; j++){
			loc_sol[i] += loc_data[j] * repx[loc_ind[j]];
		}
	}
	return(loc_sol);
}
