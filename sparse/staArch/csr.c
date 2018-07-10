#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define SANITY 0

//Bool for which matrix to generate (one must be on, the rest must be 0)
#define RANDOMMATRIX 1
#define DIAGMATRIX 0
#define CROSSMATRIX 0

//Constants for random generated matrix
#define SPARSITY 0.5
#define RANDRANGE 10

#define MATDIM 2000

#pragma grainsize = 8

struct timeval tval_before, tval_after, tval_result;

void csr_comp(long **matrix, long *ptr, long *ind, long *data);

void csr_sclr(long ptr[], long ind[], long data[], long x[], long *res);
void csr_seg(long ptr[], long ind[], long data[], long x[], long *res, int size);

int main(){
	srand(time(NULL));
	double rowPer, colPer, randNum;

	//Allocate Memory
	long **matrix = malloc(MATDIM * sizeof(long *));
	for(int i = 0; i < MATDIM; i++)
		matrix[i] = malloc(MATDIM * sizeof(long));

	for(int i = 0; i < MATDIM; i++){
		rowPer = (double)i / (double)MATDIM;
		for(int j = 0; j < MATDIM; j++){
			colPer = (double)j / (double)MATDIM;
			#if RANDOMMATRIX
                                randNum = rand() % RANDRANGE;
                                if(randNum/RANDRANGE >= SPARSITY)
                                        matrix[i][j] = rand() % RANDRANGE;
                                else
                                        matrix[i][j] = 0;
                        #endif
                        #if DIAGMATRIX
                                if(matRow == j)
                                        matrix[i][j] = 2;
                                else if(abs(matRow - j) == 1)
                                        matrix[i][j] = 1;
                                else
                                        matrix[i][j] = 0;
                        #endif

                        #if CROSSMATRIX
                                if((rowPer >= 0.2 && rowPer <= 0.3) || (colPer >= 0.2 && colPer <= 0.3))
                                        matrix[i][j] = 0;
                                else
                                        matrix[i][j] = rand() % RANDRANGE + 1;
                        #endif
		}
	}

	gettimeofday(&tval_after, NULL);
	int nonZero = 0;
	for(int i = 0; i < MATDIM; i++)
		for(int j = 0; j < MATDIM; j++)
			if(matrix[i][j] != 0)
				nonZero++;

	gettimeofday(&tval_before, NULL);
	long *ind = malloc(nonZero * sizeof(long));
	long *data = malloc(nonZero * sizeof(long));
	long *ptr = malloc((MATDIM+1) * sizeof(long));

	csr_comp(matrix, ptr, ind, data);
	timersub(&tval_after, &tval_before, &tval_result);
	long compTime = (long int)tval_result.tv_usec;

	/////////////////
	//SpMV Solution//
	/////////////////
	
	//Initialize the vector to be multiplied
	gettimeofday(&tval_before, NULL);
	long *x = malloc(MATDIM * sizeof(long));
	for(int i = 0; i < MATDIM; i++)
		x[i] = i+1;
	long *res = malloc(MATDIM * sizeof(long));

	csr_sclr(ptr, ind, data, x, res);
	//End Execution timer
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	long execTime = (long int)tval_result.tv_usec;

	//Sanity Check
	#if SANITY
		printf("Original Matrix:\n");
		for(int i = 0; i < MATDIM; i++){
			printf("|");
			for(int j = 0; j < MATDIM; j++)
				printf("%3ld", matrix[i][j]);
			printf("|\n");
		}
		for(int i = 0; i < MATDIM; i++){
			if(i % 2 == 0 && i < 8)
				printf("\n\nNode: %d\n", i/2);
			printf("|");
			for(int j = 0; j < MATDIM; j++)
				printf("%3ld", matrix[i][j]);
			printf("|\n");
		}
		printf("\n\nX: [");
		for(int i = 0; i < MATDIM; i++)
			printf("%3ld", x[i]);
		printf("]\n");
		printf("Data:  [");
		for(int i = 0; i < nonZero; i++)
			printf("%3ld", data[i]);
		printf("]\n");
		printf("Index: [");
		for(int i = 0; i < nonZero; i++)
			printf("%3ld", ind[i]);
		printf("]\n");
		printf("Pointer: [");
		for(int i = 0; i < MATDIM+1; i++)
			printf("%3ld", ptr[i]);
		printf("]\n");
		printf("Solution: [");
		for(int i = 0; i < MATDIM; i++)
			printf("%3ld", res[i]);
		printf("]\n");
	#endif
	printf("Execution Time: %ld\n", execTime);
	printf("Compression Time: %ld\n", compTime);
}

void csr_comp(long **matrix, long *ptr, long *ind, long *data){
	int cnt = 0;
	int locCnt = 0;
	ptr[0] = 0;
	for(int i = 0; i < MATDIM; i++){
		locCnt = 0;
		for(int j = 0; j < MATDIM; j++){
			if(matrix[i][j] != 0){
				data[cnt] = matrix[i][j];
				ind[cnt] = j;
				cnt++;
				locCnt++;
			}
		}
		ptr[i+1] = ptr[i] + locCnt;
	}
}

void csr_sclr(long ptr[], long ind[], long data[], long x[], long *res){
	for(int i = 0; i < MATDIM; i++){
		res[i] = 0;
		for(int j = ptr[i]; j < ptr[i+1] ;j++){
			res[i] += data[j] * x[ind[j]];
		}
	}
}
