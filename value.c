#include <stdio.h>
#include "value.h"
#include "memory.h"

void initValueArray(ValueArray* array)
{
	array->capacity = 0;
	array->count = 0;   
	array->values = NULL;
}

void writeValueArray(ValueArray* array, const Value value)
{
    if (array->capacity < array->count + 1) 
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array)
{
    FREE_ARRAY(Value, array->values, array->count);
    initValueArray(array);
}

void printValue(const Value value)
{
	printf("%f", value);
}
