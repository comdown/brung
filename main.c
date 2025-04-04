#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char* argv[])
{
	initVM();

	Chunk chunk;
	initChunk(&chunk);

	int constantIdx = addConstant(&chunk, 1.2);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantIdx, 123);

	constantIdx = addConstant(&chunk, 3.4);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantIdx, 123);

	writeChunk(&chunk, OP_ADD, 123);

	constantIdx = addConstant(&chunk, 5.6);
	writeChunk(&chunk, OP_CONSTANT, 123);
	writeChunk(&chunk, constantIdx, 123);

	writeChunk(&chunk, OP_DIVIDE, 123);
	writeChunk(&chunk, OP_RETURN, 124);

	//int constantIdx = addConstant(&chunk, 1.4);
	//writeChunk(&chunk, OP_CONSTANT, 100);
	//writeChunk(&chunk, constantIdx, 100);
	//
	//writeChunk(&chunk, OP_NEGATE, 101);
	//
	
	// writeChunk(&chunk, OP_RETURN, 101);

	interpret(&chunk);
	freeVM();
	freeChunk(&chunk);

	return 0;
}