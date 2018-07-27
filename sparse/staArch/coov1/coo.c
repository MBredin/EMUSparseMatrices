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

void Generate(long *splitData);
void Compress(long threadId, long *stamat, long *value, long *rowInd, long *colInd, long pointer);
void Solution(long *value, long *rowInd, long *colInd, int nz, long *x, long *sol);

int main(){
	//Child Tracking
	pid_t pid;
	//Thread Array
	long *threadId = malloc(THREADS * sizeof(long));
	for(int i = 0; i < THREADS; i++)
		threadId[i] = i;
	//Initialize the vector to be multiplied
        long *x = malloc(MATDIM * sizeof(long));
        for(int i = 0; i < MATDIM; i++)
                x[i] = (i%RANDRANGE) + 1;

	//Set up a shared memory matrix
	//3rd dimension defines the row chunk
	long *splitData;
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	splitData =  mmap(NULL, MATDIM*MATDIM*sizeof(long), protection, visibility, 0, 0);
	//Matrix Generation
	Generate(splitData);
	printf("Program is continuing to the compression algorithm\n");

	//Matrix Compression
	gettimeofday(&tval_before, NULL);

	int cnt = 0;
	int rowSplit = MATDIM / THREADS;
	long *value;
	long *rowInd;
	long *colInd;
	long *pointer;
	pointer =  mmap(NULL, (MATDIM+1)*sizeof(long), protection, visibility, 0, 0);
	pointer[0] = 0;
	
	cnt = 0;
	for(int i = 0; i < MATDIM; i++){
		for(int j = 0; j < MATDIM; j++){
			if(splitData[i * MATDIM + j] != 0){
				cnt++;
			}
		}
		pointer[i+1] = cnt;
	}
	int nz = cnt;

	value =  mmap(NULL, pointer[MATDIM]*sizeof(long), protection, visibility, 0, 0);
	rowInd =  mmap(NULL, pointer[MATDIM]*sizeof(long), protection, visibility, 0, 0);
	colInd =  mmap(NULL, pointer[MATDIM]*sizeof(long), protection, visibility, 0, 0);

	for(int i = 0; i < THREADS; i++){
		pid = fork();
		if(pid != 0){
			//Parent is idle
		}
		//Process is child, execute the function
		else{
			//printf("Child Spawned: %d PID: %d\n", i, getpid());
			Compress(i, splitData, value, rowInd, colInd, pointer[i * rowSplit]);
			exit(0);
		}
	}
	for(int i = 0; i < THREADS; i++)
		wait(NULL);
	printf("Program is continuing to the solution algorithm\n");

	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
        long compTime = (long int)tval_result.tv_usec;

	//Solution
	gettimeofday(&tval_before, NULL);
	long *solution = mmap(NULL, MATDIM*sizeof(long), protection, visibility, 0, 0);
	
	Solution(value, rowInd, colInd, nz, x, solution);

	printf("Solution has completed\n");
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
        long execTime = (long int)tval_result.tv_usec;

	//Sanity Check
	#if SANITY
		cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < MATDIM; i++){
			printf("|");
			for(int j = 0; j < MATDIM; j++){
				printf("%3ld", splitData[i * MATDIM + j]);
				if(splitData[i * MATDIM + j] != 0)
					cnt++;
			}
			printf("|\n");
		}
		printf("Sparsity: %d%%\n", (int)(100.0 * (double)cnt/(MATDIM*MATDIM)));
		
		//Print Data
		printf("Value = [");
		for(int i = 0; i < nz; i++)
			printf("%3ld", value[i]);
		printf("]\n");
		
		//Print Index
		printf("Row Index = [");
		for(int i = 0; i < nz; i++)
			printf("%3ld", rowInd[i]);
		printf("]\n");

		//Printf Pointer
		printf("Column Index = [");
		for(int i = 0; i <= MATDIM; i++)
			printf("%4ld", colInd[i]);
		printf("]\n");
		
		//Print Solution
		printf("Solution :\n");
		for(int i = 0; i < MATDIM; i++)
			printf("|%ld|\n", solution[i]);
		
	#endif
	printf("Execution Time: %ld\n", execTime);
	printf("Compression Time: %ld\n", compTime);

}

void Generate(long *splitData){
	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	double randNum;
	for(int i = 0; i < MATDIM; i++){
		for(int j = 0; j < MATDIM; j++){
			#if RANDOMMATRIX
				randNum = rand() % RANDRANGE;
				if(randNum/RANDRANGE >= SPARSITY)
					splitData[i * MATDIM + j] = rand() % RANDRANGE;
				else
					splitData[i * MATDIM + j] = 0;
			#endif
			#if DIAGMATRIX
				if(matRow == j)
					splitData[i * MATDIM + j] = 2;
				else if(abs(matRow - j) == 1)
					splitData[i * MATDIM + j] = 1;
				else
					splitData[i * MATDIM + j] = 0;
			#endif
			/*
			#if CROSSMATRIX
				if(( >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
					splitData[i * MATDIM + j] = 0;
	 			else
 					splitData[i * MATDIM + j] = rand() % 10 + 1;
			#endif
			*/
			
		}
	}
	return;
}

void Compress(long threadId, long *stamat, long *value, long *rowInd, long *colInd, long pointer){
	/////////////////////////////////////
	/////////////COMPRESSION/////////////
	/////////////////////////////////////
	int rowSplit = (MATDIM / THREADS);
	int rowStart = rowSplit * threadId;
	int rowEnd = rowStart + rowSplit;
	double rowPer, colPer, matRow, randNum;
	if(threadId == THREADS-1)
		rowEnd += MATDIM % THREADS;
	long cnt = 0;
	for(int i = rowStart; i < rowEnd; i++){
		for(int j = 0; j < MATDIM; j++){
			if(stamat[i * MATDIM + j] != 0){
				value[pointer] = stamat[i * MATDIM + j];
				rowInd[pointer] = i;
				colInd[pointer] = j;
				pointer++;
			}
		}
	}
}

void Solution(long *value, long *rowInd, long *colInd, int nz, long *x, long *sol){
	//////////////////////////////////
	/////////////SOLUTION/////////////
	//////////////////////////////////
	for(int i = 0; i < MATDIM; i++)
		sol[i] = 0;
	for(int i = 0; i < nz; i++)
		sol[rowInd[i]] += value[i] * x[colInd[i]];
}
