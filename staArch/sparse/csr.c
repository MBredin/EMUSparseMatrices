#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 0
#define GENERATEMATEXAMPLE 1
#define SANITY 1


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
	size_t nonZero;
};


void initMat(struct Matrix *m, size_t M, size_t N, char varName[7]){
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

void initArr(struct Array *a, int N,char varName[7]){
	a -> arr = (long *)malloc(N * sizeof(long));
	a -> size = N;
	for(int i = 0; i < 7; i++)
		a->name[i] = varName[i];
}


void print2d(struct Matrix m){
	for(int i = 0; i < m.matSize; i++){
		if(i % 8 == 0)
			printf("| ");
		printf("%3ld ",*(i + m.mat));
		if(i % 8 == 7)
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



void csr_comp(struct Matrix Orig, struct Array *ptr, struct Array *ind, struct Array *data);

void csr_sclr(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res);
void csr_seg(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res);

int main(){
	struct Matrix Orig;
	initMat(&Orig,8,8,"Origin");
	struct Array csr_ptr, csr_ind, csr_data;
	csr_comp(Orig, &csr_ptr, &csr_ind, &csr_data);
	
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
	
	//Initialize the vector to be multiplied
	struct Array x;
	initArr(&x, Orig.rowM, "MulVec");
	for(int i = 0; i < Orig.rowM; i++)
		x.arr[i] = i+1;
	struct Array csr_res;
	csr_seg(csr_ptr, csr_ind, csr_data, x , &csr_res);

	//Sanity Check
	#if SANITY
		print2d(Orig);
		print1d(&x);
		printf("\n");
		print1d(&csr_data);
		print1d(&csr_ind);
		print1d(&csr_ptr);
		printf("\nSolution:");
		print1d(&csr_res);
	#endif

}

void csr_comp(struct Matrix Orig, struct Array *ptr, struct Array *ind, struct Array *data){
	initArr(data, Orig.nonZero, "CsrDat");
	initArr(ind, Orig.nonZero, "CsrInd");
	initArr(ptr, (Orig.rowM + 1), "CsrPtr");

	int cnt = 0;
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

void csr_sclr(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res){
	initArr(res, ptr.size-1,"CsrScl");
	for(int i = 0; i < ptr.size-1; i++){
		res->arr[i] = 0;
		for(int j = ptr.arr[i]; j < ptr.arr[i+1] ;j++){
			res->arr[i] += data.arr[j] * x.arr[ind.arr[j]];
		}
	}
}

void csr_seg(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res){
	initArr(res, ptr.size-1, "CsrSeg");
	struct Array bitFlag, prod;
	initArr(&bitFlag, data.size, "BitFlg");
	initArr(&prod, data.size, "PrdHld");

	//Initialize Bit Array to false (0)
	for(int i = 0; i < bitFlag.size; i++)
		bitFlag.arr[i] = 0;
	//Set prt values to true (1)
	for(int i =0; i < ptr.size; i++)
		bitFlag.arr[ptr.arr[i]] = 1;
	//
	for(int i = 0; i < prod.size; i++)
		prod.arr[i] = data.arr[i] * x.arr[ind.arr[i]];
	//Segmentation Sum
	int j;
	for(int i = 0; i < prod.size; i++){
		if(bitFlag.arr[i] == 1){
			j = i + 1;
			while(bitFlag.arr[j] == 0 && j < prod.size){
				prod.arr[i] += prod.arr[j];
				j++;
			}
		}
		else{
			prod.arr[i] = 0;
		}
	}
	//
	for(int i = 0; i < res->size; i++){
		if(ptr.arr[i] == ptr.arr[i+1])
			res->arr[i] = 0;
		else
			res->arr[i] = prod.arr[ptr.arr[i]];
	}
}
