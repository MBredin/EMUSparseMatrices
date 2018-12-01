#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>

#include "ammar.h"

int **createMatrix();
int *createVector();
int *Multiply(int **matrix, int *vector);
int *cooMultiply(int **matrix, int *vector, int threads);
void insert(int row, int column, int value);
int first_loop(int j, element *temp, int *vector);

static list nonZeroElements;
static int sizeRow;
static int sizeCol;
static int takenRows;
static int takenCols;

static clock_t start, end;
static double cpu_time_used;


int main(int argc, char** argv){
	long threads = 0;
	if(argc != 2){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		threads = atoi(argv[1]);
	}

	sizeRow = 10;
	sizeCol = 6;

	takenRows = sizeRow/threads;
	takenCols = sizeCol/threads;

	int **matrix = /*cilk_spawn*/ createMatrix();
	int *vector = createVector();
	
	//cilk_sync;
	
	nonZeroElements.size = 0;

	start = clock();
	cooMultiply(matrix, vector, threads);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("COO multiply function took %f\n", cpu_time_used);

}

int **createMatrix(){
	int **matrix = malloc(sizeRow*sizeof(int*));

	//printf("Matrix:_\n");

	for(int i = 0; i < sizeRow; i++){
		matrix[i] = malloc(sizeCol*sizeof(int));
		//printf("|");
		for(int j = 0; j < sizeCol; j++){
			matrix[i][j] = rand()%3+j;
			//printf(" %d ", matrix[i][j]);
		}
		//printf("|\n");
	}

	//printf("\n");
	return matrix;
}

int *createVector(){
	int *vector = malloc(sizeCol*sizeof(int));

	//printf("Vector:_\n");

	for(int i = 0; i < sizeCol; i++){
		//printf("|");
		vector[i] = rand()%3+i+1;
		//printf(" %d ", vector[i]);
		//printf("|\n");
	}

	//printf("\n");
	return vector;
}

int *cooMultiply(int **matrix, int *vector, int threads){
	int *result = malloc(sizeRow*sizeof(int));
	for(int i = 0; i < sizeRow; i++){
		for(int j = 0; j < sizeCol; j++){
			if(matrix[i][j] != 0){
				insert(i,j,matrix[i][j]);
			}
		}
	}
	int length = nonZeroElements.size;
	printf("Non Zero elements are: %d\n", length);
	element *temp = nonZeroElements.head;
	int *sum = malloc(sizeRow*sizeof(int));
	cilk_for(int i = 0; i < sizeRow; i++){
		sum[i] = 0;
	}	
	cilk_for(int i = 0; i < (sizeRow*sizeCol); ++i) {
		if(temp){
			temp->value = temp->value*vector[temp->column];
			temp = temp->next;
		}
	}
	temp = nonZeroElements.head;
	cilk_for(int i = 0; i < (sizeRow*sizeCol); ++i) {
		if(temp){
			sum[temp->row] = sum[temp->row] + temp->value;
			temp = temp->next;
		}
	}

	//printf("\nResult:_\n");
	int k = 0;
	while (k < sizeRow) {
		//printf("| %d |\n",sum[k]);
		k++;
	}
	//printf("\n");
}

void insert(int row, int column, int value){
	element * temp = malloc(sizeof(element));
	temp->row = row;
	temp->column = column;
	temp->value = value;
	temp->next = NULL;


	if(nonZeroElements.size == 0){
		temp->prev = NULL;
		nonZeroElements.head = temp;
		nonZeroElements.tail = temp;
	}
	else {
		nonZeroElements.tail->next = temp;
		temp->prev = nonZeroElements.tail;
		nonZeroElements.tail = temp;
	}
	nonZeroElements.size++;
}
