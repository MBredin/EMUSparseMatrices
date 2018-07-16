#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "Utilities.h"
#include "SpmvOperations.h"

#define ANSI_COLOR_BLUE "\x1b[34m"      // Color blue for specified output
#define ANSI_COLOR_RESET "\x1b[0m"      // Reset color for specified output

#define MATRIXZISE 8                    // Size for each size of the square matrix

int nnz;

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