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
 * A: Is the matrix to compress
 * values: Is the array containing all non-zero values of A
 * colIndex: Is the array containing the column indices of the non-zero values in A
 * rowIndex: Is the array containing the row indices of the non-zero values in A
 * m: Is the row size of A
 * n: Is the column size of A
 **/
void compression(long *nodeID, int **A, int *values, int *colIndex, int *rowIndex, int m, int colSlice) {
    int i = 0;
    for(int c = 0; c < colSlice; c++) {
        for(int r = 0; r < m; r++) {
            if(A[r][c] != 0){
                values[i] = A[r][c];
                colIndex[i] = c + (*nodeID * colSlice);
                rowIndex[i] = r;
                i++;
            }
        }
    }
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
 * values: Is the array containing all non-zero values of the given sparse matrix
 * colIndex: Is the array containing all the column indices of the nonzero values in the given sparse matrix
 * rowIndex: Is the array containing all the row indices of the nonzero values in the given sparse matrix
 * x: Is the array representing the vector multiplying the given sparse matrix
 * segSolution: is the matrix containing all the sums performed by each nodlet (core).
 * nodlet: Nodlet currently performing the segmented SpMV
 * start: Column index where the sum will start at
 * range: Number of columns that will be part of the segmented sum
 **/
void segmentedSolution(long *node, int *values, int *colIndex, int *rowIndex, long *x, int **segSolution, int range, int realNNZ) {
    // printf("Starting column: %d\n", start);

    for(int i = 0; i < realNNZ; i++) {
        segSolution[rowIndex[i]][*node] += values[i] * x[colIndex[i]];
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
 * 
 * values: Is the array containing all non-zero values of the given sparse matrix
 * colIndex: Is the array containing the column indices of the non-zero values in the given sparse matrix
 * rowIndex: Is the array containing the row indices of the non-zero values in the given sparse matrix
 * x: Dense array (vector) multiplying the given sparse matrix
 * rows: Is the row size of the given sparse matrix
 * cols: Is the column size of the given sparse matrix
 **/
void solutionSpMV(long *nodes, int **segSolution, int **values, int **colIndex, int **rowIndex, long *x, int rows, int colSlice) {

    // Computes the size of the range of columns to cover parallely in SpMV
    // int colSlice, startingCol;
    // if (cols % NODLETS == 0) 
    //     colSlice = cols / NODLETS;
    // else
    //     colSlice = (cols / NODLETS) + 1;

    // printf("Column slice: %d\n", colSlice);

    // Parallel segmented sum
    unsigned long nid, nidend, starttime, endtime, totalCycles; 
    starttiming();

    // Start timing
    nid = NODE_ID();
    starttime = CLOCK();
    for (int i = 0; i < NODLETS; i++) {
        int realNNZ = arrayLength(values[i]);
        cilk_spawn segmentedSolution(&nodes[i], values[i], colIndex[i], rowIndex[i], x, segSolution, colSlice, realNNZ);
    }
    cilk_sync;
    // End timing
    endtime = CLOCK();
    nidend = NODE_ID();
    totalCycles = endtime - starttime;
    if (nid != nidend)
    {
        printf("ERROR: timing problem: start node (%d), end node (%lu)\n", nid, nidend);
    }

    double seconds = totalCycles * (1.0 / 1.500000);

    printf("Seconds: %f\n", seconds);
    printf("Cycles: %lu\n", totalCycles);

    // printMatrix(segSolution,rows,NODLETS);
    // printf("\n");
}

#endif