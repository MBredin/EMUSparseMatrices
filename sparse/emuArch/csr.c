#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>

//Print matrix operations and solution
#define SANITY 0

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//System Specs
#define NODELETS 8
#define THREADS 4
#define MATDIM 2000

//Constants for random generated matrix
#define SPARSITY 0.5
#define RANDRANGE 10

//Replicate vector across each nodelet
replicated long *x;

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
void Compress(long *nodeId, long **emuRows, long **data, long **index, long **pointer);
long *Solution(long *nodeId, long **emuRows, long *loc_data, long *loc_ind, long *loc_ptr);
void csr_solv(long **emuRows, long nodeRows, int i, long *loc_sol);

int main(){
	long *tempX = alloc_x();
	mw_replicated_init((long *)&x, (long)tempX);
	
	long *nodes = mw_malloc1dlong(NODELETS * sizeof(long *));
	for(int i = 0; i < NODELETS; i++)
		nodes[i] = i;
	/*
	for(int i = 0; i < NODELETS; i++){
		MIGRATE(&nodes[i]);
		printf("Node %ld: [", nodes[i]);
		for(int j = 0; j < MATDIM; j++){
			printf("%3ld", x[j]);
		}
		printf("End Node: %ld}\n", NODE_ID());
	}
	*/
	
	long **splitData[NODELETS];
	//Matrix Generation
	//starttiming();
	for(int i = 0; i < NODELETS; i++){
		splitData[i] = cilk_spawn Generate(&nodes[i]);
	}
	cilk_sync;
	//Matrix Compression
	long *data[NODELETS];
	long *index[NODELETS];
	long *pointer[NODELETS];
	//starttiming();
	for(int i = 0; i < NODELETS; i++){
		cilk_spawn Compress(&nodes[i], splitData[i], &data[i], &index[i], &pointer[i]);
	}
	cilk_sync;
	//Solution
	long *solution[NODELETS];
	starttiming();
	for(int i = 0; i < NODELETS; i++){
		solution[i] = cilk_spawn Solution(&nodes[i], splitData[i], data[i], index[i], pointer[i]);
	}
	cilk_sync;	
	

	//Sanity Check
	#if SANITY
		int nodeRows = MATDIM / NODELETS;
		int cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < NODELETS; i++){
			if(i == NODELETS-1)
				nodeRows += MATDIM % NODELETS;
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
		printf("Sparsity: %d%%\n", (int)(100.0 * (double)cnt/(MATDIM*MATDIM)));
		//Print Solution
		nodeRows = MATDIM / NODELETS;
		printf("[");
		for(int i = 0; i < NODELETS; i++){
			if(i != 0)
				printf("|");
			if(i == NODELETS-1)
				nodeRows += MATDIM % NODELETS;
			for(int j = 0; j < nodeRows; j++)
				printf("%3ld", solution[i][j]);
		}
		printf("]\n");
	#endif

}

long **Generate(long *nodeId){
	MIGRATE(&nodeId);
	
	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	int rowSplit = MATDIM / NODELETS;
	int nodeRows = rowSplit;
	double rowPer, colPer, matRow, randNum;
	if(*nodeId == NODELETS-1)
		nodeRows += MATDIM % NODELETS;
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

void Compress(long *nodeId, long **emuRows, long **data, long **index, long **pointer){
	
	/////////////////////////////////////
	/////////////COMPRESSION/////////////
	/////////////////////////////////////
	int rowSplit = MATDIM / NODELETS;
	int nodeRows = rowSplit;
	if(*nodeId == NODELETS-1)
		nodeRows += MATDIM % NODELETS;
	long cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){
				cnt++;
			}
		}
	}
	long *loc_data = malloc(cnt * sizeof(long));
	long *loc_ind = malloc(cnt * sizeof(long));
	long *loc_ptr = malloc((nodeRows + 1) * sizeof(long));
	loc_ptr[0] = 0;

	cnt = 0;
	long pcnt = 0;
	for(int i = 0; i < nodeRows; i++){
		pcnt = 0;
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){				
				loc_data[cnt] = emuRows[i][j];
				loc_ind[cnt] = j;
				cnt++;
				pcnt++;
			}
		}
		loc_ptr[i+1] = loc_ptr[i] + pcnt;
	}
	*data = loc_data;
	*index = loc_ind;
	*pointer = loc_ptr;
}

long *Solution(long *nodeId, long **emuRows, long *loc_data, long *loc_ind, long *loc_ptr){

	//////////////////////////////////
	/////////////SOLUTION/////////////
	//////////////////////////////////
	int rowSplit = MATDIM / NODELETS;
	int nodeRows = rowSplit;
	if(*nodeId == NODELETS-1)
		nodeRows += MATDIM % NODELETS;
	long *loc_sol = malloc(nodeRows * sizeof(long));
	for(int i = 0; i < nodeRows; i++){
		loc_sol[i] = 0;
		for(int j = loc_ptr[i]; j < loc_ptr[i+1]; j++){
			loc_sol[i] += loc_data[j] * x[loc_ind[j]];
		}
	}
	return(loc_sol);
}
