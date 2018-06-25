#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 0
#define GENERATEMATEXAMPLE 1
#define SANITY 1

#define OMEGA 4
#define SIGMA 4

struct timeval tval_before, tval_after, tval_result;

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
	for(int i = 0; i < OMEGA; i++){
		if(bitArr[i] == 1)
			arr[i] = arrCpy[i];
		else
			arr[i] += arr[i-1];
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

void csr5_comp(struct Matrix Orig, struct Tile *tileArr, double *rowPrt, double *tilePtr, int *rowPLen, int *tilePLen);

int main(){
	struct Matrix Orig;
	initMat(&Orig,8,8,"Origin");
	int tileCnt = Orig.nonZero / (OMEGA * SIGMA) + 1;
	struct Tile *tileArr = malloc(tileCnt * sizeof(struct Tile));
	int rowPLen, tilePLen;
	double *rowPtr = malloc((Orig.rowM+1)*sizeof(double));
	double *tilePtr = malloc((tileCnt+1)*sizeof(double));
	csr5_comp(Orig, tileArr, rowPtr, tilePtr, &rowPLen, &tilePLen);
	
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
	double *x = malloc(Orig.rowM * sizeof(double));
	for(int i = 0; i < Orig.rowM; i++)
		x[i] = i+1;

	//Sanity Check
	#if SANITY
		print2d(Orig);
		printf("X");
		printLong(x, Orig.rowM);
		printf("\n");
		printf("CSR5 Compressed Matrix\nRow_Pointer");
		printLong(rowPtr, rowPLen);
		printf("Tile_Pointer");
		printLong(tilePtr, tilePLen+1);
		for(int i = 0; i < tileCnt; i++)
			printTile(tileArr[i],i);
	#endif

}



void csr5_comp(struct Matrix Orig, struct Tile *tileArr, double *rowPtr, double *tilePtr, int *rowPLen, int *tilePLen){
	//Initialize all data types
	int tileSize = OMEGA * SIGMA;
	int tileCnt = Orig.nonZero / tileSize + 1;
	*rowPLen = (int)Orig.rowM + 1;
	//Dupilcate Varialbe, get rid of it
	*tilePLen = (int)tileCnt;

	
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

