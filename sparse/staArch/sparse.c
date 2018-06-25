#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 0
#define GENERATEMATEXAMPLE 1
#define SANITY 1
#define COO 0
#define CSR 0
#define CSR5 1

#define OMEGA 4
#define SIGMA 4

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
	//Matrices
	long BitF[OMEGA][SIGMA];
	long Data[OMEGA][SIGMA];
	long Ind[OMEGA][SIGMA];
	//Arrays
	long yOff[OMEGA];
	long segOff[OMEGA];
	long empOff[OMEGA * SIGMA];
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

void printTile(struct Tile t, int tileNum){
	printf("tileNum: %d\n", tileNum);
	printf("Data:            Index:           Bool:\n");
	for(int i = 0; i < OMEGA; i++){
		printf("|");
		for(int j = 0; j < SIGMA; j++){
			printf("%2ld ",t.Data[i][j]);
		}
		printf("|   |");
		for(int j = 0; j < SIGMA; j++){
			printf("%2ld ",t.Ind[i][j]);
		}
		printf("|   |");
		for(int j = 0; j < SIGMA; j++){
			printf("%2ld ",t.BitF[i][j]);
		}
		printf("|\n");
	}
	printf("Y-Offset[");
	for(int i = 0; i < OMEGA; i++)
		printf("%2ld",t.yOff[i]);
	printf("]\n");
	printf("Segment-Offset[");
	for(int i = 0; i < OMEGA; i++)
		printf("%2ld",t.segOff[i]);
	printf("]\n");
	printf("Empty-Offset[");
	for(int i = 0; i < OMEGA; i++)
		printf("%2ld",t.empOff[i]);
	printf("]\n");
	printf("\n");
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

void printLong(double *a, int size){
	printf(" = [");
	for(int i = 0; i < size; i++)
		printf("%1.0f ",a[i]);
	printf("]\n");
}

void exPreSum(long *arr){
	long *arrCpy = malloc(OMEGA * sizeof(long));
	for(int i = 0; i < OMEGA; i++){
		arrCpy[i] = arr[i];
	}
	arr[0] = 0;
	for(int i = 1; i < OMEGA; i++)
		arr[i] = arr[i-1] + arrCpy[i-1];
}

void segSum(long *arr, long *bitArr){
	long *arrCpy = malloc(OMEGA * sizeof(long));
	printf("Starting Segment: {");
	for(int i = 0; i < OMEGA; i++){
		arrCpy[i] = arr[i];
		printf("%2ld",arr[i]);
	}
//	printf("Segment Done: [");
	for(int i = 0; i < OMEGA; i++){
		if(bitArr[i] == 1)
			arr[i] = arrCpy[i];
		else
			arr[i] += arr[i-1];
//		printf("%2ld",arr[i]);
	}
	printf("]\n");
}

int binSearch(double *rowPtr, int bnd, size_t upper){
	if(bnd <= rowPtr[0])
		return(0);
	if(bnd >= rowPtr[upper])
		return(upper);
	while(1){
		if(rowPtr[upper] > bnd)
			upper--;
		else
			return(upper);
			
	}
}


void coo_comp(struct Matrix Orig, struct Array *row, struct Array *col, struct Array *data);
void csr_comp(struct Matrix Orig, struct Array *ptr, struct Array *ind, struct Array *data);
void csr5_comp(struct Matrix Orig, struct Tile *tileArr, double *rowPrt, double *tilePtr, int *rowPLen, int *tilePLen);

void csr_sclr(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res);
void csr_seg(struct Array ptr, struct Array ind, struct Array data, struct Array x, struct Array *res);

int main(){
	struct Matrix Orig;
	initMat(&Orig,8,8,"Origin");
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
		int tileCnt = Orig.nonZero / (OMEGA * SIGMA) + 1;
		struct Tile *tileArr = malloc(tileCnt * sizeof(struct Tile));
		int rowPLen, tilePLen;
		double *rowPtr = malloc((Orig.rowM+1)*sizeof(double));
		double *tilePtr = malloc((tileCnt+1)*sizeof(double));
		csr5_comp(Orig, tileArr, rowPtr, tilePtr, &rowPLen, &tilePLen);
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
		printf("\n");
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
			printf("CSR5 Compressed Matrix\nRow_Pointer");
			printLong(rowPtr, rowPLen);
			printf("Tile_Pointer");
			printLong(tilePtr, tilePLen+1);
			for(int i = 0; i < tileCnt; i++)
				printTile(tileArr[i],i);
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

void csr5_comp(struct Matrix Orig, struct Tile *tileArr, double *rowPtr, double *tilePtr, int *rowPLen, int *tilePLen){
	//Initialize all data types
	int tileSize = OMEGA * SIGMA;
	int tileCnt = Orig.nonZero / tileSize + 1;
	*rowPLen = (int)Orig.rowM + 1;
	//Dupilcate Varialbe, get rid of it
	*tilePLen = (int)tileCnt;
	//*rowPtr = malloc((Orig.rowM+1)*sizeof(double));
	//*tilePtr = malloc(tileCnt*sizeof(double));
	//initArr(rowPtr, (Orig.rowM + 1), "Csr5RP");
	//initArr(tilePtr, tileCnt, "Csr5TP");

	
	//Set up data tile, ind tile, bit tile, and row pointer
	int cnt = 0;
	int locCnt = 0;
	rowPtr[0] = 0;
	for(int i = 0; i < Orig.rowM; i++){
		locCnt = 0;
		for(int j = 0; j < Orig.colN; j++){
			if(*(Orig.mat+i*Orig.colN+j) != 0){
				tileArr[cnt / tileSize].Data[cnt%OMEGA][(cnt/SIGMA)%OMEGA] = *(Orig.mat+i*Orig.colN+j);
				tileArr[cnt / tileSize].Ind[cnt%OMEGA][(cnt/SIGMA)%OMEGA] = j;
				if(locCnt == 0 || cnt%tileSize == 0)
					tileArr[cnt / tileSize].BitF[cnt%OMEGA][(cnt/SIGMA)%SIGMA] = 1;
				else
					tileArr[cnt / tileSize].BitF[cnt%OMEGA][(cnt/SIGMA)%SIGMA] = 0;
				cnt++;
				locCnt++;
			}
		}
		rowPtr[i+1] = rowPtr[i] + locCnt;

	}

	//Find tile pointer
	int bnd;
	for(int i = 0; i < tileCnt; i++){
		bnd = i * OMEGA * SIGMA;
		tilePtr[i] = binSearch(&rowPtr[0], bnd, Orig.rowM);
	}
	tilePtr[tileCnt] = Orig.rowM;
	for(int i = 0; i < tileCnt; i++){
		for(int j = (int)tilePtr[i]; j < (int)tilePtr[i+1]; j++)
			if(rowPtr[j] == rowPtr[j+1]){
				tilePtr[i] = -1.0 * tilePtr[i];
				break;
			}
	}
	
	//Find the other tile desciptors
	long *bitT = malloc(OMEGA * sizeof(long));
	for(int t = 0; t < tileCnt; t++){
		for(int i = 0; i < OMEGA; i++){
			tileArr[t].yOff[i] = 0;
			bitT[i] = 0;
			for(int j = 0; j < SIGMA; j++){
				tileArr[t].yOff[i] = tileArr[t].yOff[i] + tileArr[t].BitF[j][i];
				bitT[i] = bitT[i] || tileArr[t].BitF[j][i+1];
			}
			tileArr[t].segOff[i] = 1 - bitT[i];
		}
		//Find y_Offset
		exPreSum(&tileArr[t].yOff[0]);
		
		//Find empty_Offest
		if(tilePtr[t] < 0 || tilePtr[t] == -0.0){
			int length = 0;
			int eid = 0;
			int ptr, idx;
			for(int i = 0 ; i < OMEGA; i++)
				for(int j = 0; j < SIGMA; j++)
					length += tileArr[t].BitF[j][i];
		
			for(int i = 0 ; i < OMEGA; i++){
				for(int j = 0; j < SIGMA; j++){
					if(tileArr[t].BitF[j][i] == 1){
						ptr = t * OMEGA * SIGMA + i * SIGMA + j;
						idx = binSearch(&rowPtr[0], ptr, Orig.rowM);
						idx = idx - fabs(tilePtr[t]);
						tileArr[t].empOff[eid] = idx;
						eid++;
					}
				}
			}
		}
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
