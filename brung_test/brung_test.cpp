#include "CppUnitTest.h"
#include "../common.h"
#include "../chunk.h"
#include "../debug.h"
#include "../vm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brungtest
{
	TEST_CLASS(brungtest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
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

			interpret(&chunk);
			freeVM();
			freeChunk(&chunk);
		}
	};
}
