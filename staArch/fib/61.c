#include "memoryweb.h"
#include "cilk.h"
#include "stdio.h"

#define N 3

long fib_cilk(long n) {
	if (n < 2)
		return n;
	long a = cilk_spawn fib_cilk(n-1);
	long b = cilk_spawn fib_cilk(n-2);
	cilk_sync;
	return a + b;
}

long fib_seq(long n) {
	if (n < 2)
		return n;
	long a = fib_seq(n-1);
	long b = fib_seq(n-2);
	return a + b;
}

long main() {
	long result_seq = fib_seq(N);
	long result_cilk = fib_cilk(N);

	if (result_seq == result_cilk) {
		printf("P"); // Pass
		printf(" ");
		printf("%d",result_seq);
	} else {
		printf("F"); // Fail
		printf(" ");
		printf("%d",result_seq);
		printf(" ");
		printf("%d",result_cilk);
	}
	return 0;
}