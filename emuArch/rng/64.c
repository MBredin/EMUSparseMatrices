#include "unistd.h"
#include "fcntl.h"
#include "memoryweb.h"
#include "malloc.h"
#include "cilk.h"
#include "distributed.h"
#include "timing.h"
#include "data_helpers.h"

#define VERIFY 0

// constants for RNG
#define K (1L << 43)
#define A_R ((1L << 62) + (1L << 53) + (1L << 41) + (1L << 36) + (1L << 23) + (1L << 17) + 1) // congruent to 1 mod 4
#define C_R 3898255708540604102L // congruent to 2 mod 4
#define A_L (6*K + 1)
#define C_L 0
#define X_0 1 // must be odd

// Total array elements MUST BE POWER OF 2 and must be > N*T
#define E (1<<15) // 2^18 elements
#define T 256 // Threads per nodelet
#define U 4 // Updates factor = number updates per element
replicated unsigned long * Table;
replicated long nUpdates = E*U; // Needs to be computed so initialize each copy
replicated long nThreads = T;