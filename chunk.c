#include "chunk.h"
#include <stdlib.h>
#include "memory.h"

void initChunk(Chunk* chunk)
{
	chunk->capacity = 0;
	chunk->count = 0;
	chunk->code = NULL;
	chunk->lineStarts = NULL;
	chunk->lineCounts = NULL;
	chunk->lineCount = 0;
	initValueArray(&chunk->constants);	
}

void writeChunk(Chunk* chunk, const uint8_t byte, const int line)
{
	if (chunk->capacity < chunk->count + 1)
	{
		const int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
	}

	if (chunk->lineCount == 0 || chunk->lineStarts[chunk->lineCount - 1] != line)
	{
		chunk->lineCount++;
		chunk->lineStarts = GROW_ARRAY(int, chunk->lineStarts, chunk->lineCount - 1, chunk->lineCount);
		chunk->lineCounts = GROW_ARRAY(int, chunk->lineCounts, chunk->lineCount - 1, chunk->lineCount);
		chunk->lineStarts[chunk->lineCount - 1] = line;
		chunk->lineCounts[chunk->lineCount - 1] = 1;
	}
	else
	{
		chunk->lineCounts[chunk->lineCount - 1]++;
	}

	chunk->code[chunk->count] = byte;
	++chunk->count;
}

int addConstant(Chunk* chunk, const Value value)
{
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}

uint8_t getConstantIndex(const Chunk* chunk, const uint8_t opOffset)
{
	return chunk->code[opOffset + 1];
}

Value getConstant(const Chunk* chunk, const int opOffset)
{
	const int constantIndex = getConstantIndex(chunk, opOffset);
	return getConstantFromConstantIndex(chunk, constantIndex);
}

Value getConstantFromConstantIndex(const Chunk* chunk, const uint8_t constantIndex)
{
	return chunk->constants.values[constantIndex];
}

void freeChunk(Chunk* chunk)
{
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lineStarts, chunk->lineCount);
	FREE_ARRAY(int, chunk->lineCounts, chunk->lineCount);
	initChunk(chunk);
	freeValueArray(&chunk->constants);
}

// It¡¯s not necessary for getLine() to be particularly efficient. 
// Since it is called only when a runtime error occurs, 
// it is well off the critical path where performance matters.
int getLine(const Chunk* chunk, const int offset)
{
	int line = 0;
	int accumulatedCount = 0;
	for (int i = 0; i < chunk->lineCount; i++)
	{
		accumulatedCount += chunk->lineCounts[i];
		if (accumulatedCount > offset)
		{
			line = chunk->lineStarts[i];
			break;
		}
	}
	return line;
}
