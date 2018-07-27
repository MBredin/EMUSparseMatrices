#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>
//#include "readMat.c"

//Print matrix operations and solution
#define SANITY 1

//SpMV = 1, SpMM = 0
#define SPMV 1

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//System Specs
#define NODELETS 8
#define THREADS 4
#define MATDIM 20

#define SOLUTIONTIME 0

//Constants for random generated matrix
#define SPARSITY 0.5
#define RANDRANGE 10

//Replicate vector across each nodelet
replicated long *repx;

//Set values in vector to be multiplied
void fill_x(void *ptr, long node){
	long *gto = (long *)ptr;

	for(int i = 0; i < MATDIM; i++)
		gto[i] = i+1;
}

//Allocate memory for vector
long *alloc_x(void){
	long *mr = mw_mallocrepl(MATDIM * sizeof(long));
	mw_replicated_init_generic(mr, fill_x);

	return mr;
}

long **GenerateMatrix(void);
long **GenerateSplitMatrix(long *nodeId);
void cooCompression(long *nodeId, long **mat, long **valPtr, long **colPtr, long **rowPtr, int *nz);
void cooCompressionSolid(long **mat, long **valPtr, long **colPtr, long **rowPtr, int *nz);
void cooSpMM(long *nodeId, long **mat1, long **mat2);
void cooSpMV(long *nodeId, long **emuRows);

int main(){
	#if SPMV
		long *tempX = alloc_x();
		mw_replicated_init((long *)&repx, (long)tempX);
	#endif
	
	long *nodes = mw_malloc1dlong(NODELETS * sizeof(long *));
	for(int i = 0; i < NODELETS; i++)
		nodes[i] = i;	
	
	long **mat1[NODELETS];
	//Matrix Generation
	for(int i = 0; i < NODELETS; i++){
		mat1[i] = cilk_spawn GenerateSplitMatrix(&nodes[i]);
	}
	cilk_sync;

	long **mat2[NODELETS];
	//Matrix Generation
	for(int i = 0; i < NODELETS; i++){
		mat2[i] = GenerateMatrix();
	}

/*
	//Matrix Compression
	//starttiming();
	#if SOLUTIONTIME
	long *solution[NODELETS];
	#endif
	////starttiming();
	#if SPMV
	for(int i = 0; i < NODELETS; i++){
		#if SOLUTIONTIME
		solution[i] = cilk_spawn cooSpMV(&nodes[i], mat1[i]); //solution[i] = 
		#else
		cilk_spawn cooSpMV(&nodes[i], mat1[i]);
		#endif
	}
	cilk_sync;
	#else	
	for(int i = 0; i < NODELETS; i++){
		#if SOLUTIONTIME
		solution[i] = cilk_spawn cooSpMM(&nodes[i], mat1[i], mat2[i]); //solution[i] = 
		#else
		cilk_spawn cooSpMM(&nodes[i], mat1[i], mat2[i]);
		#endif
	}
	cilk_sync;
	#endif
*/
	//Sanity Check
	#if SANITY
		int nodeRows = MATDIM / NODELETS;
		int cnt = 0;
		//Print Starting Matrix
		printf("Mat 1:\n");
		for(int i = 0; i < NODELETS; i++){
			if(i == NODELETS-1)
				nodeRows += MATDIM % NODELETS;
			for(int j = 0; j < nodeRows; j++){
				printf("|");
				for(int k = 0; k < MATDIM; k++){
					printf("%3ld", mat1[i][j][k]);
					if(mat1[i][j][k] != 0)
						cnt++;
				}
				printf("|\n");
			}
		}
		printf("DENSITY: %d%%\n", (int)(100.0 * (double)cnt/(MATDIM*MATDIM)));
		nodeRows = MATDIM / NODELETS;
		cnt = 0;
		//Print Second Matrix
		printf("mat 2:\n");
		for(int i = 0; i < NODELETS; i++){
			if(i == NODELETS-1)
				nodeRows += MATDIM % NODELETS;
			for(int j = 0; j < nodeRows; j++){
				printf("|");
				for(int k = 0; k < MATDIM; k++){
					printf("%3ld", mat2[i][j][k]);
					if(mat2[i][j][k] != 0)
						cnt++;
				}
				printf("|\n");
			}
		}
		printf("DENSITY: %d%%\n", (int)(100.0 * (double)cnt/(MATDIM*MATDIM)));
		#if SpMV
			//Print Solution
			nodeRows = MATDIM / NODELETS;
			for(int i = 0; i < NODELETS; i++){
				if(i == NODELETS-1)
					nodeRows += MATDIM % NODELETS;
				for(int j = 0; j < nodeRows; j++)
					printf("|%ld|\n", solution[i][j]);
			}
		#else
			//Matrix Solution	
		#endif
	#endif
}

long **GenerateMatrix(void){
	//Allocate Memory
	long **emuRows = malloc(MATDIM * sizeof(long *));
	for(int j = 0; j < nodeRows; j++){
		emuRows[j] = malloc(MATDIM * sizeof(long));
	}
		
	//int temp = *nodeId * rowSplit;
	for(int i = 0; i < MATDIM; i++){
		rowPer = (double)i / (double)MATDIM;
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)MATDIM;
			#if RANDOMMATRIX
				randNum = rand() % RANDRANGE;
				if(randNum/RANDRANGE >= SPARSITY)
					emuRows[i][j] = rand() % RANDRANGE;
				else
					emuRows[i][j] = 0;
			#endif
			#if DIAGMATRIX
				if(matRow == j)
					emuRows[i][j] = 2;
				else if(abs(matRow - j) == 1)
					emuRows[i][j] = 1;
				else
					emuRows[i][j] = 0;
			#endif
			
			#if CROSSMATRIX
				if((rowPer >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
					emuRows[i][j] = 0;
	 			else
 					emuRows[i][j] = rand() % 10 + 1;
			#endif
			
		}
	}
	return(emuRows);
}

long **GenerateSplitMatrix(long *nodeId){
	MIGRATE(&nodeId);
	
	////////////////////////////////////
	/////Allocate and Define Matrix/////
	////////////////////////////////////
	int rowSplit = MATDIM / NODELETS;
	int nodeRows = rowSplit;
	double rowPer, colPer, matRow, randNum;
	if(*nodeId == NODELETS-1)
		nodeRows += MATDIM % NODELETS;
	long **emuRows = malloc(nodeRows * sizeof(long *));

	//Allocate memory for given node
	for(int j = 0; j < nodeRows; j++){
		emuRows[j] = malloc(MATDIM * sizeof(long));
	}
		
	//int temp = *nodeId * rowSplit;
	for(int i = 0; i < nodeRows; i++){
		matRow = i + (*nodeId * rowSplit);
		rowPer = (double)(matRow) / (double)MATDIM;
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)MATDIM;
			#if RANDOMMATRIX
				randNum = rand() % RANDRANGE;
				if(randNum/RANDRANGE >= SPARSITY)
					emuRows[i][j] = rand() % RANDRANGE;
				else
					emuRows[i][j] = 0;
			#endif
			#if DIAGMATRIX
				if(matRow == j)
					emuRows[i][j] = 2;
				else if(abs(matRow - j) == 1)
					emuRows[i][j] = 1;
				else
					emuRows[i][j] = 0;
			#endif
			
			#if CROSSMATRIX
				if((rowPer >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
					emuRows[i][j] = 0;
	 			else
 					emuRows[i][j] = rand() % 10 + 1;
			#endif
			
		}
	}
	return(emuRows);
}

void cooSpMV(long *nodeId, long **emuRows){
	/////////////////////////////////////
	/////////////COMPRESSION/////////////
	/////////////////////////////////////
	int rowSplit = MATDIM / NODELETS;
	int nodeRows = rowSplit;
	if(*nodeId == NODELETS-1)
		nodeRows += MATDIM % NODELETS;
	long cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){
				cnt++;
			}
		}
	}
	long value[cnt];
	long colInd[cnt];
	long rowInd[cnt];

	cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(emuRows[i][j] != 0){
				value[cnt] = emuRows[i][j];
				colInd[cnt] = j;	
				rowInd[cnt] = i;
				cnt++;
			}
		}
	}
	#if SOLUTIONTIME
		//Solution Section
		long *loc_sol = malloc(nodeRows * sizeof(long));
		for(int i = 0; i < nodeRows; i++)
			loc_sol[i] = 0;
		for(int i = 0; i < nodeRows; i++)
			loc_sol[rowInd[i]] += value[i] * repx[colInd[i]];
		return(loc_sol);
	#endif
}

void cooSpMM(long *nodeId, long **mat1, long **mat2){
	long *mat1_value;
	long *mat1_colInd;
	long *mat1_rowInd;
	int mat1_nz;

	cooCompression(nodeId, mat1, &mat1_value, &mat1_colInd, &mat1_rowInd, &mat1_nz);

	#if SANITY
		if(*nodeId == 0){
			printf("NonZero mat1: %d  NonZero mat2: %d\n", mat1_nz, mat2_nz);
			printf("Node: %ld\n", *nodeId);
			printf("mat1 value: [");
			for(int i = 0; i < mat1_nz; i++)
				printf("%3ld", mat1_value[i]);
			printf("]   ");
			printf("mat1 rowInd: [");
			for(int i = 0; i < mat1_nz; i++)
				printf("%3ld", mat1_rowInd[i]);
			printf("]   ");
			printf("mat1 value: [");
			for(int i = 0; i < mat1_nz; i++)
				printf("%3ld", mat1_colInd[i]);
			printf("]\n\n");
			printf("mat2 value: [");
			for(int i = 0; i < mat2_nz; i++)
				printf("%3ld", mat2_value[i]);
			printf("]   ");
			printf("rowInd: [");
			for(int i = 0; i < mat2_nz; i++)
				printf("%3ld", mat2_rowInd[i]);
			printf("]   ");
			printf("value: [");
			for(int i = 0; i < mat2_nz; i++)
				printf("%3ld", mat2_colInd[i]);
			printf("]\n\n");
		}
	#endif

	#if SOLUTIONTIME
		//Solution Section
	#endif
}

void cooCompression(long *nodeId, long **mat, long **valPtr, long **colPtr, long **rowPtr, int *nz){
	int rowSplit = MATDIM / NODELETS;
	int nodeRows = rowSplit;
	if(*nodeId == NODELETS-1)
		nodeRows += MATDIM % NODELETS;
	int cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(mat[i][j] != 0){
				cnt++;
			}
		}
	}
	*valPtr = malloc(cnt * sizeof(long));
	*colPtr = malloc(cnt * sizeof(long));
	*rowPtr = malloc(cnt * sizeof(long));

	cnt = 0;
	for(int i = 0; i < nodeRows; i++){
		for(int j = 0; j < MATDIM; j++){
			if(mat[i][j] != 0){
				(*valPtr)[cnt] = mat[i][j];
				(*colPtr)[cnt] = j;	
				(*rowPtr)[cnt] = i;
				cnt++;
			}
		}
	}

	*nz = cnt;
}

void cooCompressionSolid(long **mat, long **valPtr, long **colPtr, long **rowPtr, int *nz){
	int cnt = 0;
	for(int i = 0; i < MATDIM; i++){
		for(int j = 0; j < MATDIM; j++){
			if(mat[i][j] != 0){
				cnt++;
			}
		}
	}
	*valPtr = malloc(cnt * sizeof(long));
	*colPtr = malloc(cnt * sizeof(long));
	*rowPtr = malloc(cnt * sizeof(long));

	cnt = 0;
	for(int i = 0; i < MATDIM; i++){
		for(int j = 0; j < MATDIM; j++){
			if(mat[i][j] != 0){
				(*valPtr)[cnt] = mat[i][j];
				(*colPtr)[cnt] = j;	
				(*rowPtr)[cnt] = i;
				cnt++;
			}
		}
	}

	*nz = cnt;
}
