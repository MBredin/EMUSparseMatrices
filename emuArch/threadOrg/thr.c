#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>
#include <memoryweb.h>

#define ELEMS 512
#define WORKERS 8
#define SANITY 0 

void worker(int sect, long *A, long *B);

int main(){
	//starttiming();

	long *A = mw_malloc1dlong(ELEMS);
	long *B = mw_malloc1dlong(ELEMS);

	//Initialize Values
	for(int i = 0; i < ELEMS; i++){
		A[i] = 1;
		B[i] = 1;
	}

	starttiming();
	//Spawn Workers
	for(int i = 0; i < WORKERS; i++)
		cilk_spawn worker(i,&A[0],&B[0]);
	cilk_sync;

#if SANITY
	for(int i = 0; i < ELEMS; i++)
		printf("A[%d] = %d\n",i,A[i]);
#endif
}

void worker(int sect, long *A, long *B){
	for(int i = sect; i < ELEMS; i = i + 8){
		A[i] = A[i] + B[i];
	}
}
