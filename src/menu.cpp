#include "menu.h"

// Initialize games
Hnefatafl hnefataflGame;
Solitaire solitaireGame;

NaughtsxCrossess naughtsxCrossessGame;
Hangman hangmanGame;
WordScrambler wordScramblerGame;
BattleshipGame battleshipGame;
Minsweep minesweeper;
Con4 con4Game;

Minsweep minesweeper;

// Input function to start each game
int Menu::startGame(int input)
{
	int output = RETURN_TO_MENU;

    switch (input)
    {
    case 1:
        // Call function to start Hangman
        hangmanGame.hangman();
        break;
    case 2:
        // Call function to start Connect 4
        output = con4Game.connect4();
        break;
    case 3:
        // Call function to start Naughts and Crosses
		naughtsxCrossessGame.run();
        break;
    case 4:
        // Call the class to start Hnefatafl
        output = hnefataflGame.run();
        break;
    case 5:
        // Call function to start Word Scramble
        wordScramblerGame.run();
        break;
    case 6:
        // Call function to start Battleship
        battleshipGame.run();
        break;
    case 7:
        // Call function to start Minesweeper
        //screenBuffer.writeToScreen(75, startY + row, L"Coming Soon", ScreenBuffer::RED, ScreenBuffer::BACKGROUND_NORMAL);
        minesweeper.minesweep();
        break;
    case 8:
        // Exit the program
		output = EXIT_GAME;
        break;
    default: break;
    }

	return output;
}


// Main menu function to display the menu options
int Menu::displayMenu()
{
    try
    {
        // Set cursor visibility
        screenBuffer.setCursorVisibility(false);
		screenBuffer.clearScreen();

        // Define menu options
        std::wstring text[] = {
            L"MINIGAME MADNESS",
            L"Hangman",
            L"Connect 4",
            L"Naughts and Crosses",
            L"Hnefatafl",
            L"Word Scramble",
            L"Battleship",
            L"Minesweeper",
            L"Exit",
        };

        // Print menu options to the console 
        width = screenBuffer.getScreenWidth();
        startY = 2; // Starting row position
        padding = 0;

        // Display all menu options centered
        for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++)
        {
            padding = (width / 2) - (static_cast<int>(text[i].size()) / 2);
            screenBuffer.writeToScreen(padding, startY + i, text[i]);
        }

        // Highlight the first option
        row = 1;
        padding = (width / 2) - (static_cast<int>(text[1].size()) / 2);
        screenBuffer.writeToScreen(padding, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, 4);

        // Set screen buffer to active
        screenBuffer.setActive();

        int output = -1;

        while (output == -1) {
            int ch = _getch();  // Read first input character

            // Arrow keys send two codes, so we need to check the first and read the second
            if (ch == 0 || ch == 224) {  // Arrow keys usually start with 0 or 224
                ch = _getch();  // Get the second code

                switch (ch) {
                case 72:  // Up arrow
                    if (row > 1) {
                        // Deselect current option
                        padding = (width / 2) - (static_cast<int>(text[row].size()) / 2);
                        screenBuffer.writeToScreen(padding, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BACKGROUND_NORMAL);
                        row--;
                        // Highlight new option
                        padding = (width / 2) - (static_cast<int>(text[row].size()) / 2);
                        screenBuffer.writeToScreen(padding, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, 4);
                    }
                    break;
                case 80:  // Down arrow
                    if (row < 9) {
                        // Deselect current option
                        padding = (width / 2) - (static_cast<int>(text[row].size()) / 2);
                        screenBuffer.writeToScreen(padding, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BACKGROUND_NORMAL);
                        row++;
                        // Highlight new option
                        padding = (width / 2) - (static_cast<int>(text[row].size()) / 2);
                        screenBuffer.writeToScreen(padding, startY + row, text[row], ScreenBuffer::FOREGROUND_NORMAL, 4);
                    }
                    break;
                }
            }
            else if (ch == 13) {  // Enter key
                output = startGame(row);
            }
        }
        return output;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return EXIT_GAME;
}

