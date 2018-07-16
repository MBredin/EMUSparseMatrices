#ifndef Utilities
#define Utilities

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SPARSITY 0.5     // Percentage of sparsity in the matrix
#define RANDOMVALRANGE 9 // Range of random values contained in the matrix (starting from zero)

extern int nnz; // Amount of non-zero values contained in the sparse matrix

/**
 * This methos print all values contained in a matrix, where:
 * 
 * A: Is the matrix to print
 * m: Is the number of rows of A 
 * n: Is the number of columns of A
 **/
void printMatrix(int **A, int m, int n) {
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (c == 0)
                printf("| %d ", A[r][c]);
            else if (c == n - 1)
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
    for (int i = 0; i < length; i++)
    {
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
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            A[r][c] = 0;
        }
    }
}

/**
 * This method takes an array A and initialize all it values to zero, where:
 * 
 * A: Is the array to initialize
 * length: Is the length of A
 **/
void initializeArray(int *A, int length) {
    for (int i = 0; i < length; i++)
    {
        A[i] = 0;
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
    srand(time(NULL)); // Seed rand function

    // Declaration and allocation of memory for matrix A
    int **A = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        A[i] = (int *)malloc(n * sizeof(int));

    nnz = m * n * SPARSITY;                            // Amount of non-zero elements to be stored in A
    printf("Non-zero values to be stored: %d\n", nnz); // Prints nnz
    int randomValue, randomRow, randomCol, r, c;

    // Initialize the matrix with zero values
    initializeMatrix(A, m, n);

    // Fills up matrix with nnz values ranging from one to RANDOMVALRANGE
    for (r = 0; r < nnz; r++)
    {
        randomValue = (rand() % RANDOMVALRANGE) + 1;
        randomRow = rand() % m;
        randomCol = rand() % n;
        A[randomRow][randomCol] = randomValue;
    }

    return A;
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
    initializeArray(x, length); // Initialize array with all values being zero

    for (int i = 0; i < length; i++)
    {
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
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (A[r][c] != 0)
                realNNZ++;
        }
    }

    printf("Non-zero values stored in A: %d \n", realNNZ);

    return realNNZ;
}

#endif