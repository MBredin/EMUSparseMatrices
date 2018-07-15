#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <memoryweb.h>
#include <cilk.h>

#define ANSI_COLOR_BLUE "\x1b[34m"      // Color blue for specified output
#define ANSI_COLOR_RESET "\x1b[0m"      // Reset color for specified output

#define MATRIXZISE 8                    // Size for each size of the square matrix
#define SPARSITY 0.5                    // Percentage of sparsity in the matrix
#define RANDOMVALRANGE 9                // Range of random values contained in the matrix (starting from zero)
#define NODLETS 4                       // Number of cores to be used for parallel computations

int nnz;                                // Amount of non-zero values contained in the sparse matrix

/**
 * This methos print all values contained in a matrix, where:
 * 
 * A: Is the matrix to print
 * m: Is the number of rows of A 
 * n: Is the number of columns of A
 **/
void printMatrix(int **A, int m, int n) {
    for(int r = 0; r < m; r++) {
        for(int c = 0; c < n; c++) {
            if(c == 0)
                printf("| %d ", A[r][c]);
            else if(c == n-1)
                printf("%d | \n", A[r][c]);
            else
                printf("%d ", A[r][c]);
        }
    }
}

/**
 * This method takes an array A and prints all its values, where:
 * 
 * A: Is the array to print
 * length: Is the number of values of A
 **/
void printArray(int *A, int length) {
    for (int i = 0; i < length; i++) {
        if (length == 1)
            printf("[ %d ] \n", A[i]);
        else if (i == 0)
            printf("[ %d ", A[i]);
        else if (i == (length - 1))
            printf("%d ] \n", A[i]);
        else
            printf("%d ", A[i]);
    }
}

/**
 * This method takes a matrix A and initialize all its values to zero, where:
 * 
 * A: Is the matrix to be initialize
 * m: Is the row size of A
 * n: Is the column size of A
 **/
void initializeMatrix(int **A, int m, int n) {
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            A[r][c] = 0;
        }
    }
}

/**
 * This method generates random values for making a sparse matrix A, where:
 * 
 * A: Is the matrix to fill up
 * m: Is the number of rows of A 
 * n: Is the number of columns of A
 * returns: nnz (number of nonzero values contained in A)
 **/
int **genSparseMatrix(int m, int n) {
    srand(time(NULL));                                          // Seed rand function

    // Declaration and allocation of memory for matrix A
    int **A = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        A[i] = (int *)malloc(n * sizeof(int));

    nnz = m * n * SPARSITY;                                     // Amount of non-zero elements to be stored in A
    printf("Non-zero values to be stored: %d\n", nnz);          // Prints nnz
    int randomValue, randomRow, randomCol, r, c;

    // Initialize the matrix with zero values
    initializeMatrix(A,m,n);
    
    // Fills up matrix with nnz values ranging from one to RANDOMVALRANGE
    for(r = 0; r < nnz; r++) {
        randomValue = (rand() % RANDOMVALRANGE) + 1;
        randomRow = rand() % m;
        randomCol = rand() % n;
        A[randomRow][randomCol] = randomValue;
    } 

    return A;
}

/**
 * This method takes an array A and initialize all it values to zero, where:
 * 
 * A: Is the array to initialize
 * length: Is the length of A
 **/
void initializeArray(int *A, int length) {
    for (int i = 0; i < length; i++) {
        A[i] = 0;
    }
}

/**
 * This method takes an array x and fills it up with random values ranging from 1 to RANDOMVALRANGE, where:
 * 
 * x: Is the array to fill up with random values
 * length: Is the length of x
 **/
int *genDenseVector(int length) {
    srand(time(NULL));

    int *x = (int *)malloc(length * sizeof(int));
    initializeArray(x, length);      // Initialize array with all values being zero

    for(int i = 0; i < length; i++) {
        x[i] = (rand() % RANDOMVALRANGE) + 1;
    }

    return x;
}

/**
 * This method takes sparse matrix A and checks the total non-zero values stored in it (nnz), where:
 * 
 * A: Is the sparse matrix to analyze
 * m: Is the number of rows of A 
 * n: Is the number of columns of A
 * returns: Total nnz
 **/
int checkNNZ(int **A, int m, int n) {
    int realNNZ = 0;
    for(int r = 0; r < m; r++) {
        for(int c  = 0; c < n; c++) {
            if(A[r][c] != 0)
                realNNZ++;
        }
    }

    printf("Non-zero values stored in A: %d \n", realNNZ);

    return realNNZ;
}

/**
 * This method takes matrix A and separates all non-zero values information into three arrays, where:
 * 
 * A: Is the matrix to compress
 * values: Is the array containing all non-zero values of A
 * colIndex: Is the array containing the column indices of the non-zero values in A
 * rowIndex: Is the array containing the row indices of the non-zero values in A
 * m: Is the row size of A
 * n: Is the column size of A
 **/
void compression(int **A, int *values, int *colIndex, int *rowIndex, int m, int n) {
    int i = 0;
    for(int c = 0; c < n; c++) {
        for(int r = 0; r < m; r++) {
            if(A[r][c] != 0){
                values[i] = A[r][c];
                colIndex[i] = c;
                rowIndex[i] = r;
                i++;
            }
        }
    }
    printf("Values: ");
    printArray(values, nnz);
    printf("Col Indices: ");
    printArray(colIndex, nnz);
    printf("Row Indices: ");
    printArray(rowIndex, nnz);
}

/**
 * This method computes SpMV over a range of columns using the compressed information of an sparse matrix, where:
 * 
 * values: Is the array containing all non-zero values of the given sparse matrix
 * colIndex: Is the array containing all the column indices of the nonzero values in the given sparse matrix
 * rowIndex: Is the array containing all the row indices of the nonzero values in the given sparse matrix
 * x: Is the array representing the vector multiplying the given sparse matrix
 * segSolution: is the matrix containing all the sums performed by each nodlet (core).
 * nodlet: Nodlet currently performing the segmented SpMV
 * start: Column index where the sum will start at
 * range: Number of columns that will be part of the segmented sum
 **/
void segmentedSolution(int *values, int *colIndex, int *rowIndex, int *x, int **segSolution, int nodlet, int start, int range) {
    printf("Starting column: %d\n", start);

    for(int i = 0; i < nnz; i++) {
        if(colIndex[i] >= start  && colIndex[i] < (start + range)) {
            segSolution[rowIndex[i]][nodlet] += values[i] * x[colIndex[i]];
        }
    }
}

/**
 * This method takes a matrix containing all the sums performed by each nodlet (core) and add up every row's values, where:
 * 
 * segSolution: is the matrix containing all the sums performed by each nodlet (core).
 * rows: Row length of the segSolution matrix
 **/
int *segmentedSum(int **segSolution, int rows) {
    int *solution = (int *)malloc(rows * sizeof(int));  // Allocation of memory for solution array

    initializeArray(solution, rows);                    // Initialize solution array with all values being zero

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < NODLETS; c++) {
            solution[r] += segSolution[r][c];
        }
    }

    return solution;
}

/**
 * This method computes SpMV parallely using the compressed info of the given sparse matrix, where:
 * values: Is the array containing all non-zero values of the given sparse matrix
 * colIndex: Is the array containing the column indices of the non-zero values in the given sparse matrix
 * rowIndex: Is the array containing the row indices of the non-zero values in the given sparse matrix
 * x: Dense array (vector) multiplying the given sparse matrix
 * rows: Is the row size of the given sparse matrix
 * cols: Is the column size of the given sparse matrix
 **/
int *solutionSpMV(int *values, int *colIndex, int *rowIndex, int *x, int rows, int cols) {
    // Declaration and allocation of memory for matrix segSolution
    int **segSolution = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        segSolution[i] = (int *)malloc(NODLETS * sizeof(int));

    initializeMatrix(segSolution, rows, NODLETS);               // Initialize all values of matrix to zero

    // Computes the size of the range of columns to cover parallely in SpMV
    int colSlice, startingCol;
    if (cols % NODLETS == 0) 
        colSlice = cols / NODLETS;
    else
        colSlice = (cols / NODLETS) + 1;

    printf("Column slice: %d\n", colSlice);

    // Parallel segmented sum
    for(int i = 0; i < NODLETS; i++) {
        startingCol = i * colSlice;
        cilk_spawn segmentedSolution(values,colIndex,rowIndex,x,segSolution,i,startingCol,colSlice);
        cilk_sink;
    }
    printMatrix(segSolution,rows,NODLETS);
    printf("\n");

    return segmentedSum(segSolution, rows);
}

/********************************** MAIN ***********************************/
int main() {
    int m = MATRIXZISE;     // Number of rows in matrix A
    int n = MATRIXZISE;     // Number of columns in matrix A
    printf("Rows: %d \n", m);
    printf("Columns: %d \n", n);

    int **A = genSparseMatrix(m, n);        // Creates sparse matrix A
    printf("Matrix A: \n");
    printMatrix(A, m, n);                   // Prints matrix A

    int *x = genDenseVector(m);             // Creates vector that multiplies matrix A
    printf("Vector x: ");
    printArray(x,m);                        // Prints vector x

    int realNNZ = checkNNZ(A,m,n);
    double sparsePercentage = (realNNZ * 100) / (double)(m*n);
    printf("Sparse percentage: %f \n", sparsePercentage);
    printf("\n");

    // Arrays containing the compressed information of A
    printf("Compressed information of A: \n");
    int *values = (int  *)malloc(nnz * sizeof(int));            // Non-zero values contained in A;
    int *colIndex = (int *)malloc(nnz * sizeof(int));           // Column indices of the non-zero values located in A
    int *rowIndex = (int *)malloc(nnz * sizeof(int));           // Row indicex of the non-zero values located in A

    // Compress all valuable info about A's non-zero values in values, colIndex, and rowIndex
    compression(A, values, colIndex, rowIndex, m, n);                
    printf("\n");

    // Solves SpMV parallely through 4 cores using the compressed information
    int *solution = solutionSpMV(values, colIndex, rowIndex, x, m, n); 
    printf("Solution: ");
    printArray(solution, m);

    return 0;
}