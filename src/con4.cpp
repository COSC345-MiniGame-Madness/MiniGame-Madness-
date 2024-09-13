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

bool Con4::endgame() // 
{
    return false;
}

void Con4::playerturn(int player)
{
    screenBuffer.writeToScreen(0, 14, L"player " + to_wstring(player) + L"'s turn. Select a column to drop a coin.  ");

    string diff = screenBuffer.getBlockingInput();

    if (stoi(diff) == 9)
    {

    }
    else
    {
        dropcoin(stoi(diff), player);
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

void Con4::dropcoin(int column, int playercoin)
{
    for (int i = 0; i < 6; i++)
    {
        if (grid[column][i+1] != 0 || i == 6)
        {
            grid[column][i] = playercoin;
            
            break;
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
        endgame();
    }
}

void Con4::checkwin()
{
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; i < 7; i++)
        {
            if(i < 5) // horizontal, diagonal right
            {
                if (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j])
                {
                    endgame();
                }

                if (j < 3) // vertical
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2] && grid[i + 2][j + 2] == grid[i + 3][j + 3])
                    {
                        endgame();
                    }
                }
            }

            if (i > 3 && j < 3) // diagonal left
            {
                if (grid[i][j] == grid[i - 1][j + 1] && grid[i - 1][j + 1] == grid[i - 2][j + 2] && grid[i - 2][j + 2] == grid[i - 3][j + 3])
                {
                    endgame();
                }
            }

            if (j < 3) // vertical
            {
                if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3])
                {
                    endgame();
                }
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
    else {
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
}

int Con4::connect4()
{
    screenBuffer.setActive();
    /*screenBuffer.writeToScreen(0, 0, L"asdfghjk");
    screenBuffer.getBlockingInput();
    cout << "Hello World";*/

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

        swapturn(currentplayer);

    } while (winquestionmark == false);

    screenBuffer.clearScreen();

    return 0;
    // sysout player # wins
}