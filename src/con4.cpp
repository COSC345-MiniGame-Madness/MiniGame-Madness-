#include <iostream>
#include "con4.h"
#include "screenBuffer.h"
/*
int grid[6][7] = { 0 };
int player1 = 1, player2 = 2; //1 for player 1, 2 for 2, 0 for empty space.*/
int currentplayer;
bool winquestionmark = false;

Con4::Con4()
{
	populategrid();
}

void Con4::endgame(bool surrender) // end game
{
    if (surrender == false)
    {
        screenBuffer.writeToScreen(0, 16, L"player " + to_wstring(currentplayer) + L" wins.");

        screenBuffer.getBlockingInput();
    }

    winquestionmark = true;
}

void Con4::playerturn(int player)
{
    screenBuffer.writeToScreen(0, 14, L"player " + to_wstring(player) + L"'s turn. Select a column to drop a coin.  ");

    string diff = screenBuffer.getBlockingInput();

    bool repeat = true;

    while(repeat)
    {
        if (stoi(diff) == 9)
        {
            repeat = false;

            endgame(true);
        }
        else if (stoi(diff) >= 1 && stoi(diff) <= 7)
        {
            repeat = false;

            dropcoin(stoi(diff), player);
        }
        else
        {
            screenBuffer.writeToScreen(0, 16, L"Invalid input. Choose between 1 and 7.");

            //screenBuffer.getBlockingInput();
        }
    }
}

void Con4::dropcoin(int column, int playercoin)
{
    for (int i = 5; i >= 0; i--)
    {
        if (grid[i][column - 1] == 0)
        {
            grid[i][column - 1] = playercoin;
            
            screenBuffer.writeToScreen(0, 16, L"Dropping coin in column: " + to_wstring(column - 1));

            //screenBuffer.getBlockingInput();

            break;
        }
    }
}

void Con4::populategrid()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Con4::checkdraw()
{
    bool full = true;

    for(int i = 0; i < 7; i++)
    {
        if(grid[i][0] == 0)
        {
            full = false;
        }
    }

    if(full == true)
    {
        endgame(false);
    }
}

void Con4::checkwin()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if (j < 4 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] && grid[i][j] == grid[i][j + 3] && grid[i][j] != 0) // horizontal
            {
                endgame(false);
            }
            
            if (i < 3 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 3][j] && grid[i][j] != 0) // vertical
            {
                endgame(false);
            }

            if (i < 3 && j < 4 && grid[i][j] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 2] && grid[i][j] == grid[i + 3][j + 3] && grid[i][j] != 0) // diagonal down right
            {
                endgame(false);
            }

            if (i > 3 && j < 4 && grid[i][j] == grid[i - 1][j + 1] && grid[i][j] == grid[i - 2][j + 2] && grid[i][j] == grid[i - 3][j + 3] && grid[i][j] != 0) // diagonal down left
            {
                endgame(false);
            }
        }
    }
}

int Con4::randomstarter()
{
    return 1 + (rand() % 2);
}

int Con4::swapturn(int playert)
{
    if (playert == 1)
    {
        return 2;
    }
    else 
    {
        return 1;
    }
}

void Con4::display()
{
    screenBuffer.writeToScreen(5, 0, L"1   2   3   4   5   6   7");
    screenBuffer.writeToScreen(3, 1, L"_____________________________");

    int offset = 2;

    for (int i = 0; i < 6; i++)
    {
        std::wstring row = L" |";

        for (int o = 0; o < 7; o++)
        {
            row += L" " + to_wstring(grid[i][o]) + L" |";
        }
        
        screenBuffer.writeToScreen(2, offset++, row);

        screenBuffer.writeToScreen(3, offset++, L"-----------------------------");
    }

    screenBuffer.writeToScreen(3, offset++, L"-------------" + to_wstring(grid[4][6])); // gives number when dropping in column 1. FIX
}

int Con4::connect4()
{
    winquestionmark = false;

    screenBuffer.setActive();

    populategrid();

    currentplayer = randomstarter();
    /**/
    do
    {
        currentplayer = swapturn(currentplayer);

        display();

        playerturn(currentplayer);
        
        screenBuffer.clearScreen();
        
        checkwin();

        checkdraw();

    } while (winquestionmark == false);

    screenBuffer.clearScreen();

    return 0;
    // sysout player # wins
}