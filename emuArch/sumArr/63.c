#include "memoryweb.h"
#include "cilk.h"
#include "timing.h"
#include "stdio.h"

#define SIZE 32

//noinline
long sum(long **array, long epn) {
	long sum = 0;
	for (long i=0; i<NODELETS(); i++)
		for (long j=0; j<epn; j++)
			sum += array[i][j];
	return sum;
}

int main(){
	// Allocate arrays
	long epn = SIZE/NODELETS(); // elements per nodelet
	long** A = (long **) mw_malloc2d(NODELETS(), epn * sizeof(long));
	long** B = (long **) mw_malloc2d(NODELETS(), epn * sizeof(long));
	long sumA;
	long sumB;

	// Initialize array values
	for (long i=0; i<NODELETS(); i++)
		for (long j=0; j<epn; j++) {
			A[i][j] = 1;
			B[i][j] = 2;
	}

	starttiming();

	// Spawn threadlet to sum values in A
	sumA = cilk_spawn sum(A, epn);

	// Call function to sum values of B (in current threadlet)
	sumB = sum(B, epn);

	// Wait for spawned threadlet to complete
	cilk_sync;

	printf("A = %ld, B = %ld\n", sumA, sumB);

	return 0;
}