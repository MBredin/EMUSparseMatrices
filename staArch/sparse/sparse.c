#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 1
#define SANITY 1
#define COO 0
#define CSR 1
#define ELL 0
#define SELL 0

struct timeval tval_before, tval_after, tval_result;

struct Array{
	long *arr;
	char name[7];
	size_t size;
};

struct Matrix{
	long *mat;
	char name[7];
	size_t rowM;
	size_t colN;
	size_t matSize;
};

void initMat(struct Matrix *m, size_t M, size_t N, char varName[7]){
	m -> mat = (long *)malloc(M*N*sizeof(long));
	m -> rowM = M;
	m -> colN = N;
	m -> matSize = M * N;
	for(int i = 0; i < 7; i++)
		m -> name[i] = varName[i];
	#if GENERATEMAT
		for(int i = 0; i < M; i++){
			for(int j = 0; j < N; j++){
				if(i == j)
					*(m->mat+i*N+j) = 2;
				else if(abs(i - j) == 1)
					*(m->mat+i*N+j) = 1;
			}
		}
	#endif
}

void initArr(struct Array *a, int N,char varName[7]){
	a -> arr = (long *)malloc(N * sizeof(long));
	a -> size = N;
	for(int i = 0; i < 7; i++)
		a->name[i] = varName[i];
}

void print2d(struct Matrix m){
	for(int i = 0; i < m.matSize; i++){
		if(i % 4 == 0)
			printf("| ");
		printf("%ld ",*(i + m.mat));
		if(i % 4 == 3)
			printf("|\n");
	}
}

void print1d(struct Array *a){
	for(int i = 0; i < 7; i++){
		printf("%c",a->name[i]);
	}
	printf(" = [");
	for(int i = 0; i < a->size; i++)
		printf("%ld ",a->arr[i]);
	printf("]\n");
}

void coo_comp(struct Matrix Orig, struct Array *row, struct Array *col, struct Array *data);
void csr_comp(struct Matrix Orig, struct Array *ptr, struct Array *ind, struct Array *data);

int main(){
	struct Matrix Orig;
	initMat(&Orig,4,4,"Origin");
	//size_t rowM = 4;
	//size_t colN = 4
	//size_t matSize = colM * rowM;
	#if COO
		struct Array coo_row, coo_col, coo_data;
		coo_comp(Orig, &coo_row, &coo_col, &coo_data);

	#endif
	#if CSR
		struct Array csr_ptr, csr_ind, csr_data;
		csr_comp(Orig, &csr_ptr, &csr_ind, &csr_data);
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
	*/
	#if SANITY
		print2d(Orig);
		#if COO
			print1d(&coo_data);
			print1d(&coo_row);
			print1d(&coo_col);
		#endif
		#if CSR
			print1d(&csr_data);
			print1d(&csr_ind);
			print1d(&csr_ptr);
		#endif
		#if ELL
			//Later
		#endif
		#if SELL
			//Later
		#endif
	#endif

}


void coo_comp(struct Matrix Orig, struct Array *row, struct Array *col, struct Array *data){
	int cnt = 0;
	for(int i = 0; i < Orig.matSize; i++)
		if(*(i + Orig.mat) != 0)
			cnt++;
	initArr(row, cnt, "CooRow");
	initArr(col, cnt, "CooCol");
	initArr(data, cnt, "CooDat");

	cnt = 0;
	for(int i = 0; i < Orig.matSize; i++){
		if(*(i + Orig.mat) != 0){
			data->arr[cnt] = *(i + Orig.mat);
			row->arr[cnt] = i / 4;
			col->arr[cnt] = i % 4;
			cnt++;
		}
	}
}

void csr_comp(struct Matrix Orig, struct Array *ptr, struct Array *ind, struct Array *data){
	int cnt = 0;
	for(int i = 0; i < Orig.matSize; i++)
		if(*(i + Orig.mat) != 0)
			cnt++;
	initArr(data, cnt, "CsrDat");
	initArr(ind, cnt, "CsrInd");
	initArr(ptr, (Orig.rowM + 1), "CsrPtr");

	cnt = 0;
	int locCnt = 0;
	ptr->arr[0] = 0;
	for(int i = 0; i < Orig.rowM; i++){
		locCnt = 0;
		for(int j = 0; j < Orig.colN; j++){
			if(*(Orig.mat+i*Orig.colN+j) != 0){
				data->arr[cnt] = *(Orig.mat+i*Orig.colN+j);
				ind->arr[cnt] = j;
				cnt++;
				locCnt++;
			}
		}
		ptr->arr[i+1] = ptr->arr[i] + locCnt;

	}
}

