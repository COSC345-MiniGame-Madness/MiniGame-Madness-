#include <iostream>
#include "chckrs.h"
#include "screenBuffer.h"
//#include <bits/stdc++.h>

using namespace std;

int checkersGrid[8][8]; //grid
int player1 = 1, player2 = 2, currentplayer = 1; //players
bool winnerquestionmark = false; //ends game loop if true

Checkers::Checkers() // constructor
{
    populateCheckersGrid();
}

void Checkers::populateCheckersGrid() // resets grid to starting positions
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            if (i < 3 && j % 2 == 1) //player 2
            {
                checkersGrid[i][j] = 2;
            }
            else if (i > 4 && j % 2 == 0) //player 1
            {
                checkersGrid[i][j] = 1;
            }
            else
            {
                checkersGrid[i][j] = 0;
            }
        }
    }
}

void Checkers::forcejump(int playerturn) // force player to jump when another piece is within taking conditions
{
    if (playerturn == 1)
    {
        if (/*piece is king && (checkersGrid[piecex - 1][piecey + 1] == 2 && checkersGrid[piecex - 2][piecey + 2] == 0) || (checkersGrid[piecex + 1][piecey + 1] == 2 && checkersGrid[piecex + 2][piecey + 2] == 0)*/true) // backward captures
        {

        }

        if (/*(checkersGrid[piecex - 1][piecey - 1] == 2 && checkersGrid[piecex - 2][piecey - 2] == 0) || (checkersGrid[piecex + 1][piecey - 1] == 2 && checkersGrid[piecex + 2][piecey - 2] == 0)*/true) // forward captures
        {

        }
    }
    else
    {
        if (/*(checkersGrid[piecex - 1][piecey - 1] == 2 && checkersGrid[piecex - 2][piecey - 2] == 0) || (checkersGrid[piecex + 1][piecey - 1] == 2 && checkersGrid[piecex + 2][piecey - 2] == 0)*/true) // backward captures
        {

        }

        if (/*piece is king && (checkersGrid[piecex - 1][piecey + 1] == 2 && checkersGrid[piecex - 2][piecey + 2] == 0) || (checkersGrid[piecex + 1][piecey + 1] == 2 && checkersGrid[piecex + 2][piecey + 2] == 0)*/true) // forward captures
        {

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

void Checkers::playerturn(int curre) // gets player input and moves the piece specified to the space given if its within checkers rules
{
    screenBuffer.writeToScreen(0, 11, L"Player " + to_wstring(curre) + L" input move as '<piece>x y <move>x y'");

    string input = screenBuffer.getBlockingInput();

    string s;

    stringstream ss(input);

    vector<string> v;

    while (getline(ss, s, ' '))
    {
        v.push_back(s);
    }

    int piecexpos = stoi(v[0]), pieceypos = stoi(v[1]), xinp = stoi(v[2]), yinp = stoi(v[3]); // piece x position, piece y position, move to x coord, move to y coord
    bool mademove = false, correctmove = true;

    do
    {
        /*if (curre == 1)
        {*/
            while (checkersGrid[piecexpos][pieceypos] != curre || correctmove == false)
            {
                v.clear();

                screenBuffer.writeToScreen(0, 11, L"Player " + to_wstring(curre) + L" made an invalid input. re-enter input as '<piece>x y <move>x y'.");

                input = screenBuffer.getBlockingInput();

                stringstream ss(input);

                while (getline(ss, s, ' '))
                {
                    v.push_back(s);
                }

                piecexpos = stoi(v[0]), pieceypos = stoi(v[1]), xinp = stoi(v[2]), yinp = stoi(v[3]);

                correctmove = true;
            }

            correctmove = false; //ensures above loop is run if xinp and/or yinp fails

            /*Kinged piece takes an enemy piece*/ 
            if (checkersGrid[xinp][yinp] / 3 == 1 && ((checkersGrid[piecexpos - 1][pieceypos - 1] != curre && checkersGrid[piecexpos - 1][pieceypos - 1] != 0 && checkersGrid[piecexpos - 2][pieceypos - 2] == 0 && piecexpos - 2 == xinp && pieceypos - 2 == yinp) || (checkersGrid[piecexpos + 1][pieceypos - 1] != curre && checkersGrid[piecexpos + 1][pieceypos - 1] != 0 && checkersGrid[piecexpos + 2][pieceypos - 2] == 0 && piecexpos + 2 == xinp && pieceypos - 2 == yinp) || (checkersGrid[piecexpos - 1][pieceypos + 1] != curre && checkersGrid[piecexpos - 1][pieceypos + 1] != 0 && checkersGrid[piecexpos - 2][pieceypos + 2] == 0 && piecexpos - 2 == xinp && pieceypos + 2 == yinp) || (checkersGrid[piecexpos + 1][pieceypos + 1] != curre && checkersGrid[piecexpos + 1][pieceypos + 1] != 0 && checkersGrid[piecexpos + 2][pieceypos + 2] == 0 && piecexpos + 2 == xinp && pieceypos + 2 == yinp))) // backward captures
            {
                checkersGrid[xinp][yinp] = curre;
                checkersGrid[piecexpos][pieceypos] = 0;
                checkersGrid[(piecexpos + xinp) / 2][(pieceypos + yinp) / 2] = 0;
                mademove = true;
            } else
            {
                //Kinged moves to empty space
                if (checkersGrid[xinp][yinp] / 3 == 1 && ((checkersGrid[piecexpos - 1][pieceypos - 1]  == 0 && piecexpos - 1 == xinp && pieceypos - 1 == yinp) || (checkersGrid[piecexpos + 1][pieceypos - 1] == 0 && piecexpos + 1 == xinp && pieceypos - 1 == yinp) || (checkersGrid[piecexpos - 1][pieceypos + 1] == 0 && piecexpos - 1 == xinp && pieceypos + 1 == yinp) || (checkersGrid[piecexpos + 1][pieceypos + 1] == 0 && piecexpos + 1 == xinp && pieceypos + 1 == yinp)))
                {
                    checkersGrid[xinp][yinp] = curre;
                    checkersGrid[piecexpos][pieceypos] = 0;
                    mademove = true;
                } else
                {
                    int posmod;

                    if (curre == 1) //player 1
                    {
                        posmod = 1;
                    } else //player 2
                    {
                        posmod = -1;
                    }
                    
                    //Non-Kinged piece takes piece
                    if (checkersGrid[xinp][yinp] / 3 == 0 && ((checkersGrid[piecexpos - posmod][pieceypos - posmod] != curre && checkersGrid[piecexpos - posmod][pieceypos - posmod] != 0 && checkersGrid[piecexpos - (posmod * 2)][pieceypos - (posmod * 2)] == 0 && piecexpos - (posmod * 2) == xinp && pieceypos - (posmod * 2) == yinp) || (checkersGrid[piecexpos + posmod][pieceypos - posmod] != curre && checkersGrid[piecexpos + posmod][pieceypos - posmod] != 0 && checkersGrid[piecexpos + (posmod * 2)][pieceypos - (posmod * 2)] == 0 && piecexpos + (posmod * 2) == xinp && pieceypos - (posmod * 2) == yinp)))
                    {
                        checkersGrid[xinp][yinp] = curre;

                        if (curre == 1 && xinp == 0)
                        {
                            checkersGrid[xinp][yinp] = checkersGrid[xinp][yinp] + 2;
                        } else if (curre == 2 && xinp == 7)
                        {
                            checkersGrid[xinp][yinp] = checkersGrid[xinp][yinp] + 2;
                        }

                        checkersGrid[piecexpos][pieceypos] = 0;
                        checkersGrid[(piecexpos + xinp) / 2][(pieceypos + yinp) / 2] = 0;
                        mademove = true;
                    } else
                    {
                        //Non-Kinged moves to empty space
                        if (checkersGrid[xinp][yinp] / 3 == 0 && ((checkersGrid[piecexpos - posmod][pieceypos - posmod] == 0 && piecexpos - posmod == xinp && pieceypos - posmod == yinp) || (checkersGrid[piecexpos + posmod][pieceypos - posmod] == 0 && piecexpos - posmod == xinp && pieceypos - posmod == yinp)))
                        {
                            checkersGrid[xinp][yinp] = curre;
                            checkersGrid[piecexpos][pieceypos] = 0;
                            mademove = true;
                        }
                    }
                }
                    
            }

            v.clear();

        /*}
        else
        {
            while (checkersGrid[piecexpos][pieceypos] != curre)
            {
                v.clear();

                screenBuffer.writeToScreen(0, 11, L"Player " + to_wstring(curre) + L" doesn't own the piece at x: " + to_wstring(xinp) + L" y: " + to_wstring(yinp) + L". re-enter co-ordinates.");

                input = screenBuffer.getBlockingInput();

                stringstream ss(input);

                while (getline(ss, s, ' '))
                {
                    v.push_back(s);
                }
            }
            //Kinged piece 
            if (checkersGrid[xinp][yinp] / 3 == 1 && ((checkersGrid[piecexpos - 1][pieceypos + 1] == 2 && checkersGrid[piecexpos - 2][pieceypos + 2] == 0) || (checkersGrid[piecexpos + 1][pieceypos + 1] == 2 && checkersGrid[piecexpos + 2][pieceypos + 2] == 0 || checkersGrid[piecexpos - 1][pieceypos - 1] == 2 && checkersGrid[piecexpos - 2][pieceypos - 2] == 0) || (checkersGrid[piecexpos + 1][pieceypos - 1] == 2 && checkersGrid[piecexpos + 2][pieceypos - 2] == 0))) // backward captures
            {
                checkersGrid[xinp][yinp] = curre;
                checkersGrid[piecexpos][pieceypos] = 0;
                mademove = true;
            } else
            {
                //Non-Kinged piece
                if (checkersGrid[xinp][yinp] / 3 == 0  && ((checkersGrid[piecexpos - 1][pieceypos + 1] == 2 && checkersGrid[piecexpos - 2][pieceypos + 2] == 0) || (checkersGrid[piecexpos + 1][pieceypos + 1] == 2 && checkersGrid[piecexpos + 2][pieceypos + 2] == 0)))
                {
                    checkersGrid[xinp][yinp] = curre;
                    checkersGrid[piecexpos][pieceypos] = 0;
                    mademove = true;
                }
            }
        }*/
    } while (mademove == false);
    
    
}

/*
void Checkers::move(int playerturn) // moves piece to given location
{
    if (playerturn == 1)
    {

    }
}*/

int Checkers::randomstarter() // chooses a random starter
{
    return 1 + (rand() % 2);
}

void Checkers::swapturn(int playert) //swaps player turns
{
    if (playert == 1)
    {
        currentplayer = 2;
    }
    else {
        currentplayer = 1;
    }
}

void Checkers::display() // write the grid to screen buffer
{
    screenBuffer.writeToScreen(6, 0, L"1   2   3   4   5   6   7   8");
    screenBuffer.writeToScreen(4, 1, L"________________________________");

    int offset = 2;

    for (int row = 0; row < 9; row++)
    {
        wstring rowDisplay = to_wstring(row + 1) + L" |";

        for (int col = 0; col < 9; col++)
        {
            wstring value = to_wstring(grid[row][col]);

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
    populateCheckersGrid();

    while (winnerquestionmark == false)
    {
        playerturn(currentplayer);

        checkwin();

        swapturn(currentplayer);
    }

    swapturn(currentplayer);

    screenBuffer.writeToScreen(0, 14, L"Player " + to_wstring(currentplayer) + L" wins.");

    string see = "seel";
    cout << see;
}