#include <stdio.h>
#include "debug.h"
#include "value.h"

int simpleInstruction(const char* name, const int offset)
{
	printf("%s\n", name);
	return offset + 1;
}

int constantInstruction(const char* name, const Chunk* chunk, const int offset)
{
	const uint8_t constantIndex = getConstantIndex(chunk, offset);
	printf("%-16s %4d '", name, constantIndex);

	Value constant = getConstantFromConstantIndex(chunk, constantIndex);
	printValue(constant);
	printf("'\n");

	return offset + 2;
}

void disassembleChunk(Chunk* chunk, char* name)
{
	printf("== %s ==\n", name);
	
	for (int offset = 0; offset < chunk->count;)
	{
		offset = disassembleInstruction(chunk, offset);
	}
}

int disassembleInstruction(Chunk* chunk, int offset)
{
	// print offset
	printf("%04d ", offset);

	// print line number
	// 이전 명령의 줄번호와 같으면 줄번호 다시 출력하지 않음
	int line = getLine(chunk, offset);
	if (offset > 0 && line == getLine(chunk, offset-1))
	{
		printf("   | ");
	}
	else 
	{
		printf("%4d ", line);
	}

	// print instruction
	uint8_t instruction = chunk->code[offset];
	switch (instruction)
	{
	case OP_RETURN:
		return simpleInstruction("OP_RETURN", offset);
	case OP_NEGATE:
		return simpleInstruction("OP_NEGATE", offset);
	case OP_CONSTANT:
		return constantInstruction("OP_CONSTANT", chunk, offset);
	case OP_ADD:
		return simpleInstruction("OP_ADD", offset);
	case OP_SUBTRACT:
		return simpleInstruction("OP_SUBTRACT", offset);
	case OP_MULTIPLY:
		return simpleInstruction("OP_MULTIPLY", offset);
	case OP_DIVIDE:
		return simpleInstruction("OP_DIVIDE", offset);
	default:
		printf("Unknown opcode %d\n", instruction);
		return offset + 1;
	}

	return 0;
}
