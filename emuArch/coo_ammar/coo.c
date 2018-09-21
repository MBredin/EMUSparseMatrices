#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>
//#include "readMat.c"

//Print matrix operations and solution
#define SANITY 1

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//System Specs
#define NODELETS 8
//#define THREADSPERNODELET 16 //2, 4, 8, 16, 32, 64
//#define THREADS (NODELETS * THREADSPERNODELET) //16, 32, 64, 128, 256, 512
#define MATDIM 8 //512, 1024, 2048, 4096, 8192, 16384

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

long **Generate(long *nodeId);
void nodeletsComp(long *nodeId, long **emuRows, long ***valArr, long ***rowArr, long ***colArr, long ***nzArr, long threads);
long cooComp(long **emuRows, long **value, long **rowIndex, long **colIndex, int nodeSplit, long threads, int threadId);
long* csrSpMV(long *nodeId, long threads, long *loc_data, long *loc_ind, long *loc_ptr);

int main(int argc, char** argv){
	long threads = 0;
	if(argc != 2){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		threads = atoi(argv[1]);
	}
	unsigned long long starttime, endtime, comptime, soltime;
	long *tempX = alloc_x();
	mw_replicated_init((long *)&repx, (long)tempX);

	long *nodes = mw_malloc1dlong(threads * sizeof(long *));
	for(int i = 0; i < NODELETS; i++)
		nodes[i] = i;
	#if SANITY
		for(int i = 0; i < NODELETS; i++){
			MIGRATE(&nodes[i]);
			printf("Node %ld: [", nodes[i]);
			for(int j = 0; j < MATDIM; j++){
				printf("%3ld", repx[j]);
			}
			printf("End Node: %ld}\n", NODE_ID());
		}
	#endif


	long **splitData[NODELETS];
	//Matrix Generation
	//starttiming();
	for(int i = 0; i < NODELETS; i++){
		splitData[i] = cilk_spawn Generate(&nodes[i]);
	}
	cilk_sync;

	//Matrix Compression
	////starttiming();
	////starttime = CLOCK();
	long **value[NODELETS];
	long **rowInd[NODELETS];
	long **colInd[NODELETS];
	long **nzCount[NODELETS];

	for(int i = 0; i < NODELETS; i++){
		cilk_spawn nodeletsComp(&nodes[i], splitData[i], &value[i], &rowInd[i], &colInd[i], &nzCount[i], threads);
	}
	cilk_sync;
	////endtime = CLOCK();
	////comptime = endtime - starttime;


	long *solution[NODELETS];
	//SpMV
	starttime = CLOCK();
	for(int i = 0; i < NODELETS; i++){
		solution[i] =  cilk_spawn csrSpMV(&nodes[i], threads, &value[i], &colInd[i], &rowInd[i]);
	}
	cilk_sync;
	endtime = CLOCK();
	soltime = endtime - starttime;

	//Sanity Check
	#if SANITY
		int nodeSplit = MATDIM / NODELETS;
		int cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < NODELETS; i++){
			if(i == NODELETS-1)
				nodeSplit += MATDIM % threads;
			for(int j = 0; j < nodeSplit; j++){
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
/*
		printf("Value: [");
		for(int i = 0; i < NODELETS; i++)
			for(int j = 0; j < threads; j++)
				for(int k = 0; k < *nzCount[i][j]; k++)
					printf("%3ld", value[i][j][k]);
		printf("]\n");
*/
/*
		printf("Solution: \n");
		for(int i = 0; i < threads; i++)
			for(int j = 0; j < nodeRows; j++)
				printf("|%8ld|\n", solution[i][j]);
		printf("\n");
*/
	#endif
/*
	printf("Matrix Size: %d\nThreads per Core: %d\n", MATDIM, threads);
	printf("Compression Cycles: %ld\n", comptime);
	printf("Solution Cycles: %ld\n\n", soltime);
*/
}

long **Generate(long *nodeId){
	MIGRATE(&nodeId);

	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	int rowSplit = MATDIM / NODELETS;
	double rowPer, colPer, matRow, randNum;
	long **emuRows = malloc(rowSplit * sizeof(long *));

	//Allocate memory for given node
	for(int j = 0; j < rowSplit; j++){
		emuRows[j] = malloc(MATDIM * sizeof(long));
	}

	//int temp = *nodeId * rowSplit;
	for(int i = 0; i < rowSplit; i++){
		matRow = i + (*nodeId * rowSplit);
		rowPer = (double)(matRow) / (double)MATDIM;
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)MATDIM;
			#if RANDOMMATRIX
				randNum = rand() % RANDRANGE;
				if(randNum/RANDRANGE >= SPARSITY)
					emuRows[i][j] = rand() % RANDRANGE;
				else
					emuRows[i][j] = 0;
			#endif
			#if DIAGMATRIX
				if(matRow == j)
					emuRows[i][j] = 2;
				else if(abs(matRow - j) == 1)
					emuRows[i][j] = 1;
				else
					emuRows[i][j] = 0;
			#endif

			#if CROSSMATRIX
				if((rowPer >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
					emuRows[i][j] = 0;
	 			else
 					emuRows[i][j] = rand() % 10 + 1;
			#endif

		}
	}
	return(emuRows);
}

void nodeletsComp(long *nodeId, long **emuRows, long ***valArr, long ***rowArr, long ***colArr, long ***nzArr, long threads){
	//Migrate thread to relevent nodelet
	MIGRATE(nodeId);

	//Find relevent indexing information
	int nodeSplit = MATDIM / NODELETS;
	if(*nodeId == NODELETS-1)
		nodeSplit += MATDIM % NODELETS;
	//printf("Node: %3d threads: %3d nodeSplit: %3d colSplit: %3d\n", *nodeId, threads, nodeSplit, colSplit);

	//Find number of non-zeros on nodelets for allocation purposes
	long *value = malloc(threads * sizeof(long));
	long *rowIndex = malloc(threads * sizeof(long));
	long *colIndex = malloc(threads * sizeof(long));
	long *nonZero = malloc(threads * sizeof(long));
	////int cnt = 0;
	////for(int i = 0; i < nodeSplit; i++)
	////	cnt++;
	//Allocate memory
	////long *value = malloc(cnt * sizeof(long));
	////long *colIndex = malloc(cnt * sizeof(long));
	////long *rowIndex = malloc(cnt * sizeof(long));

	for(int i = 0; i < threads; i++){
		nonZero[i] = cilk_spawn cooComp(emuRows, &value, &rowIndex, &colIndex, nodeSplit, threads, i);
	}

	**valArr = value;
	**rowArr = rowIndex;
	**colArr = colIndex;
	**nzArr = nonZero;
}


long cooComp(long **emuRows, long **value, long **rowIndex, long **colIndex, int nodeSplit, long threads, int threadId){
	long colSplit = MATDIM / threads;
	colSplit += (MATDIM%threads < threadId);
	int startCol = threadId * colSplit;
	int endCol = (threadId+1) * ((MATDIM/threads) + (MATDIM%threads < (threadId+1)));
	long cnt = 0;
	printf("Col Range: %3d -> %3d\n", startCol, endCol);

	for(int i = 0; i < nodeSplit; i++){
		for(int j = startCol; j < endCol; j++){
			if(emuRows[i][j] != 0){
				cnt++;
			}
		}
	}

	//long loc_data[cnt];
	//long loc_ind[cnt];
	//long loc_ptr[rowSplit + 1];
	long* loc_data = malloc(cnt * sizeof(long));
	long* loc_col = malloc(cnt * sizeof(long));
	long* loc_row = malloc(cnt * sizeof(long));

	cnt = 0;
	for(int i = 0; i < nodeSplit; i++){
		for(int j = startCol; j < endCol; j++){
			if(emuRows[i][j] != 0){
				loc_data[cnt] = emuRows[i][j];
				loc_col[cnt] = j;
				loc_row[cnt] = i;
				cnt++;
			}
		}
	}

	*value = loc_data;
	*rowIndex = loc_row;
	*colIndex = loc_col;
	return(cnt);
}

long* csrSpMV(long *nodeId, long threads, long *loc_data, long *loc_ind, long *loc_row){
	int rowSplit = MATDIM / threads;
	//Solution Section
	long *loc_sol = malloc(rowSplit * sizeof(long));
	for(int i = 0; i < rowSplit; ++i){
		//loc_sol[i] = 0;
		//for(int j = loc_ptr[i]; j < loc_ptr[i+1]; j++){
			loc_sol[loc_row[i]] += loc_data[i] * repx[loc_ind[i]];
		//}
	}
	return(loc_sol);
}
