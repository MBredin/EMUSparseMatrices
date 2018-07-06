#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cilk/cilk.h>

#define GENERATEMAT 1
#define SANITY 1

#define ROWM 10
#define COLN 10

#pragma grainsize = 8

struct timeval tval_before, tval_after, tval_result;

void csr_comp(long **matrix, long *ptr, long *ind, long *data);

void csr_sclr(long ptr[], long ind[], long data[], long x[], long *res);
void csr_seg(long ptr[], long ind[], long data[], long x[], long *res, int size);

int main(){
	srand(time(NULL));
	gettimeofday(&tval_before, NULL);
	double tempR, tempC;

	//Allocate Memory
	long **matrix = malloc(ROWM * sizeof(long *));
	for(int i = 0; i < COLN; i++)
		matrix[i] = malloc(COLN * sizeof(long));

	for(int i = 0; i < ROWM; i++){
		tempR = (double)i / (double)ROWM;
		for(int j = 0; j < COLN; j++){
			tempC = (double)j / (double)COLN;
			
			if(i == j)
				matrix[i][j] = rand() % 10 + 1;
			else if(abs(i - j) == 1)
				matrix[i][j] = rand() % 10 + 1;
			
			/*
			if((tempR >= 0.1 && tempR <= 0.4) || (tempC >= 0.1 && tempC <= 0.4))
				matrix[i][j] = 0;
			else
				matrix[i][j] = rand() % 10 + 1;
			*/
		}
	}

	int nonZero = 0;
	for(int i = 0; i < ROWM; i++)
		for(int j = 0; j < COLN; j++)
			if(matrix[i][j] != 0)
				nonZero++;

	long *ind = malloc(nonZero * sizeof(long));
	long *data = malloc(nonZero * sizeof(long));
	long *ptr = malloc((ROWM+1) * sizeof(long));

	csr_comp(matrix, ptr, ind, data);

	/////////////////
	//SpMV Solution//
	/////////////////
	
	//Initialize the vector to be multiplied
	long *x = malloc(ROWM * sizeof(long));
	for(int i = 0; i < ROWM; i++)
		x[i] = i+1;
	long *res = malloc(ROWM * sizeof(long));

	csr_sclr(ptr, ind, data, x, res);
	//End Execution timer
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	long execTime = (long int)tval_result.tv_usec;

	//Sanity Check
	#if SANITY
		printf("Original Matrix:\n");
		for(int i = 0; i < ROWM; i++){
			printf("|");
			for(int j = 0; j < COLN; j++)
				printf("%3ld", matrix[i][j]);
			printf("|\n");
		}
		for(int i = 0; i < ROWM; i++){
			if(i % 2 == 0 && i < 8)
				printf("\n\nNode: %d\n", i/2);
			printf("|");
			for(int j = 0; j < COLN; j++)
				printf("%3ld", matrix[i][j]);
			printf("|\n");
		}
		printf("\n\nX: [");
		for(int i = 0; i < ROWM; i++)
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
		for(int i = 0; i < ROWM+1; i++)
			printf("%3ld", ptr[i]);
		printf("]\n");
		printf("Solution: [");
		for(int i = 0; i < ROWM; i++)
			printf("%3ld", res[i]);
		printf("]\n");
	#endif
	printf("Execution Time: %ld\n", execTime);
}

void csr_comp(long **matrix, long *ptr, long *ind, long *data){
	int cnt = 0;
	int locCnt = 0;
	ptr[0] = 0;
	for(int i = 0; i < ROWM; i++){
		locCnt = 0;
		for(int j = 0; j < COLN; j++){
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
	for(int i = 0; i < ROWM; i++){
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
