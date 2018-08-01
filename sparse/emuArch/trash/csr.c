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

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//System Specs
#define NODELETS 256 //8 nodelets, 32 threads per nodelet
#define THREADS 4
#define MATDIM 100

#define SOLUTIONTIME 0

//Constants for random generated matrix
#define SPARSITY 0.1
#define RANDRANGE 10

struct timeval tval_before, tval_after, tval_result;

//Replicate vector across each nodelet
replicated long *repx;

//Set values in vector to be multiplied
void fill_x(void *ptr, long node){
	long *gto = (long *)ptr;

	for(int i = 0; i < MATDIM; i++)
		gto[i] = i+1;
}

//Allocate memory for vector
long *alloc_x(void){
	long *mr = mw_mallocrepl(MATDIM * sizeof(long));
	mw_replicated_init_generic(mr, fill_x);

	return mr;
}

long **Generate(long *nodeId);
void csrSpMV(long *nodeId, long **emuRows);

int main(){
	unsigned long long starttime, endtime, comptime;
	long *tempX = alloc_x();
	mw_replicated_init((long *)&repx, (long)tempX);
	
	long *nodes = mw_malloc1dlong(NODELETS * sizeof(long *));
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
	starttiming();
	starttime = CLOCK();
	for(int i = 0; i < NODELETS; i++){
		cilk_spawn csrSpMV(&nodes[i], splitData[i]);
	}
	cilk_sync;
	endtime = CLOCK();

	//Sanity Check
	#if SANITY
		int nodeRows = MATDIM / NODELETS;
		int remRows = MATDIM % NODELETS;
		int cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < NODELETS; i++){
			if(remRows > 0 && remRows < i)
				nodeRows++;
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
	#endif
	comptime = endtime - starttime; 
	printf("Execution Cycles: %ld\n", comptime);
}

long **Generate(long *nodeId){
	MIGRATE(&nodeId);
	
	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	int nodeRows = MATDIM / NODELETS;
	int remRows = MATDIM / NODELETS;
	double rowPer, colPer, matRow, randNum;
	if(remRows != 0 && remRows > *nodeId)
		nodeRows++;
	long **emuRows = malloc(nodeRows * sizeof(long *));

	//Allocate memory for given node
	for(int j = 0; j < nodeRows; j++){
		emuRows[j] = malloc(MATDIM * sizeof(long));
	}
		
	//int temp = *nodeId * rowSplit;
	for(int i = 0; i < nodeRows; i++){
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

void csrSpMV(long *nodeId, long **emuRows){
	/////////////////////////////////////
	/////////////COMPRESSION/////////////
	/////////////////////////////////////
	int nodeRows = MATDIM / NODELETS;
	int remRows = MATDIM / NODELETS;
	if(remRows != 0 && remRows > *nodeId)
		nodeRows++;
	long cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){
				cnt++;
			}
		}
	}
	long loc_data[cnt];
	long loc_ind[cnt];
	long loc_ptr[nodeRows + 1];
	loc_ptr[0] = 0;

	cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){
				loc_data[cnt] = emuRows[i][j];
				loc_ind[cnt] = j;	
				cnt++;
			}
		}
		loc_ptr[i+1] = cnt;
	}
	#if SOLUTIONTIME
		//Solution Section
		long *loc_sol = malloc(nodeRows * sizeof(long));
		for(int i = 0; i < nodeRows; i++){
			loc_sol[i] = 0;
			for(int j = loc_ptr[i]; j < loc_ptr[i+1]; j++){
				loc_sol[i] += loc_data[j] * repx[loc_ind[j]];
			}
		}
	#endif
}

