#include "pch.h"
#include "CppUnitTest.h"
#include "../src/hnefatafl.h"
#include <sstream>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HnefataflTests
{
    TEST_CLASS(HnefataflGameTest)
    {
    public:
        static const int BOARD_SIZE = 11; 
        static const int WHITE = 1; 
        static const int BLACK = 2; 
        static const int KING = 3; 
        static const int KING_SQUARE = 4; 
        static const int EMPTY = 0; 
        static const int OUT_OF_BOUNDS = -1; 
        
        // Test board initialization
        TEST_METHOD(BoardInitialization)
        {
            Hnefatafl game;

            // Check the king's position
            Assert::AreEqual(KING, game.getPiece(5, 5));

            // Check the king's squares
            Assert::AreEqual(KING_SQUARE, game.getPiece(0, 0));
            Assert::AreEqual(KING_SQUARE, game.getPiece(10, 10));
            Assert::AreEqual(KING_SQUARE, game.getPiece(0, 10));
            Assert::AreEqual(KING_SQUARE, game.getPiece(10, 0));

            // Check black pieces
            Assert::AreEqual(BLACK, game.getPiece(0, 3));
            Assert::AreEqual(BLACK, game.getPiece(10, 3));
            Assert::AreEqual(BLACK, game.getPiece(1, 5));
            Assert::AreEqual(BLACK, game.getPiece(5, 1));

            // Check white pieces
            Assert::AreEqual(WHITE, game.getPiece(4, 4));
            Assert::AreEqual(WHITE, game.getPiece(5, 4));
            Assert::AreEqual(WHITE, game.getPiece(6, 4));
            Assert::AreEqual(WHITE, game.getPiece(3, 5));
        }

        // Test moving a piece
        TEST_METHOD(MovePiece)
        {
            Hnefatafl game;

            std::pair<int, int> source = std::make_pair(4, 4);
            std::pair<int, int> target = std::make_pair(4, 6);
            game.move(source, target);

            Assert::AreEqual(0, game.getPiece(4, 4));
            Assert::AreEqual(WHITE, game.getPiece(4, 6));
        }

		// Test capturing a piece vertically
        TEST_METHOD(CapturePieceVertical)
        {
            Hnefatafl game;

            // Move black pieces to surround a white piece
            game.move(std::make_pair(0, 3), std::make_pair(4, 3));
            game.move(std::make_pair(10, 3), std::make_pair(6, 3));
           
            // Check if the white piece is captured
            Assert::IsTrue(game.isCaptured(std::make_pair(5, 3)));
        }

		// Test capturing a piece horizontally
		TEST_METHOD(CapturePieceHorizontal)
		{
            Hnefatafl game;

			// Move black pieces to surround a white piece
			game.move(std::make_pair(5, 3), std::make_pair(5, 2));
			game.move(std::make_pair(0, 3), std::make_pair(5, 3));

			// Check if the white piece is captured
			Assert::IsTrue(game.isCaptured(std::make_pair(5, 2)));
		}

        // Test if the king is captured
        TEST_METHOD(KingCaptured)
        {
            Hnefatafl game;

            // Move White out of the way
            game.move(std::make_pair(5, 3), std::make_pair(9, 3));
			game.move(std::make_pair(5, 4), std::make_pair(5, 2));

            // Move King
			game.move(std::make_pair(5, 5), std::make_pair(5, 3));
			game.move(std::make_pair(5, 3), std::make_pair(1, 3));

            // Move black pieces to surround the king
            game.move(std::make_pair(1, 5), std::make_pair(1, 4));
            game.move(std::make_pair(3, 0), std::make_pair(3, 3));
            game.move(std::make_pair(3, 3), std::make_pair(2, 3));
            game.move(std::make_pair(5, 1), std::make_pair(1, 1));
			game.move(std::make_pair(1, 1), std::make_pair(1, 2));

            // Check if the king is captured
            Assert::IsTrue(game.isKingCaptured());
        }

        // Test if the game is over
        TEST_METHOD(GameOver)
        {
            Hnefatafl game;

			Assert::IsFalse(game.isGameOver());

            // Move White out of the way
            game.move(std::make_pair(5, 3), std::make_pair(9, 3));
            game.move(std::make_pair(5, 4), std::make_pair(5, 2));

            // Move King
            game.move(std::make_pair(5, 5), std::make_pair(5, 3));
            Logger::WriteMessage(std::to_wstring(game.getPiece(5, 3)).c_str());
            game.move(std::make_pair(5, 3), std::make_pair(1, 3));
            Logger::WriteMessage(std::to_wstring(game.getPiece(1, 3)).c_str());
			game.move(std::make_pair(1, 3), std::make_pair(1, 0));
			Logger::WriteMessage(std::to_wstring(game.getPiece(1, 0)).c_str());
			game.move(std::make_pair(1, 0), std::make_pair(0, 0));
            Logger::WriteMessage(std::to_wstring(game.getPiece(0, 0)).c_str());

            // Check if the game is over
            Assert::IsTrue(game.isGameOver());
        }

		// Test if getPiece returns the correct piece
        TEST_METHOD(GetPiece)
        {
            Hnefatafl game;

            // Each type
            Assert::AreEqual(KING, game.getPiece(5, 5));
            Assert::AreEqual(KING_SQUARE, game.getPiece(0, 0));
            Assert::AreEqual(BLACK, game.getPiece(0, 3));
            Assert::AreEqual(WHITE, game.getPiece(4, 4));
			Assert::AreEqual(0, game.getPiece(3, 3));

			// Out of bounds
			Assert::AreEqual(-1, game.getPiece(-1, 0));
			Assert::AreEqual(-1, game.getPiece(0, -1));
			Assert::AreEqual(-1, game.getPiece(11, 0));
			Assert::AreEqual(-1, game.getPiece(0, 11));

        }

		// Test if covertMove returns the correct pair
        TEST_METHOD(ConvertMove)
        {
            Hnefatafl game;
			std::pair<int, int> test = game.convertMove("A2");
            Assert::AreEqual(1, test.first);
			Assert::AreEqual(0, test.second);

			test = game.convertMove("K10");
			Assert::AreEqual(9, test.first);
			Assert::AreEqual(10, test.second);
        }

		// Test if isValidInput returns the correct boolean
        TEST_METHOD(IsValidInput)
        {
            Hnefatafl game;

            // Valid input
            Assert::IsTrue(game.isValidInput("A1 B1"));

            // Invalid input
            Assert::IsFalse(game.isValidInput("A12 A9"));
            Assert::IsFalse(game.isValidInput("A"));
            Assert::IsFalse(game.isValidInput("11 22"));
            Assert::IsFalse(game.isValidInput("AA BB"));
            Assert::IsFalse(game.isValidInput("a1 B1"));
        }

		// Test if HandleNeighboursCaptured captures the correct pieces
        TEST_METHOD(HandleNeighboursCaptured)
        {
            Hnefatafl game;

            // Set up the board to capture a piece
            game.move(std::make_pair(0, 3), std::make_pair(4, 3)); // Move black piece
            game.move(std::make_pair(10, 3), std::make_pair(6, 3)); // Move black piece

            // Call the handleNeighboursCaptured function
            game.handleNeighboursCaptured(4, 3);

            // Check if the neighboring pieces are captured
            Assert::AreEqual(EMPTY, game.getPiece(3, 3)); // Up
            Assert::AreEqual(EMPTY, game.getPiece(5, 3)); // Down
            Assert::AreEqual(EMPTY, game.getPiece(4, 2)); // Left
            Assert::AreEqual(WHITE, game.getPiece(4, 4)); // Right
        }

        // Test the run method
        /*TEST_METHOD(RunGame)
        {
            Hnefatafl game;

            // Redirect std::cin and std::cout
			std::istringstream input("W\rD6 D2\rE6 C6\rF6 D6\rD6 D3\rD3 A3\rA3 A1\rreturn\r");
            std::ostringstream output;
            std::streambuf* cinbuf = std::cin.rdbuf(input.rdbuf());
            std::streambuf* coutbuf = std::cout.rdbuf(output.rdbuf());

            // Run the game
            int result = game.run();

            // Restore std::cin and std::cout
            std::cin.rdbuf(cinbuf);
            std::cout.rdbuf(coutbuf);

            // Check if the game returns to the main menu
            Assert::AreEqual(0, result);

            // Check the expected output for correct prompts and moves
            std::string expectedOutput =
                "Choose starting player (W/B) :\n"  // Prompt for starting player
                "Enter your move (e.g., A1 B2): \n"  // Prompt for player move
                "Enter your move (e.g., A1 B2): \n"
                "Enter your move (e.g., A1 B2): \n"
                "The king has escaped. White wins!\n"  // Expected game result if white wins
                "Type 'return' to return to the main menu, or 'exit' to exit MiniGame-Madness.\n";

            // Check if output contains the expected result
            Assert::IsTrue(output.str().find(expectedOutput) != std::string::npos);

            // Additional checks could include checking game board state after each move, 
            // handling of captures, and ensuring that the game ends correctly.

            // Example: Ensure the game ends correctly and the king escapes.
            Assert::IsTrue(game.isGameOver());
        }*/
    };
}