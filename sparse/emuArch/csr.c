#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 1
#define GENERATEMATEXAMPLE 0
#define SANITY 1

#define NODELETS 8

struct timeval tval_before, tval_after, tval_result;

struct Matrix{
	long *mat;
	char name[7];
	int rowM;
	int colN;
	int matSize;
	int nonZero;
};


void initMat(struct Matrix *m, int M, int N, char varName[7]){
	m -> mat = (long *)malloc(M*N*sizeof(long));
	m -> rowM = M;
	m -> colN = N;
	m -> matSize = M * N;
	for(int i = 0; i < 7; i++)
		m -> name[i] = varName[i];
	#if GENERATEMAT
		int temp = 1;
		for(int i = 0; i < M; i++){
			for(int j = 0; j < N; j++){
				//*(m->mat+i*N+j) = i*N+j;
				if(i == j){
					*(m->mat+i*N+j) = temp;
					temp++;
				}
				else if(abs(i - j) == 1){
					*(m->mat+i*N+j) = temp;
					temp++;
				}
			}
		}
	#endif
	#if GENERATEMATEXAMPLE
		*(m->mat) = 1;
		*(m->mat+2) = 2;
		*(m->mat+3) = 3;
		*(m->mat+6) = 4;
		*(m->mat+7) = 5;
		*(m->mat+9) = 1;
		*(m->mat+11) = 2;
		*(m->mat+24) = 1;
		*(m->mat+25) = 2;
		*(m->mat+26) = 3;
		*(m->mat+27) = 4;
		*(m->mat+28) = 5;
		*(m->mat+30) = 6;
		*(m->mat+31) = 7;
		*(m->mat+33) = 1;
		*(m->mat+35) = 2;
		*(m->mat+37) = 3;
		*(m->mat+40) = 1;
		*(m->mat+41) = 2;
		*(m->mat+49) = 1;
		*(m->mat+50) = 2;
		*(m->mat+51) = 3;
		*(m->mat+52) = 4;
		*(m->mat+53) = 5;
		*(m->mat+54) = 6;
		*(m->mat+55) = 7;
		*(m->mat+56) = 1;
		*(m->mat+57) = 2;
		*(m->mat+58) = 3;
		*(m->mat+59) = 4;
		*(m->mat+60) = 5;
		*(m->mat+61) = 6;
		*(m->mat+62) = 7;
		*(m->mat+63) = 8;
	#endif
	int cnt = 0;
	for(int i = 0; i < m->matSize; i++)
		if(*(i + m->mat) != 0)
			cnt++;

	m -> nonZero = 	cnt;
}

void print2d(struct Matrix m){
	for(int i = 0; i < m.matSize; i++){
		if(i % m.rowM == 0)
			printf("| ");
		printf("%3ld ",*(i + m.mat));
		if(i % m.rowM == m.rowM-1)
			printf("|\n");
	}
}

void printLong(long *arr, int size){
	printf("[");
	for(int i = 0 ; i < size; i++)
		printf("%3ld", arr[i]);
	printf("]");
}

void csr_comp(struct Matrix Orig, long *ptr, long *ind, long *data);

void csr_sclr(long ptr[], long ind[], long data[], long x[], long *res, int size);
void csr_seg(long ptr[], long ind[], long data[], long x[], long *res, int size);

int main(){
	struct Matrix Orig;
	initMat(&Orig,10,10,"Origin");

	//Initialize the vector to be multiplied
	long *x = malloc(Orig.rowM * sizeof(long));
	x[0] = 1;
	for(int i = 1; i < Orig.rowM; i++)
		x[i] = 0;
	long *csr_res = malloc(Orig.rowM * sizeof(long));

	//Start Compression timer
	gettimeofday(&tval_before, NULL);

	//Might just want to compress and solve each row at the same time. (Should improve permformance on EMU)
	for(int i = 0; i < Orig.rowM; i++){
		cilk_spawn csr_comp(Orig, csr_ptr, csr_ind, csr_data);
	}

	long *csr_ind = malloc(Orig.nonZero * sizeof(long));
	long *csr_data = malloc(Orig.nonZero * sizeof(long));
	long *csr_ptr = malloc((Orig.rowM+1) * sizeof(long));

	csr_comp(Orig, csr_ptr, csr_ind, csr_data);
	printf("Size of Array: %zu\n", sizeof(csr_data));

	//End Compression time
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	long compTime = (long int)tval_result.tv_usec;
	
	/*
	gettimeofday(&tval_before, NULL);
	//Spawn Workers
	for(int i = 0; i < WORKERS; i++)
		cilk_spawn worker(i,&A[0],&B[0]);
	cilk_sync;

	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	printf("Time: %ld\n",(long int)tval_result.tv_usec);
	*/

	/////////////////
	//SpMV Solution//
	/////////////////
	
	//Start Execution timer
	gettimeofday(&tval_before, NULL);

	csr_sclr(csr_ptr, csr_ind, csr_data, x , csr_res, Orig.rowM);
	//End Execution timer
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	long execTime = (long int)tval_result.tv_usec;

	//Sanity Check
	#if SANITY
		print2d(Orig);
		printf("X = ");
		printLong(x, Orig.rowM);
		printf("\nData = ");
		printLong(csr_data, Orig.nonZero);
		printf("\nIndex = ");
		printLong(csr_ind, Orig.nonZero);
		printf("\nPointer = ");
		printLong(csr_ptr, Orig.rowM+1);
		printf("\n\nSolution:");
		printLong(csr_res, Orig.rowM);
	#endif
	printf("Compression Time: %ld\n", compTime);
	printf("Execution Time: %ld\n", execTime);
}

void csr_comp(struct Matrix Orig, long *ptr, long *ind, long *data){
	int cnt = 0;
	int locCnt = 0;
	ptr[0] = 0;
	for(int i = 0; i < Orig.rowM; i++){
		locCnt = 0;
		for(int j = 0; j < Orig.colN; j++){
			if(*(Orig.mat+i*Orig.colN+j) != 0){
				data[cnt] = *(Orig.mat+i*Orig.colN+j);
				ind[cnt] = j;
				cnt++;
				locCnt++;
			}
		}
		ptr[i+1] = ptr[i] + locCnt;
	}
}

void csr_sclr(long ptr[], long ind[], long data[], long x[], long *res, int size){
	cilk_for(int i = 0; i < size; i++){
		res[i] = 0;
		for(int j = ptr[i]; j < ptr[i+1] ;j++){
			res[i] += data[j] * x[ind[j]];
		}
	}
}

void csr_seg(long ptr[], long ind[], long data[], long x[], long *res, int size){
	long *bitFlag = malloc(size * sizeof(long));
	long *prod = malloc(size * sizeof(long));

	//Initialize Bit Array to false (0)
	cilk_for(int i = 0; i < size; i++)
		bitFlag[i] = 0;
	//Set prt values to true (1)
	cilk_for(int i =0; i < size; i++)
		bitFlag[ptr[i]] = 1;
	//
	cilk_for(int i = 0; i < size; i++)
		prod[i] = data[i] * x[ind[i]];
	//Segmentation Sum
	int j;
	cilk_for(int i = 0; i < size; i++){
		if(bitFlag[i] == 1){
			j = i + 1;
			while(bitFlag[j] == 0 && j < size){
				prod[i] += prod[j];
				j++;
			}
		}
		else{
			prod[i] = 0;
		}
	}
	//
	cilk_for(int i = 0; i < size; i++){
		if(ptr[i] == ptr[i+1])
			res[i] = 0;
		else
			res[i] = prod[ptr[i]];
	}
}
