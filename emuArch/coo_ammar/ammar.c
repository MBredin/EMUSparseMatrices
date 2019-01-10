#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <memoryweb.h>
#include <sys/time.h>
#include <cilk.h>
#include <distributed.h>

#include "ammar.h"

//For printing The Matrix, Vector and Result
static int PRINT = 0;

//For Timing
static int TIME = 0;

double **createMatrix();
double *createVector();
char** str_split(char* a_str, const char a_delim);
double ** read_mat (const char* file_name);
void cooCompress(double **matrix, double *vector, int threads);
void cooMultiply(double *vector, int threads);
void insert(int row, int column, double value, void * localpointer);
element* find(int index);

static list nonZeroElements;
static int sizeRow;
static int sizeCol;
static double *sum;
static char * FILENAME;

unsigned long start, end, soltime, comptime;


int main(int argc, char** argv){
	long threads = 0;
	if(argc != 6){
		printf("Command Line Input Error\n");
		exit(1);
	}
	else{
		threads = atoi(argv[1]);
		sizeRow = atoi(argv[2]);
		sizeCol = atoi(argv[3]);
		PRINT = atoi(argv[4]);
		TIME = atoi(argv[5]);
		//if(sizeRow == 0 && sizeCol == 0) {
			//FILENAME = atoi(argv[6]);
		//}
	}


	double **matrix;
	if(sizeRow == 0 && sizeCol == 0){
		matrix = read_mat("494_bus.mtx");
		sizeCol = 3;
		sizeRow = 1081;
	} else{
		matrix = createMatrix();
	}
	double *vector = createVector();

	nonZeroElements.size = 0;

	if(TIME == 1){
		starttiming();
	}

	start = clock();
	cooCompress(matrix, vector, threads);
	end = clock();
	comptime = end - start;
	printf("Compression cycles are %d\n", comptime);

	sum = mw_malloc1dlong(sizeRow);
	cilk_for(int i = 0; i < sizeRow; i++){
		sum[i] = 0.0;
	}

	start = clock();
	cooMultiply(vector, threads);
	end = clock();
	soltime = end - start;
	printf("Solution cycles are %d\n", soltime);

	if(PRINT==1){
		printf("\nResult:_\n");
		int k = 0;
		while (k < sizeRow) {
			printf("| %G |\n",sum[k]);
			k++;
		}
		printf("\n");
	}

}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

double ** read_mat (const char* file_name)
{
	double **matrix = (double **) mw_malloc2d(1081, 3*sizeof(double));
  FILE* file = fopen (file_name, "r");
	if(file == NULL){
		printf("Error reading file\n");
		exit(1);
	}

	char * line = NULL;
  size_t len = 0;
	ssize_t read;
	char ** temp;
	int j = 0;

	while ((read = getline(&line, &len, file)) != -1) {
			temp = str_split(line, ' ');
			for(int i = 0; i < 3; i++){
				matrix[j][i] = atof(temp[i]);
			}
			j++;
  }
  fclose (file);
	return matrix;
}

double **createMatrix(){
	//Generating Matrix
	double **matrix = (double **) mw_malloc2d(sizeRow, sizeCol*sizeof(double));

	if (PRINT==1) {
		printf("Matrix:_\n");
	}

	for(int i = 0; i < sizeRow; i++){

		if (PRINT==1){
			printf("|");
		}

		for(int j = 0; j < sizeCol; j++){
			srand (time(NULL));
			matrix[i][j] = rand()%3+j+0.2;
			//printf("%d\n",NODE_ID());
			if (PRINT==1){
				printf(" %G ", matrix[i][j]);
			}

		}
		if (PRINT==1) {
			printf("|\n");
		}

	}

	if (PRINT==1){
		printf("\n");
	}

	return matrix;
}

double *createVector(){
	//Generating Vector
	double *vector = mw_malloc1dlong(sizeCol);
	if (PRINT==1){
		printf("Vector:_\n");
	}

	for(int i = 0; i < sizeCol; i++){
		srand(time(NULL));
		vector[i] = rand()%3+i+1;
		if(PRINT==1){
			printf("|");
			printf(" %G ", vector[i]);
			printf("|\n");
		}
	}

	if (PRINT==1){
		printf("\n");
	}

	return vector;
}

void cooCompress(double **matrix, double *vector, int threads){
	int grainT = ((sizeRow*sizeCol)/threads)==0?1:((sizeRow*sizeCol)/threads);
	//Start of Compression
	#pragma cilk grainsize = grainT
	cilk_for(int k = 0; k < (sizeRow*sizeCol); k++){
		matrix[k%sizeRow][k/sizeRow] != 0?insert(k%sizeRow,k/sizeRow,matrix[k%sizeRow][k/sizeRow],&matrix[k%sizeRow][k/sizeRow]):NULL;
	}
	//End of Compression
}

void cooMultiply(double *vector, int threads){
	int length = nonZeroElements.size;
	int grainL = (length/threads)==0?1:(length/threads);
	//Start of Solution
	#pragma cilk grainsize = grainL
	cilk_for(int i = 0; i < length; ++i) {
		element* tempo = find(i);
		sum[tempo->row] += tempo?tempo->value*vector[tempo->column]:0;
	}
	//End of Solution
}

void insert(int row, int column, double value, void * localpointer){
	//Insertion into linked list
	element * temp = mw_localmalloc(sizeof(element), &localpointer);
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
