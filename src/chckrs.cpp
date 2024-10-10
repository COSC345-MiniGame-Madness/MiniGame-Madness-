#include <iostream>
#include "chckrs.h"
#include "screenBuffer.h"

using namespace std;

int checkersGrid[8][8]; // grid
int player1 = 1, player2 = 2, currentplayer = 1; // players
bool winnerquestionmark = false; // ends game loop if true

Checkers::Checkers() // constructor
{
    populateCheckersGrid();
}

void Checkers::populateCheckersGrid() // resets grid to starting positions
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if (i < 3 && j % 2 == 1) 
            {
                checkersGrid[i][j] = 2; // Player 2's pieces
            }
            else if (i > 4 && j % 2 == 0) 
            {
                checkersGrid[i][j] = 1; // Player 1's pieces
            }
            else 
            {
                checkersGrid[i][j] = 0; // Empty squares
            }
        }
    }

}

void Checkers::forcejump(int playerturn) 
{
    int opponent = (playerturn == 1) ? 2 : 1;

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if (checkersGrid[i][j] == playerturn) // Check diagonal jumps for normal pieces
            {
                if (playerturn == 1) // Player 1 moves upwards
                { 
                    if (i > 1 && j > 1 && checkersGrid[i - 1][j - 1] == opponent && checkersGrid[i - 2][j - 2] == 0) // A forced jump is possible
                    {
                        screenBuffer.writeToScreen(0, 15, L"Player " + to_wstring(playerturn) + L" must jump at (" + to_wstring(i) + L", " + to_wstring(j) + L")");
                        
                        return;
                    }

                    if (i > 1 && j < 6 && checkersGrid[i - 1][j + 1] == opponent && checkersGrid[i - 2][j + 2] == 0) 
                    {
                        screenBuffer.writeToScreen(0, 15, L"Player " + to_wstring(playerturn) + L" must jump at (" + to_wstring(i) + L", " + to_wstring(j) + L")");
                        
                        return;
                    }
                } else // Player 2 moves downwards
                { 
                    if (i < 6 && j > 1 && checkersGrid[i + 1][j - 1] == opponent && checkersGrid[i + 2][j - 2] == 0) 
                    {
                        screenBuffer.writeToScreen(0, 15, L"Player " + to_wstring(playerturn) + L" must jump at (" + to_wstring(i) + L", " + to_wstring(j) + L")");
                        
                        return;
                    }

                    if (i < 6 && j < 6 && checkersGrid[i + 1][j + 1] == opponent && checkersGrid[i + 2][j + 2] == 0) 
                    {
                        screenBuffer.writeToScreen(0, 15, L"Player " + to_wstring(playerturn) + L" must jump at (" + to_wstring(i) + L", " + to_wstring(j) + L")");

                        return;
                    }
                }
            }
        }
    }
}

void Checkers::checkwin() //checks if any of the players' pieces are still on the grid
{
    bool one = false, two = false;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            if (checkersGrid[i][j] == 1)
            {
                one = true;
            }
            else if (checkersGrid[i][j] == 2)
            {
                two = true;
            }
        }
    }

    if(one == false || two == false) // game over check
    {
        winnerquestionmark = true;
    }
}

void Checkers::playerturn(int curre) 
{
    screenBuffer.writeToScreen(0, 11, L"Player " + to_wstring(curre) + L", input move as '<piece>x y <move>x y':");

    string input = screenBuffer.getBlockingInput();

    stringstream ss(input);

    vector<int> moveCoords;

    for (string s; ss >> s;) 
    {
        moveCoords.push_back(stoi(s));
    }

    int piecexpos = moveCoords[0], pieceypos = moveCoords[1];
    int xinp = moveCoords[2], yinp = moveCoords[3];
    
    while (checkersGrid[piecexpos][pieceypos] % 3 != curre) // Validate that the selected piece belongs to the current player
    {
        screenBuffer.writeToScreen(0, 11, L"Invalid selection. Re-enter move.");

        input = screenBuffer.getBlockingInput();

        moveCoords.clear();

        stringstream newSS(input);

        for (string s; newSS >> s;) 
        {
            moveCoords.push_back(stoi(s));
        }
        piecexpos = moveCoords[0];
        pieceypos = moveCoords[1];

        xinp = moveCoords[2];
        yinp = moveCoords[3];
    }

    bool mademove = false;
    int pieceValue = checkersGrid[piecexpos][pieceypos];

    bool isKing = (pieceValue >= 3); // Check if the piece is a king (pieceValue >= 3)

    if (!isKing) // Normal piece logic
    { 
        if (curre == 1 && xinp == piecexpos - 1 && abs(yinp - pieceypos) == 1 && checkersGrid[xinp][yinp] == 0) // Regular move for player 1
        {
            checkersGrid[xinp][yinp] = curre;
            checkersGrid[piecexpos][pieceypos] = 0;

            mademove = true;

            if (xinp == 0) // Promote to king if player 1 reaches the top row
            {
                checkersGrid[xinp][yinp] += 2;
            }
        }
        else if (curre == 2 && xinp == piecexpos + 1 && abs(yinp - pieceypos) == 1 && checkersGrid[xinp][yinp] == 0) // Regular move for player 2
        {
            checkersGrid[xinp][yinp] = curre;
            checkersGrid[piecexpos][pieceypos] = 0;

            mademove = true;

            if (xinp == 7) // Promote to king if player 2 reaches the bottom row
            {
                checkersGrid[xinp][yinp] += 2;
            }
        }
    }

    if (!mademove) // Handle jump (capture)
    {
        int jumpx = (piecexpos + xinp) / 2;
        int jumpy = (pieceypos + yinp) / 2;

        if (curre == 1 && xinp == piecexpos - 2 && abs(yinp - pieceypos) == 2 && checkersGrid[jumpx][jumpy] % 3 == 2 && checkersGrid[xinp][yinp] == 0) // Player 1 jumps over player 2's piece
        {
            checkersGrid[xinp][yinp] = curre;
            checkersGrid[piecexpos][pieceypos] = 0;
            checkersGrid[jumpx][jumpy] = 0;

            mademove = true;

            if (xinp == 0) // Promote to king if player 1 reaches the top row
            {
                checkersGrid[xinp][yinp] += 2;
            }
        }
        else if (curre == 2 && xinp == piecexpos + 2 && abs(yinp - pieceypos) == 2 && checkersGrid[jumpx][jumpy] % 3 == 1 && checkersGrid[xinp][yinp] == 0) // Player 2 jumps over player 1's piece
        {
            checkersGrid[xinp][yinp] = curre;
            checkersGrid[piecexpos][pieceypos] = 0;
            checkersGrid[jumpx][jumpy] = 0;

            mademove = true;
            
            if (xinp == 7) // Promote to king if player 2 reaches the bottom row
            {
                checkersGrid[xinp][yinp] += 2;
            }
        }
    }
    
    if (isKing && !mademove) // Handle king piece logic (both forward and backward moves)
    {
        if (abs(xinp - piecexpos) == 1 && abs(yinp - pieceypos) == 1 && checkersGrid[xinp][yinp] == 0) // King moves
        {
            checkersGrid[xinp][yinp] = pieceValue;
            checkersGrid[piecexpos][pieceypos] = 0;

            mademove = true;
        }
        else if (abs(xinp - piecexpos) == 2 && abs(yinp - pieceypos) == 2) // King captures
        {
            int jumpx = (piecexpos + xinp) / 2;
            int jumpy = (pieceypos + yinp) / 2;

            if (checkersGrid[jumpx][jumpy] % 3 != curre && checkersGrid[jumpx][jumpy] != 0 && checkersGrid[xinp][yinp] == 0) 
            {
                checkersGrid[xinp][yinp] = pieceValue;
                checkersGrid[piecexpos][pieceypos] = 0;
                checkersGrid[jumpx][jumpy] = 0;

                mademove = true;
            }
        }
    }

    if (!mademove) 
    {
        screenBuffer.writeToScreen(0, 11, L"Invalid move. Try again.");
    }
}


int Checkers::randomstarter() // chooses a random starter
{
    return 1 + (rand() % 2);
}

void Checkers::swapturn(int playert) //swaps player turns
{
    if (playert == 1)
    {
        currentplayer = 2;
    } else 
    {
        currentplayer = 1;
    }
}

void Checkers::display() 
{
    screenBuffer.writeToScreen(6, 0, L"1   2   3   4   5   6   7   8");
    screenBuffer.writeToScreen(4, 1, L"________________________________");

    int offset = 2;

    for (int row = 0; row < 8; row++) 
    {
        wstring rowDisplay = to_wstring(row + 1) + L" |";

        for (int col = 0; col < 8; col++) 
        {
            wstring value = to_wstring(checkersGrid[row][col]);

            if (value == L"0") 
            {
                rowDisplay += L"   |";
            }
            else 
            {
                rowDisplay += L" " + value + L" |";
            }
        }

        screenBuffer.writeToScreen(2, offset++, rowDisplay);
        screenBuffer.writeToScreen(4, offset++, L"--------------------------------");
    }
}


void Checkers::checkersGam() // class is called from menu
{
    screenBuffer.setActive();

    populateCheckersGrid();

    while (!winnerquestionmark)
    {
        playerturn(currentplayer);

        screenBuffer.clear();

        display();

        checkwin();

        swapturn(currentplayer);
    }

    swapturn(currentplayer);

    screenBuffer.writeToScreen(0, 14, L"Player " + to_wstring(currentplayer) + L" wins.");
}