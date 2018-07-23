#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <memoryweb.h>
#include <cilk.h>
#include "Utilities.h"
#include "SpmvOperations.h"

replicated long *x;                      // Replicate vector across each nodelet
int nnz;                                // Amount of non-zero values in sparse matrix 

/********************************** MAIN ***********************************/
int main() {
    int m = MATRIXZISE;     // Number of rows in matrix A
    int n = MATRIXZISE;     // Number of columns in matrix A
    // printf("Rows: %d \n", m);
    // printf("Columns: %d \n", n);

    // int **A = genSparseMatrix(m, n);        // Creates sparse matrix A
    // printf("Matrix A: \n");
    // printMatrix(A, m, n);                   // Prints matrix A

    // int *x = genDenseVector(m);             // Creates vector that multiplies matrix A
    // printf("Vector x: ");
    // printArray(x,m);                        // Prints vector x

    long *tempX = alloc_x();
    mw_replicated_init((long *)&x, (long)tempX);

    long *nodes = mw_malloc1dlong(NODLETS * sizeof(long *));
    for (int i = 0; i < NODLETS; i++)
        nodes[i] = i;

    int colSlice = 0;
    if (n % NODLETS == 0)
        colSlice = n / NODLETS;
    else
        colSlice = (n / NODLETS) + 1;

    int **splitA[NODLETS];
    for (int i = 0; i < NODLETS; i++) {
        splitA[i] = cilk_spawn genSparseMatrix(&nodes[i], m, colSlice);
    }
    cilk_sync;
    // int realNNZ = checkNNZ(A,m,n);
    // double sparsePercentage = (realNNZ * 100) / (double)(m*n);
    // printf("Sparse percentage: %f \n", sparsePercentage);
    // printf("\n");

    // Arrays containing the compressed information of A
    // printf("Compressed information of A: \n");
    int **values = (int  **)malloc(NODLETS * sizeof(int *));            // Non-zero values contained in A;
    int **colIndex = (int **)malloc(NODLETS * sizeof(int *));           // Column indices of the non-zero values located in A
    int **rowIndex = (int **)malloc(NODLETS * sizeof(int *));           // Row indicex of the non-zero values located in A

    // Compress all valuable info about A's non-zero values in values, colIndex, and rowIndex
    for(int i = 0; i < NODLETS; i++) {
        int realNNZ = checkNNZ(splitA[i], m, colSlice);

        values[i] = (int *)malloc(realNNZ * sizeof(int));
        initializeArray(values[i], realNNZ);
        colIndex[i] = (int *)malloc(realNNZ * sizeof(int));
        initializeArray(colIndex[i], realNNZ);
        rowIndex[i] = (int *)malloc(realNNZ * sizeof(int));
        initializeArray(rowIndex[i], realNNZ);

        cilk_spawn compression(&nodes[i], splitA[i], values[i], colIndex[i], rowIndex[i], m, colSlice);
    }
    cilk_sync;
    // printf("\n");

    // Declaration and allocation of memory for matrix segSolution
    int **segSolution = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        segSolution[i] = (int *)malloc(NODLETS * sizeof(int));

    initializeMatrix(segSolution, m, NODLETS); // Initialize all values of matrix to zero

    // Solves SpMV parallely through 4 cores using the compressed information
    solutionSpMV(nodes, segSolution, values, colIndex, rowIndex, x, m, colSlice);

    int *solution = segmentedSum(segSolution, m);

    // printf("Solution: ");
    // printArray(solution, m);

    return 0;
}