#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define ELEMS 512
#define WORKERS 8
#define SANITY 0

struct timeval tval_before, tval_after, tval_result;

void worker(int sect, long *A, long *B);

int main(){

	long *A = malloc(ELEMS * sizeof(long));
	long *B = malloc(ELEMS * sizeof(long));

	//Initialize Values
	for(int i = 0; i < ELEMS; i++){
		A[i] = 1;
		B[i] = 1;
	}

	gettimeofday(&tval_before, NULL);
	//Spawn Workers
	for(int i = 0; i < WORKERS; i++)
		cilk_spawn worker(i,&A[0],&B[0]);
	cilk_sync;

	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	printf("Time: %ld\n",(long int)tval_result.tv_usec);

#if SANITY
	for(int i = 0; i < ELEMS; i++)
		printf("A[%d] = %ld.9\n",i,A[i]);
#endif
}

void worker(int sect, long *A, long *B){
	int partSize = ELEMS / WORKERS;	
	for(int i = sect*partSize; i < (sect+1)*partSize; i++){
		A[i] = A[i] + B[i];
	}
}
