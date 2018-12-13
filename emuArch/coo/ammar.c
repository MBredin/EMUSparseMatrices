#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>

#include "ammar.h"

//For printing The Matrix, Vector and Result
#define PRINT 0

int **createMatrix();
int *createVector();
void cooCompress(int **matrix, int *vector, int threads);
void cooMultiply(int *vector, int threads);
void insert(int row, int column, int value);
element* find(int index);  

static list nonZeroElements;
static int sizeRow;
static int sizeCol;
static int *sum;

unsigned long start, end, soltime, comptime;


int main(int argc, char** argv){
	long threads = 0;
	if(argc != 2){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		threads = atoi(argv[1]);
	}

	sizeRow = 16;
	sizeCol = 8;

	int **matrix = createMatrix();
	int *vector = createVector();
	
	nonZeroElements.size = 0;
	
	starttiming();
	
	start = clock();
	cooCompress(matrix, vector, threads);
	end = clock();
	comptime = end - start;
	printf("Compression cycles are %f\n", comptime);

	sum = mw_malloc1dlong(sizeRow*sizeof(int));
	cilk_for(int i = 0; i < sizeRow; i++){
		sum[i] = 0;
	}

	start = clock();
	cooMultiply(vector, threads);
	end = clock();
	soltime = end - start;
	printf("Solution cycles are %f\n", soltime);
	
	if(PRINT){
		printf("\nResult:_\n");
		int k = 0;
		while (k < sizeRow) {
			printf("| %d |\n",sum[k]);
			k++;
		}
		printf("\n");
	}

}

int **createMatrix(){
	//Generating Matrix
	int **matrix = mw_malloc2d(sizeRow*sizeof(int*), sizeCol*sizeof(int));

	if (PRINT) {
		printf("Matrix:_\n");
	}

	for(int i = 0; i < sizeRow; i++){
		
		if (PRINT){			
			printf("|");
		}
		
		for(int j = 0; j < sizeCol; j++){
			matrix[i][j] = rand()%3+j;
			if (PRINT){			
				printf(" %d ", matrix[i][j]);
			}
		
		}
		if (PRINT) {			
			printf("|\n");
		}
	
	}

	if (PRINT){	
		printf("\n");
	}
	
	return matrix;
}

int *createVector(){
	//Generating Vector
	int *vector = mw_malloc1dlong(sizeCol*sizeof(int));
	if (PRINT){
		printf("Vector:_\n");
	}

	for(int i = 0; i < sizeCol; i++){		
		vector[i] = rand()%3+i+1;
		if(PRINT){
			printf("|");		
			printf(" %d ", vector[i]);
			printf("|\n");
		}
	}

	if (PRINT){
		printf("\n");
	}
	
	return vector;
}

void cooCompress(int **matrix, int *vector, int threads){
	int grainT = ((sizeRow*sizeCol)/threads)==0?1:((sizeRow*sizeCol)/threads);
	//Start of Compression
	#pragma cilk grainsize = grainT
	cilk_for(int k = 0; k < (sizeRow*sizeCol); k++){
		matrix[k%sizeRow][k/sizeRow] != 0?insert(k%sizeRow,k/sizeRow,matrix[k%sizeRow][k/sizeRow]):NULL;
	}
	//End of Compression
}

void cooMultiply(int *vector, int threads){
	int length = nonZeroElements.size;
	int grainL = (length/threads)==0?1:(length/threads);
	//Start of Solution
	#pragma cilk grainsize = grainL	
	cilk_for(int i = 0; i < length; ++i) {
		sum[find(i)->row] += find(i)?find(i)->value*vector[find(i)->column]:0;
	}
	//End of Solution	
}

void insert(int row, int column, int value){
	//Insertion into linked list
	element * temp = mw_malloc1dlong(sizeof(element));
	temp->row = row;
	temp->column = column;
	temp->value = value;
	temp->next = NULL;
	if(nonZeroElements.size == 0){
		temp->prev = NULL;
		temp->index = 0;
		nonZeroElements.head = temp;
		nonZeroElements.tail = temp;
	}
	else {	
		nonZeroElements.tail->next = temp;
		temp->index = nonZeroElements.tail->index+1;
		temp->prev = nonZeroElements.tail;
		nonZeroElements.tail = temp;
	}
	nonZeroElements.size++;
}

element* find(int index){
	element *temp = nonZeroElements.head;
	while(temp) {
		if(temp->index == index){
			return temp;
		} else {
			temp = temp->next;
		}
	}
	return NULL;
}
