#ifndef brung_debug_h
#define brung_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif
