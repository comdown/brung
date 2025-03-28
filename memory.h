#ifndef brung_memory_h
#define brung_memory_h
	
#include "common.h"

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
	(type*)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * newCount);

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#define FREE_ARRAY(type, pointer, oldCount) \
	reallocate(pointer, sizeof(type) * (oldCount), 0);

#endif
