#include "pch.h"
#include "CppUnitTest.h"
#include "../src/con4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace con4Tests
{
    TEST_CLASS(con4Tests)
    {
	public:

		TEST_METHOD(testplayerswitch)
		{
			con4game game;

			Assert::AreEqual(1, swapturn(2));
		}

		TEST_METHOD(testdrop)
		{
			con4game game;

			grid[7][6] = {0};

			game.dropcoin(7, 1);

			Assert::AreEqual(1, grid[0][7]);
		}

		TEST_METHOD(testwin)
		{
			con4game game;

			grid[7][6] = {0};

			game.dropcoin(7, 1);
			game.dropcoin(6, 1);
			game.dropcoin(5, 1);
			game.dropcoin(4, 1);

			game.checkwin();

			Assert::AreEqual(game.winquestionmark, true);
		}

		TEST_METHOD(testdraw)
		{
			con4game game;

			grid[7][6] = {0};

			for(int toprow = 0; toprow < 7; toprow++)
			{
				game.setnum(1, toprow, 0);
			}

			game.checkdraw();

			Assert::AreEqual(game.winquestionmark, true);
		}
	}
}