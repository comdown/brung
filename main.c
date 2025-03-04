#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, char* argv[])
{
	Chunk chunk;
	initChunk(&chunk);

	int constantIdx = addConstant(&chunk, 1.4);
	writeChunk(&chunk, OP_CONSTANT, 100);
	writeChunk(&chunk, constantIdx, 100);
	writeChunk(&chunk, OP_RETURN, 101);
	writeChunk(&chunk, OP_RETURN, 101);

	disassembleChunk(&chunk, "test chunk");

	freeChunk(&chunk);

	return 0;
}