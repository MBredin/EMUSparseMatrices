#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <memoryweb.h>
#include <cilk.h>
#include "Utilities.h"
#include "SpmvOperations.h"

replicated long *x;                     // Replicate vector across each nodelet
int nnz;                                // Amount of non-zero values in sparse matrix 

/********************************** MAIN ***********************************/
int main(int argc, char **argv) {
    long threads = 0;
    if (argc != 2)
    {
        printf("Command Line Input Error\n");
        exit(1);
    }
    else
    {
        threads = NODLETS * atoi(argv[1]);
    }
    printf("Threads: %d\n", threads);

    printf("Matrix Size: %d\nThreads per Core: %d\n", MATRIXZISE, threads);

    int m = MATRIXZISE;     // Number of rows in matrix A
    int n = MATRIXZISE;     // Number of columns in matrix A

    long *tempX = alloc_x();
    mw_replicated_init((long *)&x, (long)tempX);

    long *nodes = mw_malloc1dlong(threads * sizeof(long *));
    for (int i = 0; i < threads; i++)
        nodes[i] = i;

    // Computes the size of the range of columns to cover parallely in SpMV
    int colSlice = 0;
    if (n % threads == 0)
        colSlice = n / threads;
    else
        colSlice = (n / threads) + 1;

    // Generates a cluster of the sparse matrix per nodlet and stores it in splitA parallely 
    int **splitA[threads];
    for (int i = 0; i < threads; i++) {
        splitA[i] = cilk_spawn genSparseMatrix(&nodes[i], m, colSlice);
    }
    cilk_sync;

    // Arrays containing the compressed information of A
    // printf("Compressed information of A: \n");
    int *values[threads];               // Non-zero values contained in A;
    int *colIndex[threads];             // Column indices of the non-zero values located in A
    int *rowIndex[threads];             // Row indicex of the non-zero values located in A
    //int realNNZ[threads];
    int *realNNZ =(int *)malloc(threads * sizeof(int));

    // Compresses all valuable info about non-zero values contained in the clusters of 
    // splitA within arrays: values, colIndex, and rowIndex
    // unsigned long nid, nidend, starttime, endtime, totalCycles; 
    starttiming();

    // Start timing
    // nid = NODE_ID();
    // starttime = CLOCK();
    for(int i = 0; i < threads; i++) {
        cilk_spawn compression(&nodes[i], splitA[i], &values[i], &colIndex[i], &rowIndex[i], &realNNZ[i], m, colSlice);
    }
    cilk_sync;
    // End timing
    // endtime = CLOCK();
    // nidend = NODE_ID();
    // totalCycles = endtime - starttime;
    // if (nid != nidend)
    // {
    //     printf("ERROR: timing problem: start node (%d), end node (%lu)\n", nid, nidend);
    // }

    // printf("Compilation cycles: %lu\n", totalCycles);
    
    int *segSolution[threads];

    // Solves SpMV parallely through 4 cores using the compressed information
    unsigned long starttime, endtime, totalCycles; 
    //starttiming();

    // Start timing
    starttime = CLOCK();

    solutionSpMV(nodes, segSolution, values, colIndex, rowIndex, realNNZ, x, m, colSlice, threads);
    
    // End timing
    endtime = CLOCK();
    totalCycles = endtime - starttime;

    printf("Solution cycles: %lu\n", totalCycles);
    
    int *solution = (int *)malloc(m * sizeof(int));  // Allocation of memory for solution array
    initializeArray(solution, m);                    // Initialize solution array with all values being zero
    for(int c = 0; c < threads; c++) {
        segmentedSum(&nodes[c], solution, segSolution, m, c);
    }

    // printf("Solution: ");
    // printArray(solution, m);

    return 0;
}