#include "pch.h"
#include "CppUnitTest.h"
#include "../src/sudoku.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sudokuTest
{
	TEST_CLASS(sudokuTest)
	{
	public:

		TEST_METHOD(GridMaker)
		{
			sudokuuuu game;

			Assert::AreEqual(0, remover(grid, 500));
		}

		TEST_METHOD(Unique)
		{
			sudokuuuu game;

			generate(input);
			
			Assert::uniquequestionmark(input, 0, 0, 0);
		}

		TEST_METHOD(givenAnswer)
		{
			sudokuuuu game;

			generate(input);

			Assert::AreEqual(0, remover(grid, 100));
		}
	};
}
