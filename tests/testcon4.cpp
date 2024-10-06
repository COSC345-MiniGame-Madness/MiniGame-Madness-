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
			Con4 game;

			Assert::AreEqual(1, game.swapturn(2));
		}

		TEST_METHOD(testdrop)
		{
			Con4 game;

			game.dropcoin(7, 1);

			Assert::AreEqual(1, game.getnum(6, 5));
		}

		TEST_METHOD(testwin)
		{
			Con4 game;

			game.dropcoin(7, 1);
			game.dropcoin(6, 1);
			game.dropcoin(5, 1);
			game.dropcoin(4, 1);

			game.checkwin();

			Assert::IsTrue(game.winquestionmark);
		}

		TEST_METHOD(testdraw)
		{
			Con4 game;

			int num = 1;

			for (int toprow = 0; toprow < 7; toprow++)
			{
				if (num == 1)
				{
					game.setnum(num, toprow, 0);
					num = 2;
				}
				else 
				{
					game.setnum(num, toprow, 0);
					num = 1;
				}
			}

			game.checkdraw();

			Assert::IsTrue(game.winquestionmark);
		}
	};
}