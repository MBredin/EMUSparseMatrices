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
#define SANITY 1

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//System Specs
#define CORES 8
//#define THREADS 2 //2, 4, 8, 16, 32, 64
//#define MATDIM 8 //512, 1024, 2048, 4096, 8192, 16384

//Constants for random generated matrix
#define SPARSITY 0.9
#define RANDRANGE 10

//Globals
int Threads, Matdim;

struct timeval tval_before, tval_after, tval_result;

void Generate(long *splitData);
void Compress(int id, long *stamat, long *data, long *colIndex, long *rowIndex, long pointer);
void Solution(long **segSol, int id, long *data, long *rowindex, long *colindex, long *x, long *sol, long nz, int nzSplit);

static __inline__ unsigned long long rdtsc(void){
	unsigned hi, lo;
	__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

int main(int argc, char** argv){
	if(argc != 3){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		Threads = atoi(argv[1]);
		Matdim = atoi(argv[2]);
	}
	unsigned long long starttime, endtime, comCyc, solCyc;
	//Child Tracking
	pid_t pid;
	//Thread Array
	long *coreId = malloc(CORES * sizeof(long));
	for(int i = 0; i < CORES; i++)
		coreId[i] = i;
	//Initialize the vector to be multiplied
        long *x = malloc(Matdim * sizeof(long));
        for(int i = 0; i < Matdim; i++)
                x[i] = (i%RANDRANGE)+1;

	//Set up a shared memory matrix
	//3rd dimension defines the row chunk
	long *splitData;
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_ANONYMOUS | MAP_SHARED;
	splitData =  mmap(NULL, Matdim*Matdim*sizeof(long), protection, visibility, 0, 0);
	//Matrix Generation
	Generate(splitData);
	//printf("Program is continuing to the compression algorithm\n");

	//Matrix Compression
	gettimeofday(&tval_before, NULL);
	starttime = rdtsc();

	int cnt = 0;
	int colSplit = Matdim / (CORES * Threads);
	long *data;
	long *colIndex;
	long *rowIndex;
	long *pointer =  mmap(NULL, (Matdim+1)*sizeof(long), protection, visibility, 0, 0);
	pointer[0] = 0;
	
	cnt = 0;
	for(int i = 0; i < Matdim; i++){
		for(int j = 0; j < Matdim; j++){
			if(splitData[j * Matdim + i] != 0){
				cnt++;
			}
		}
		pointer[i+1] = cnt;
	}

	data =  mmap(NULL, pointer[Matdim]*sizeof(long), protection, visibility, 0, 0);
	colIndex =  mmap(NULL, pointer[Matdim]*sizeof(long), protection, visibility, 0, 0);
	rowIndex =  mmap(NULL, pointer[Matdim]*sizeof(long), protection, visibility, 0, 0);

	for(int i = 0; i < CORES; i++){
		pid = fork();
		if(pid != 0){
			//Parent is idle
		}
		//Process is child, execute the function
		else{
			//printf("Child Spawned: %d PID: %d\n", i, getpid());
			for(int j = 0; j < Threads; j++)
				cilk_spawn Compress(j * Threads + i, splitData, data, colIndex, rowIndex, pointer[(j * Threads + i) * colSplit]);
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
	long *segSolution[CORES * Threads];
	int nzSplit = pointer[Matdim] / (CORES * Threads);
	long *solution = malloc(Matdim * sizeof(long));
	
	for(int i = 0; i < CORES; i++){
		pid = fork();
		if(pid != 0){
			//Parent is idle
		}
		//Process is child, execute the function
		else{
			//printf("Child Spawned: %d PID: %d\n", i, getpid());
			for(int j = 0; j < Threads; j++)
				Solution(&segSolution[i * Threads + j], j * Threads + i, data, colIndex, rowIndex, x, solution, pointer[Matdim], nzSplit);
			exit(0);
		}
	}
	for(int i = 0; i < CORES; i++)
		wait(NULL);
	for(int i = 0; i < Matdim; i++){
		solution[i] = 0;
		for(int j = 0; j < CORES*Threads; j++)
			solution[i] += *segSolution[j];
	}
	//printf("Program is continuing to the solution algorithm\n");

	//printf("Solution has completed\n");
	endtime = rdtsc();
	solCyc = endtime - starttime;
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
        long execTime = (long int)tval_result.tv_usec;

	//Sanity Check
	#if SANITY
		cnt = 0;
		//Print Starting Matrix
		for(int i = 0; i < Matdim; i++){
			printf("|");
			for(int j = 0; j < Matdim; j++){
				printf("%3ld", splitData[i * Matdim + j]);
				if(splitData[i * Matdim + j] != 0)
					cnt++;
			}
			printf("|\n");
		}
		printf("Sparsity: %d%%\n", (int)(100.0 * (double)cnt/(Matdim*Matdim)));
		
		//Print Data
		printf("Data = [");
		for(int i = 0; i < pointer[Matdim]; i++)
			printf("%3ld", data[i]);
		printf("]\n");
		
		//Print Index
		printf("Column Index = [");
		for(int i = 0; i < pointer[Matdim]; i++)
			printf("%3ld", colIndex[i]);
		printf("]\n");

		//Printf Pointer
		printf("Row Index = [");
		for(int i = 0; i <= pointer[Matdim]; i++)
			printf("%4ld", rowIndex[i]);
		printf("]\n");
		
		//Print Solution
		printf("Solution :\n");
		for(int i = 0; i < Matdim; i++)
			printf("|%ld|\n", solution[i]);
		
	#endif
	printf("Matrix Size: %d\nThreads per Core: %d\n", Matdim, Threads);
        printf("Compression Cycles: %llu  Time:%lu\n", comCyc, compTime);
        printf("Solution    Cycles: %llu  Time:%lu\n\n", solCyc, execTime);
}

void Generate(long *splitData){
	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	double randNum;
	for(int i = 0; i < Matdim; i++){
		for(int j = 0; j < Matdim; j++){
			#if RANDOMMATRIX
				randNum = rand() % RANDRANGE;
				if(randNum/RANDRANGE >= SPARSITY)
					splitData[i * Matdim + j] = rand() % RANDRANGE;
				else
					splitData[i * Matdim + j] = 0;
			#endif
			#if DIAGMATRIX
				if(matRow == j)
					splitData[i * Matdim + j] = 2;
				else if(abs(matRow - j) == 1)
					splitData[i * Matdim + j] = 1;
				else
					splitData[i * Matdim + j] = 0;
			#endif
			/*
			#if CROSSMATRIX
				if(( >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
					splitData[i * Matdim + j] = 0;
	 			else
 					splitData[i * Matdim + j] = rand() % 10 + 1;
			#endif
			*/
			
		}
	}
	return;
}

void Compress(int id, long *stamat, long *data, long *colIndex, long *rowIndex, long pointer){
	/////////////////////////////////////
	/////////////COMPRESSION/////////////
	/////////////////////////////////////
	int colSplit = Matdim / (CORES * Threads);
	int colStart = colSplit * id;
	int colEnd = colStart + colSplit;
	double rowPer, colPer, matRow, randNum;
	long cnt = 0;
	for(int i = colStart; i < colEnd; i++){
		for(int j = 0; j < Matdim; j++){
			if(stamat[j * Matdim + i] != 0){
				data[pointer] = stamat[j * Matdim + i];
				colIndex[pointer] = i;
				rowIndex[pointer] = j;
				pointer++;
			}
		}
	}
}

void Solution(long **segSol, int id, long *data, long *colIndex, long *rowIndex, long *x, long *sol, long nz, int nzSplit){
	int nzStart = nz * id;
	int nzEnd = nzStart + nzSplit;
	if(id == CORES*Threads-1)
		nzEnd += nz % (CORES * Threads);
	long *locSol = malloc(Matdim * sizeof(long));
	for(int i = 0; i < Matdim; i++)
		segSol[i] = 0;
	//////////////////////////////////
	/////////////SOLUTION/////////////
	//////////////////////////////////
	for(int i = nzStart; i < nzEnd; i++){
		locSol[rowIndex[i]] += data[i] * x[colIndex[i]];
	}
	*segSol = locSol;
	return;
}
