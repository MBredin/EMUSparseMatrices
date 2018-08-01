#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

//Print matrix operations and solution
#define SANITY 0

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//System Specs
#define THREADS 8
#define MATDIM 2000

//Constants for random generated matrix
#define SPARSITY 0.5
#define RANDRANGE 10

struct timeval tval_before, tval_after, tval_result;

long **Generate(long threadId);
void Compress(long threadId, long **stamat, long **data, long **index, long **pointer);
long *Solution(long threadId, long **stamat, long *loc_data, long *loc_ind, long *loc_ptr, long *x);

int main(){
	//Thread Array
	long *threadId = malloc(THREADS * sizeof(long));
	for(int i = 0; i < THREADS; i++)
		threadId[i] = i;
	//Initialize the vector to be multiplied
        long *x = malloc(MATDIM * sizeof(long));
        for(int i = 0; i < MATDIM; i++)
                x[i] = i+1;

	long **splitData[THREADS];
	//Matrix Generation
	for(int i = 0; i < THREADS; i++){
		splitData[i] = cilk_spawn Generate(threadId[i]);
	}
	cilk_sync;
	//Matrix Compression
	long *data[THREADS];
	long *index[THREADS];
	long *pointer[THREADS];
	gettimeofday(&tval_before, NULL);
	for(int i = 0; i < THREADS; i++){
		cilk_spawn Compress(threadId[i], splitData[i], &data[i], &index[i], &pointer[i]);
	}
	cilk_sync;
	timersub(&tval_after, &tval_before, &tval_result);
        long compTime = (long int)tval_result.tv_usec;

	//Solution
	long *solution[THREADS];
	gettimeofday(&tval_before, NULL);
	for(int i = 0; i < THREADS; i++){
		solution[i] = cilk_spawn Solution(threadId[i], splitData[i], data[i], index[i], pointer[i], x);
	}
	cilk_sync;	
	timersub(&tval_after, &tval_before, &tval_result);
        long execTime = (long int)tval_result.tv_usec;
	

	//Sanity Check
	#if SANITY
		int nodeRows = MATDIM / THREADS;
		int cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < THREADS; i++){
			if(i == THREADS-1)
				nodeRows += MATDIM % THREADS;
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
		nodeRows = MATDIM / THREADS;
		printf("[");
		for(int i = 0; i < THREADS; i++){
			if(i != 0)
				printf("|");
			if(i == THREADS-1)
				nodeRows += MATDIM % THREADS;
			for(int j = 0; j < nodeRows; j++)
				printf("%3ld", solution[i][j]);
		}
		printf("]\n");
	#endif
	printf("Execution Time: %ld\n", execTime);
        printf("Compression Time: %ld\n", compTime);
}

long **Generate(long threadId){
	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	int rowSplit = MATDIM / THREADS;
	int nodeRows = rowSplit;
	double rowPer, colPer, matRow, randNum;
	if(threadId == THREADS-1)
		nodeRows += MATDIM % THREADS;
	long **stamat = malloc(nodeRows * sizeof(long *));

	//Allocate memory for given node
	for(int j = 0; j < nodeRows; j++){
		stamat[j] = malloc(MATDIM * sizeof(long));
	}
		
	//int temp = threadId * rowSplit;
	for(int i = 0; i < nodeRows; i++){
		matRow = i + (threadId * rowSplit);
		rowPer = (double)(matRow) / (double)MATDIM;
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)MATDIM;
			#if RANDOMMATRIX
				randNum = rand() % RANDRANGE;
				if(randNum/RANDRANGE >= SPARSITY)
					stamat[i][j] = rand() % RANDRANGE;
				else
					stamat[i][j] = 0;
			#endif
			#if DIAGMATRIX
				if(matRow == j)
					stamat[i][j] = 2;
				else if(abs(matRow - j) == 1)
					stamat[i][j] = 1;
				else
					stamat[i][j] = 0;
			#endif
			
			#if CROSSMATRIX
				if((rowPer >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
					stamat[i][j] = 0;
	 			else
 					stamat[i][j] = rand() % 10 + 1;
			#endif
			
		}
	}
	return(stamat);
}

void Compress(long threadId, long **stamat, long **data, long **index, long **pointer){
	
	/////////////////////////////////////
	/////////////COMPRESSION/////////////
	/////////////////////////////////////
	int rowSplit = MATDIM / THREADS;
	int nodeRows = rowSplit;
	if(threadId == THREADS-1)
		nodeRows += MATDIM % THREADS;
	long cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(stamat[i][j] != 0){
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
			if(stamat[i][j] != 0){				
				loc_data[cnt] = stamat[i][j];
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

long *Solution(long threadId, long **stamat, long *loc_data, long *loc_ind, long *loc_ptr, long *x){

	//////////////////////////////////
	/////////////SOLUTION/////////////
	//////////////////////////////////
	int rowSplit = MATDIM / THREADS;
	int nodeRows = rowSplit;
	if(threadId == THREADS-1)
		nodeRows += MATDIM % THREADS;
	long *loc_sol = malloc(nodeRows * sizeof(long));
	for(int i = 0; i < nodeRows; i++){
		loc_sol[i] = 0;
		for(int j = loc_ptr[i]; j < loc_ptr[i+1]; j++){
			loc_sol[i] += loc_data[j] * x[loc_ind[j]];
		}
	}
	return(loc_sol);
}
