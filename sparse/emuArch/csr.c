#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>

#define GENERATEMAT 1
#define GENERATEMATEXAMPLE 0
#define SANITY 0

#define NODELETS 8

struct timeval tval_before, tval_after, tval_result;

struct Matrix{
	long **mat;
	char name[7];
	int rowM;
	int colN;
	int matSize;
	int nonZero;
};


void initMat(struct Matrix *m, int M, int N, char varName[7]){
	m -> mat = (long **)malloc(M * sizeof(long *));
	for(int i = 0; i < M; i++)
		m -> mat[i] = malloc(N * sizeof(long));
	//m -> mat = (long *)malloc(M*N*sizeof(long));
	m -> rowM = M;
	m -> colN = N;
	m -> matSize = M * N;
	for(int i = 0; i < 7; i++)
		m -> name[i] = varName[i];
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
			m -> mat[i][j] = 0;
	#if GENERATEMAT
		int temp = 1;
		for(int i = 0; i < M; i++){
			for(int j = 0; j < N; j++){
				//*(m->mat+i*N+j) = i*N+j;
				if(i == j){
					m->mat[i][j] = 2;
					temp++;
				}
				else if(abs(i - j) == 1){
					m->mat[i][j] = 1;
					temp++;
				}
			}
		}
	#endif
	#if GENERATEMATEXAMPLE
		m->mat[0][0] = 1;
		m->mat[0][2] = 2;
		m->mat[0][3] = 3;
		m->mat[0][6] = 4;
		m->mat[0][7] = 5;
		m->mat[1][1] = 1;
		m->mat[1][3] = 2;
		m->mat[3][0] = 1;
		m->mat[3][1] = 2;
		m->mat[3][2] = 3;
		m->mat[3][3] = 4;
		m->mat[3][4] = 5;
		m->mat[3][6] = 6;
		m->mat[3][7] = 7;
		m->mat[4][1] = 1;
		m->mat[4][3] = 2;
		m->mat[4][5] = 3;
		m->mat[5][0] = 1;
		m->mat[5][1] = 2;
		m->mat[6][1] = 1;
		m->mat[6][2] = 2;
		m->mat[6][3] = 3;
		m->mat[6][4] = 4;
		m->mat[6][5] = 5;
		m->mat[6][6] = 6;
		m->mat[6][7] = 7;
		m->mat[7][0] = 1;
		m->mat[7][1] = 2;
		m->mat[7][2] = 3;
		m->mat[7][3] = 4;
		m->mat[7][4] = 5;
		m->mat[7][5] = 6;
		m->mat[7][6] = 7;
		m->mat[7][7] = 8;
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
		printf("%5ld", arr[i]);
	printf("]");
}

void csr_comp(long *orig, long *ptr, long *x, long *csr_res, int size);

int main(){
	struct Matrix Orig;
	initMat(&Orig,8,8,"Origin");

	//Rearrange Matrix in memory
	//starttiming();
	/*
	long *data = mw_malloc2d()
	for(int i = 0; i < 100; i++){
		if(orig[i] != 0){
			loc_data[cnt] = orig[i];
			loc_ind[cnt] = i;
			cnt++;
		}
	}
	*ptr = cnt;

	csr_res[rowId] = 0;
	for(int i = 0; i < cnt; i++)
		csr_res[rowId] += loc_data[i] * x[loc_ind[i]];
	*/
	
	long *nodes = malloc(NODELETS * sizeof(long *));
	//long *nodes = mw_malloc1dlong(NODELETS);
	long *emuRows[Orig.rowM];
	for(int i = 0; i < Orig.rowM; i++){
		emuRows[i] = mw_localmalloc(Orig.colN * sizeof(long), &nodes[i%NODELETS]);
		for(int j = 0; j < Orig.colN; j++){
			//emuRows[i][j] = 0;
			//if(i == j){
			//	emuRows[i][j] = 2;
			//}
			//else if(abs(i - j) == 1){
			//	emuRows[i][j] = 1;
			//}
			emuRows[i][j] = Orig.mat[i][j];
		}
	}
	
	
	//Initialize the vector to be multiplied (replicated across each node)
	long x[Orig.rowM];
	for(int j = 0; j < Orig.rowM; j++)
		mw_replicated_init(&x[j], j+1);

	//Remotely update the row_ptr (May not need since each row is seperated and empty rows are not dropped)
	long *csr_ptr = malloc((Orig.rowM+1) * sizeof(long));
	csr_ptr[0] = 0;
	//initialize Resolution Array (Update remotely from nodes)
	long *csr_res = malloc(Orig.rowM * sizeof(long));

	//Split the Original Matrix by its rows, allocating different rows to each node
	
	starttiming();
	for(int i = 0; i < Orig.rowM; i++){
		cilk_spawn csr_comp(emuRows[i], &csr_ptr[i+1], x, &csr_res[i], Orig.colN);
	}
	cilk_sync;
	


	/////////////////
	//SpMV Solution//
	/////////////////

//	csr_sclr(csr_ptr, csr_ind, csr_data, x , csr_res, Orig.rowM);

	//Sanity Check
	#if SANITY
		//print2d(Orig);
		//printf("X = ");
		//printf("Emu Matrix");
		//for(int i = 0; i < Orig.rowM; i++){
		//	printf("| ");
		//	for(int j = 0; j < Orig.colN; j++)
		//		printf("%3ld",emuRows[i][j]);
		//	printf(" |\n");
		//}
		//printLong(x, Orig.rowM);
		//printf("\nData = ");
		//printLong(csr_data, Orig.nonZero);
		//printf("\nIndex = ");
		//printLong(csr_ind, Orig.nonZero);
		//printf("\nPointer = ");
		//printLong(csr_ptr, Orig.rowM+1);
		printf("\n\nSolution:");
		printLong(csr_res, Orig.rowM);
	#endif
	//printf("Compression Time: %ld\n", compTime);
	//printf("Execution Time: %ld\n", execTime);

}

void csr_comp(long *orig, long *ptr, long *x, long *csr_res, int size){
	long cnt = 0;
	for(int i = 0; i < size; i++)
		if(orig[i] != 0)
			cnt++;
	long *loc_data = malloc(cnt * sizeof(long));
	long *loc_ind = malloc(cnt * sizeof(long));
	
	for(int i = 0; i < cnt; i++){
		if(orig[i] != 0){
			loc_data[cnt] = orig[i];
			loc_ind[cnt] = i;
		}
	}

	long loc_res = 0;
	for(int i = 0; i < cnt; i++)
		loc_res += loc_data[i] * x[loc_ind[i]];
}

