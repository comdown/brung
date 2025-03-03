#ifndef brung_value_h
#define brung_value_h

#include "common.h"
typedef double Value;

typedef struct
{
	int capacity;
	int count;
	Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, const Value value);
void freeValueArray(ValueArray* array);
void printValue(const Value value);

#endif