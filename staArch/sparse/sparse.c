#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 1
#define SANITY 1
#define COO 0
#define CSR 1
#define CSR5 1

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

struct Tile{
	struct Matrix *BitF;
	struct Matrix *Data;
	struct Matrix *Ind;
	long *yOff;
	long *segOff;
	long *empOff;
	struct TileDesc *next;
	size_t tileSize;
	size_t tileNum;
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
	int cnt = 0;
	for(int i = 0; i < m->matSize; i++)
		if(*(i + m->matSize))
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
void csr5_comp();

void csr_sclr(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res);
void csr_seg(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res);

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
	#if CSR5
		struct Array csr5_row_ptr, csr5_tile_ptr;
		struct TileDesc csr5_desc;
		csr5_comp();
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

	/////////////////
	//SpMV Solution//
	/////////////////
	
	//Initialize the vector to be multiplied
	struct Array x;
	initArr(&x, Orig.rowM, "MulVec");
	for(int i = 0; i < Orig.rowM; i++)
		x.arr[i] = i+1;
	#if COO
		//Later
	#endif
	#if CSR
		struct Array csr_res;
		csr_seg(csr_ptr, csr_ind, csr_data, x , &csr_res);
	#endif

	//Sanity Check
	#if SANITY
		print2d(Orig);
		print1d(&x);
		#if COO
			print1d(&coo_data);
			print1d(&coo_row);
			print1d(&coo_col);
		#endif
		#if CSR
			print1d(&csr_data);
			print1d(&csr_ind);
			print1d(&csr_ptr);
			printf("\nSolution:");
			print1d(&csr_res);
		#endif
		#if CSR5
			//Later
		#endif
	#endif

}


void coo_comp(struct Matrix Orig, struct Array *row, struct Array *col, struct Array *data){
	initArr(row, Orig.nonZero, "CooRow");
	initArr(col, Orig.nonZero, "CooCol");
	initArr(data, Orig.nonZero, "CooDat");

	int cnt = 0;
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

void csr5_comp(){
	//Initialize sigma and omega paramters and cnt for non-zero elements
	int sigma = 2;
	int omega = 2;
	int cnt = 0;
	int tileCnt = Orig.nonZero / (omega*sigma);
	
	//Initialize all data types
	initArr(rowPtr, (Orig.rowM + 1), "Csr5RP");
	initArr(tilePtr, tileCnt, "Csr5TP");

	initMat(Data, omega, sigma, "Csr5Dt");	
	initMat(Ind, omega, sigma, "Csr5In");	
	initMat(&Tile->bitF, omega, sigma, "Csr5Bt");
	Tile->yOff = (long*)malloc(tileCnt*sizeof(long));
	Tile->segOff = (long*)malloc(tileCnt*sizeof(long));
	Tile->empOff = (long*)malloc(tileCnt*sizeof(long));
	
	//Set up data tile, ind tile, bit tile, and row pointer
	cnt = 0;
	int tileCnt = 0
	int locCnt = 0;
	ptr->arr[0] = 0;
	for(int i = 0; i < Orig.rowM; i++){
		locCnt = 0;
		for(int j = 0; j < Orig.colN; j++){
			if(*(Orig.mat+i*Orig.colN+j) != 0){
				data->arr[cnt][] = *(Orig.mat+i*Orig.colN+j);
				ind->arr[cnt] = j;
				cnt++;
				locCnt++;
			}
		}
		ptr->arr[i+1] = ptr->arr[i] + locCnt;

	}

	//Find tile pointer
	for(int i = 0; i < tileCnt; i++){
		
	}
}

void csr_sclr(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res){
	initArr(res, ptr.size-1,"CsrScl");
	int temp;
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
