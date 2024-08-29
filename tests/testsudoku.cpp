#include "pch.h"
#include "CppUnitTest.h"
#include "../src/sudoku.h"
#include "../games/SUDOKUUUUUU/"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sudokuTest
{
	TEST_CLASS(sudokuTest)
	{
	public:
		
		int grid[9][9] = { 0 };

		TEST_METHOD(GridMaker) //tests if grid is successfully created
		{
			sudokuuuu game;

			game.setnum(9, 0, 0);

			game.setnum(5, 8, 2);

			game.setnum(3, 7, 4);

			Assert::AreEqual(9, game.getnum(0, 0);

			Assert::AreEqual(5, game.getnum(8, 2);

			Assert::AreEqual(3, game.getnum(7, 3);
		}
		
		TEST_METHOD(uniquecheck) //checks if the number is unique horizontally, vertically and in 3x3 inner cube
		{
			sudokuuuu game;

			game.setnum(6, 1, 1);

			Assert::AreEqual(true, game.uniquequestionmark(game.grid, 1, 1, 6));

			Assert::AreEqual(false, game.uniquequestionmark(game.grid, 2, 1, 6));
		}
		/*
		TEST_METHOD() //theres literally no other thing to test
		{

		}*/
	};
}
