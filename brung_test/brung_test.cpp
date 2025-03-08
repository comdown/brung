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
		
		TEST_METHOD(TestChunk)
		{
			initVM();

			Chunk chunk;
			initChunk(&chunk);

			// Test adding constants
			int constantIdx1 = addConstant(&chunk, 1.2);
			Assert::AreEqual(1.2, chunk.constants.values[constantIdx1]);
			Assert::AreEqual(1.2, getConstantFromConstantIndex(&chunk, constantIdx1));

			int constantIdx2 = addConstant(&chunk, 3.4);
			Assert::AreEqual(3.4, chunk.constants.values[constantIdx2]);
			Assert::AreEqual(3.4, getConstantFromConstantIndex(&chunk, constantIdx2));

			// Test writing to chunk
			writeChunk(&chunk, OP_CONSTANT, 123);
			writeChunk(&chunk, constantIdx1, 123);
			Assert::AreEqual((uint8_t)OP_CONSTANT, chunk.code[0]);
			Assert::AreEqual((uint8_t)constantIdx1, chunk.code[1]);

			writeChunk(&chunk, OP_ADD, 123);
			Assert::AreEqual((uint8_t)OP_ADD, chunk.code[2]);

			writeChunk(&chunk, OP_RETURN, 124);
			Assert::AreEqual((uint8_t)OP_RETURN, chunk.code[3]);

			freeVM();
			freeChunk(&chunk);
		}

        TEST_METHOD(TestStack)
        {
			initVM();

			Chunk chunk;
			initChunk(&chunk);

			// Test pushing and popping values on the stack

			// one value
			{
				push(1.2);
				Assert::AreEqual(1.2, pop());
			}

			// two values
			{
				push(1.2);
				push(3.4);
				auto v1 = pop();
				auto v2 = pop();
				Assert::AreEqual(3.4, v1);
				Assert::AreEqual(1.2, v2);
			}

			// 3 values
			{
				push(1.2);
				push(3.4);
				push(5.6);
				auto v1 = pop();
				auto v2 = pop();
				auto v3 = pop();
				Assert::AreEqual(5.6, v1);
				Assert::AreEqual(3.4, v2);
				Assert::AreEqual(1.2, v3);
			}

			// test if the stack is empty
			{
				Assert::IsTrue(isStackEmpty());
			}
			
			freeVM();
			freeChunk(&chunk);
        }

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
