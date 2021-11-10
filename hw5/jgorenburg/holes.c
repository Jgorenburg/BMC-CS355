// tests coalescing

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include "mem.h"


int main() {
	Mem_Init(4096);
	// these 4 points should take up the entire space (based on my header and global variables, may be slightly 
	// different for your setup)
	void * ptr1 = Mem_Alloc(981);
	void * ptr2 = Mem_Alloc(981);
	void * ptr3 = Mem_Alloc(981);
	void * ptr4 = Mem_Alloc(981);
	
	assert(ptr1 != NULL);
	assert(ptr2 != NULL);
	assert(ptr3 != NULL);
	assert(ptr4 != NULL);
	
	// no room for this
	void * ptr5 = Mem_Alloc(1024);
	assert(ptr5 == NULL);

	Mem_Free(ptr2, 0);
	Mem_Free(ptr3, 0);
	Mem_Dump();

	// should be no room for this
	void * ptr6 = Mem_Alloc(1024);
	assert(ptr6 == NULL);

	Mem_Free(NULL, 1);
	Mem_Dump();
	
	// now there is room
	void * ptr7 = Mem_Alloc(1024);
	assert(ptr7 != NULL);
	
	Mem_Dump();

	printf("SUCCESS\n");
	return 0;
}
