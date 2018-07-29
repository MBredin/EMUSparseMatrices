#ifndef SpmvOperations
#define SpmvOperations

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memoryweb.h>
#include <cilk.h>
#include "Utilities.h"

#define NODLETS 8 // Number of cores to be used for parallel computations

/**
 * This method takes matrix A and separates all non-zero values information into three arrays, where:
 * 
 * *nodeID: ID of nodlet being used
 * A: Is the matrix to compress
 * values: Is the array containing all non-zero values of A
 * colIndex: Is the array containing the column indices of the non-zero values in A
 * rowIndex: Is the array containing the row indices of the non-zero values in A
 * m: Is the row size of A
 * colSlice: Is the column size of A
 **/
void compression(long *nodeID, int **A, int **values, int **colIndex, int **rowIndex, int *realNNZ, int m, int colSlice) {
    MIGRATE(&nodeID);

    int nnzIndex = checkNNZ(A, m, colSlice);
    *realNNZ = nnzIndex;

    int *localValues = (int *)malloc(nnzIndex * sizeof(int));
    initializeArray(localValues, nnzIndex);
    int *localColIndex = (int *)malloc(nnzIndex * sizeof(int));
    initializeArray(localColIndex, nnzIndex);
    int *localRowIndex = (int *)malloc(nnzIndex * sizeof(int));
    initializeArray(localRowIndex, nnzIndex);

    int i = 0;
    for(int c = 0; c < colSlice; c++) {
        for(int r = 0; r < m; r++) {
            if(A[r][c] != 0){
                localValues[i] = A[r][c];
                localColIndex[i] = c + (*nodeID * colSlice);
                localRowIndex[i] = r;
                i++;
            }
        }
    }

    *values = localValues;
    *colIndex = localColIndex;
    *rowIndex = localRowIndex;
    // printf("Values: ");
    // printArray(values, nnz);
    // printf("Col Indices: ");
    // printArray(colIndex, nnz);
    // printf("Row Indices: ");
    // printArray(rowIndex, nnz);
}

/**
 * This method computes SpMV over a range of columns using the compressed information of an sparse matrix, where:
 * 
 * *nodeID: ID of nodlet being used
 * values: Is the array containing all non-zero values of the given sparse matrix
 * colIndex: Is the array containing all the column indices of the nonzero values in the given sparse matrix
 * rowIndex: Is the array containing all the row indices of the nonzero values in the given sparse matrix
 * x: Is the array representing the vector multiplying the given sparse matrix
 * segSolution: is the matrix containing all the sums performed by each nodlet (core).
 * rows: Row size of segSolution matrix 
 * realNNZ: Real number of non-zero values within values
 **/
void segmentedSolution(long *nodeID, int *values, int *colIndex, int *rowIndex, long *x, int **segSolution, int rows, int realNNZ) {
    MIGRATE(&nodeID);

    int *segLocalSolution = (int *)malloc(rows * sizeof(int));
    initializeArray(segLocalSolution, rows);

    for(int i = 0; i < realNNZ; i++) {
        segLocalSolution[rowIndex[i]] += values[i] * x[colIndex[i]];
        
    }
    //printArray(segLocalSolution, rows);


    *segSolution = segLocalSolution;
}

/**
 * This method takes a matrix containing all the sums performed by each nodlet (core) and add up every row's values, where:
 * 
 * segSolution: is the matrix containing all the sums performed by each nodlet (core).
 * rows: Row length of the segSolution matrix
 **/
int *segmentedSum(long *nodeID, int *solution, int **segSolution, int rows, long thread) {
    //MIGRATE(&nodeID);

    for(int r = 0; r < rows; r++) {
        solution[r] += segSolution[r][thread];
    }

    return solution;
}

/**
 * This method computes SpMV parallely using the compressed info of the given sparse matrix, where:
 * 
 * *nodes: ID of nodlet being used
 * segSolution: is the matrix containing all the sums performed by each nodlet (core).
 * values: Is the array containing all non-zero values of the given sparse matrix
 * colIndex: Is the array containing the column indices of the non-zero values in the given sparse matrix
 * rowIndex: Is the array containing the row indices of the non-zero values in the given sparse matrix
 * x: Dense array (vector) multiplying the given sparse matrix
 * rows: Is the row size of the given sparse matrix
 * colSlice: Is the column size of the given sparse matrix
 **/
void solutionSpMV(long *nodes, int **segSolution, int **values, int **colIndex, int **rowIndex, int *realNNZ, long *x, int rows, int colSlice, long threads) {
    // Parallel segmented sum

    for (int i = 0; i < threads; i++) {        
        cilk_spawn segmentedSolution(&nodes[i], values[i], colIndex[i], rowIndex[i], x, &segSolution[i], rows, realNNZ[i]);
    }
    cilk_sync;

    // printMatrix(segSolution,rows,threads);
    // printf("\n");
}

#endif