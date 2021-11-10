// This test is designed to test coalescing the local neighborhood
// A large number of chunks are allocated and freed, leaving a lot of
// fragmented memory. Then a chunk in the middle is freed with a '2',
// causing the local neighborhood to be coalesced.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include "mem.h"

#define ALLOC_SIZE 1024
#define CHUNK 64


int main() {
	Mem_Init(ALLOC_SIZE);

	void **ptrs = malloc(sizeof(void*) * ALLOC_SIZE);

	for (int i = 0; i < ALLOC_SIZE / CHUNK; i++) {
		ptrs[i] = Mem_Alloc(CHUNK);
		assert(ptrs[i] != NULL);
	}
	
	for (int i = 0; i < ALLOC_SIZE / CHUNK; i++) {
		if (i != 6) {
			Mem_Free(ptrs[i], 0);
		}
	}
	// should see a lot of small free holes
	Mem_Dump();

	Mem_Free(ptrs[6], 2);

	// should see fewer holes and one larger hole
	Mem_Dump();

	free(ptrs);

}
