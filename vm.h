#ifndef brung_vm_h
#define brung_vm_h

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct 
{
	Chunk* chunk;
	uint8_t* ip; // instruction pointer // points to the next instruction to be executed
	Value stack[STACK_MAX];
	Value* stackTop;
} VM;

typedef enum
{
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

void push(Value value);
Value pop();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // brung_vm_h
