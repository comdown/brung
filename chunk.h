#ifndef brung_chunk_h
#define brung_chunk_h

#include "common.h"
#include "value.h"

typedef enum 
{
	OP_CONSTANT,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NEGATE,
	OP_RETURN,
} OpCode;

typedef struct 
{
	int count;
	int capacity;
	uint8_t* code;
	ValueArray constants;

	// line information (Run-length encoding (RLE))
	int* lineStarts;
	int* lineCounts;
	int lineCount;
} Chunk;


void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, const uint8_t byte, const int line);
int addConstant(Chunk* chunk, const Value value);
uint8_t getConstantIndex(const Chunk* chunk, const uint8_t opOffset);
Value getConstant(const Chunk* chunk, const int opIndex);
Value getConstantFromConstantIndex(const Chunk* chunk, const uint8_t constantIndex);
void freeChunk(Chunk* chunk);
int getLine(const Chunk* chunk, const int offset);

#endif