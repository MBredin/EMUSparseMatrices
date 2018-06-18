#include "memoryweb.h"
#include "timing.h"
#include "stdio.h"
#include "cilk.h"

#define N 131072 // 4096 elements on 8 nodelets -> 4 elements per nodelet
#define VERIFY 0

void addOne(long *A){
	(*A) += 1;
}

int main(){
	long* A = mw_malloc1dlong(N);

	starttiming();

	// Thread will migrate to each element and initialize it
	cilk_for (long i=0; i < N; i++)
		A[i] = 0;
	printf(" A[0] = %ld\n", A[0]);

	// Thread will migrate to each element and update it
	cilk_for (long i=0; i < N; i++) {
		A[i] += 1; // Use ATOMIC_ADDM(&A[i], 1) for multithreaded code
		//REMOTE_ADD(&A[i], 1); // Replace prev line for remote atomic add
		//cilk_spawn addOne(&A[i]);
	}
	//cilk_sync;
	printf(" A[0] = %ld\n", A[0]);

	#if VERIFY
	// Thread will migrate to read element of list and then print
	for (long i=1; i < N; i++)
		printf(" A[%ld] = %ld\n", i, A[i]);
	#endif

return 0;
}
