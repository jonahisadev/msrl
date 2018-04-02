#include "lib/msrl.h"

#include <stdio.h>

int main(int argc, char** argv) {
	// Create memory pool of 1kB
	MSRLMemPool* pool = msrl_pool(1024);

	// Allocate some memory
	int* a = msrl_alloc(pool, 5);
	int* b = msrl_alloc(pool, 10);
	int* c = msrl_alloc(pool, 5);
	msrl_free(pool, b);
	int* d = msrl_alloc(pool, 5);

	// Test
	assert(a != b);			// Should not be the same
	assert(b != c);			// Same as above
	assert(b == d);			// These should be the same

	// Clean up
	msrl_pool_free(pool);

	// Yay!
	printf("This means we succeeded!\n");
	return 0;
}