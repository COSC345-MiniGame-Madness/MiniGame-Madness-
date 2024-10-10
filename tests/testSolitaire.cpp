#include "pch.h"
#include "CppUnitTest.h"
#include "../src/solitaire.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SolitaireTests
{
    TEST_CLASS(SolitaireTests)
    {
    public:
        TEST_METHOD(TestCreateStock)
        {
            Solitaire game;
            Assert::AreEqual(23, static_cast<int>(game.stock.size()), L"Stock should contain 52 cards.");
        }

        TEST_METHOD(TestDealCards)
        {
            Solitaire game;
            for (int i = 0; i < 7; ++i) {
                Assert::AreEqual(i + 1, game.tableau[i].size(), L"Tableau pile should have correct number of cards.");
            }
        }

        TEST_METHOD(TestCanCardAddToPile)
        {
            Solitaire game;
            Card king(Value::KING, Suit::HEARTS, Colour::RED, true);
            Pile emptyPile;
            Assert::IsTrue(game.canCardAddToPile(king, emptyPile), L"King should be able to be added to an empty pile.");

            Card queen(Value::QUEEN, Suit::CLUBS, Colour::BLACK, true);
            emptyPile.addCard(king);
            Assert::IsTrue(game.canCardAddToPile(queen, emptyPile), L"Queen should be able to be added to a pile with a King of opposite color.");
        }

        TEST_METHOD(TestCanCardAddToFoundation)
        {
            Solitaire game;
            Card ace(Value::ACE, Suit::HEARTS, Colour::RED, true);
            FoundationPile emptyFoundation(Suit::HEARTS);
            Assert::IsTrue(game.canCardAddToFoundation(ace, emptyFoundation), L"Ace should be able to be added to an empty foundation.");

            Card two(Value::TWO, Suit::HEARTS, Colour::RED, true);
            emptyFoundation.addCard(ace);
            Assert::IsTrue(game.canCardAddToFoundation(two, emptyFoundation), L"Two should be able to be added to a foundation with an Ace of the same suit.");
        }

        TEST_METHOD(TestIsGameWon)
        {
            Solitaire game;
            for (int i = 0; i < 4; ++i) {
                for (int j = Value::ACE; j <= Value::KING; ++j) {
                    if (i < 2) {
                        game.foundations[i].addCard(Card(static_cast<Value>(j), static_cast<Suit>(i), Colour::RED, true));
					}
                    else {
                        game.foundations[i].addCard(Card(static_cast<Value>(j), static_cast<Suit>(i), Colour::BLACK, true));
                    }
                }
            }
            Assert::IsTrue(game.isGameWon(), L"Game should be won when all foundation piles have 13 cards.");
        }

        TEST_METHOD(TestDrawBackOfCards)
        {
            Solitaire game;
            game.drawBackOfCards(0, 0);
            // Assuming you have a method to read the screen buffer content
            std::wstring expected[] = { L"+------------+",
                L"|  / / / / / |",
                L"| / / / / /  |",
                L"| \\ \\ \\ \\ \\  |",
                L"|  \\ \\ \\ \\ \\ |",
                L"|  / / / / / |",
                L"| / / / / /  |",
                L"| \\ \\ \\ \\ \\  |",
                L"|  \\ \\ \\ \\ \\ |",
                L"|  / / / / / |",
                L"+------------+" };
			for (int i = 0; i < 11; ++i) {
				std::wstring actual = game.screenBuffer.readScreenText(0, i, 14);
				Assert::AreEqual(expected[i], actual, L"Back of card should be drawn correctly.");
			}
        }

        TEST_METHOD(TestDrawCard)
        {
            Solitaire game;
            Card card(Value::ACE, Suit::HEARTS, Colour::RED, true);
            game.drawCard(0, 0, card);
            // Assuming you have a method to read the screen buffer content
            std::wstring expected[] = { L"+------------+",
                L"| A        ♥ |",
                L"|            |",
                L"|            |",
                L"|            |",
                L"|            |",
                L"|            |",
                L"|            |",
                L"|            |",
                L"| ♥        A |",
                L"+------------+"
            };
			for (int i = 0; i < 11; ++i) {
				std::wstring actual = game.screenBuffer.readScreenText(0, i, 14);
				Assert::AreEqual(expected[i], actual, L"Card should be drawn correctly.");
			}
        }

        TEST_METHOD(TestIsValidTableauInput)
        {
            Solitaire game;

            // Test valid inputs
            Assert::IsTrue(game.isValidTableauInput('0'), L"Input '0' should be valid.");
            Assert::IsTrue(game.isValidTableauInput('6'), L"Input '6' should be valid.");

            // Test invalid inputs
            Assert::IsFalse(game.isValidTableauInput('8'), L"Input '8' should be invalid.");
            Assert::IsFalse(game.isValidTableauInput('a'), L"Input 'a' should be invalid.");
        }

        TEST_METHOD(TestIsValidFoundationInput)
        {
            Solitaire game;

            // Test valid inputs
            Assert::IsTrue(game.isValidFoundationInput('H'), L"Input 'H' should be valid.");
            Assert::IsTrue(game.isValidFoundationInput('D'), L"Input 'D' should be valid.");

            // Test invalid inputs
            Assert::IsFalse(game.isValidFoundationInput('E'), L"Input 'E' should be invalid.");
            Assert::IsFalse(game.isValidFoundationInput('1'), L"Input '1' should be invalid.");
            Assert::IsFalse(game.isValidFoundationInput('a'), L"Input 'a' should be invalid.");
        }
    };
}