#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define SANITY 0
#define COO 0
#define CSR 0
#define ELL 0
#define SELL 0

struct timeval tval_before, tval_after, tval_result;

typedef struct{
	long *arr;
	size_t size;
} Array;

void initArr(Array *a){
	a -> array = (long *)malloc(sizeof(long));
	a -> size = 1;
}

void coo_comp(long fullMatrix, size_t matSize, long *row, long *col, long *data);
void csr_comp(long fullMatrix, size_t matSize, long *ptr, long *ind, long *data);
void ell_comp(long fullMatrix, size_t matSize, long *data, long *ind);
void sell_comp(long fullMatrix, size_t matSize, long *data, long *ind);

void worker(int sect, long *A, long *B);

int main(){
	long fullMatrix[4][4] = [[2,1,0,0],[1,2,1,0],[0,1,2,1],[0,0,1,2]];
	size_t matSize = 16;
	#if COO
		Array row, col, data;
		coo_comp(fullMatrix, &row, &col, &data);
	#endif
	#if CSR
		//Later
	#endif
	#if ELL
		//Later
	#endif
	#if SELL
		//Later
	#endif
	
	/*
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
*/
}


void coo_comp(long fullMatrix, size_t matSize, long *row, long *col, long *data){
	int cnt = 0;
	for(int i = 0; i < matSize; i++)
		if(*(i + fullMatrix) != 0)
			cnt++;
}

void csr_comp(long fullMatrix, size_t matSize, long *ptr, long *ind, long *data){

}

void ell_comp(long fullMatrix, size_t matSize, long *data, long *ind){

}

void sell_comp(long fullMatrix, size_t matSize, long *data, long *ind){

}

void worker(int sect, long *A, long *B){
	int partSize = ELEMS / WORKERS;	
	for(int i = sect*partSize; i < (sect+1)*partSize; i++){
		A[i] = A[i] + B[i];
	}
}
