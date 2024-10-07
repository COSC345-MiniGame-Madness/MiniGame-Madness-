#include <iostream>
#include "chckrs.h"
#include "screenBuffer.h"
#include <bits/stdc++.h>

using namespace std;

int checkersGrid[8][8];
int player1 = 1, player2 = 2, currentplaying = 1;
bool winnerquestionmark = false;

Checkers::Checkers()
{
    populateCheckersGrid();
}

void Checkers::populateCheckersGrid()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            if (i < 3 && j % 2 == 1)
            {
                checkersGrid[i][j] = 1;
            }
            else if (i > 4 && j % 2 == 0)
            {
                checkersGrid[i][j] = 2;
            }
            else
            {
                checkersGrid[i][j] = 0;
            }
        }
    }
}

void Checkers::forcejump(int playerturn) // piece should be like x 1, y 0 as 10
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

void Checkers::checkwin()
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

            }

            cout << "\t " << (j + 1) << "shit";
        }
    }
}

void Checkers::playerturn(int curre)
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

    int piecexpos = stoi(v[0]), pieceypos = stoi(v[1]), xinp = stoi(v[2]), yinp = stoi(v[3]);

    if (curre == 1)
    {
        while (checkersGrid[xinp][yinp] != curre)
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

        if (checkersGrid[xinp][yinp] / 3 == 1 && ((checkersGrid[piecexpos - 1][pieceypos + 1] == 2 && checkersGrid[piecexpos - 2][pieceypos + 2] == 0) || (checkersGrid[piecexpos + 1][pieceypos + 1] == 2 && checkersGrid[piecexpos + 2][pieceypos + 2] == 0 || checkersGrid[piecexpos - 1][pieceypos - 1] == 2 && checkersGrid[piecexpos - 2][pieceypos - 2] == 0) || (checkersGrid[piecexpos + 1][pieceypos - 1] == 2 && checkersGrid[piecexpos + 2][pieceypos - 2] == 0))) // backward captures
        {

        } else
        {

        }

        if ()
        {

        }
    }
    else
    {
        if (/*(checkersGrid[piecex - 1][piecey - 1] == 2 && checkersGrid[piecex - 2][piecey - 2] == 0) || (checkersGrid[piecex + 1][piecey - 1] == 2 && checkersGrid[piecex + 2][piecey - 2] == 0)*/true) // backward captures
        {

        } else
        {

        }
    }
}

void Checkers::move(int playerturn)
{
    if (playerturn == 1)
    {

    }
}

int Checkers::randomstarter()
{
    return 1 + (rand() % 2);
}

void Checkers::swapturn(int playert)
{
    if (playert == 1)
    {
        currentplaying = 2;
    }
    else {
        currentplaying = 1;
    }
}

void Checkers::display()
{
    cout << "\t 1 \t 2 \t 3 \t 4 \t 5 \t 6 \t 7 \t 8 \n";

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; i < 7; i++)
        {
            cout << "\t " << (j + 1) << "shit";
        }
    }
}

void Checkers::checkersGam()
{
    populateCheckersGrid();

    while (winnerquestionmark == false)
    {
        playerturn(currentplaying);

        checkwin();

        //checkdraw();

        swapturn(currentplaying);
    }

    string see = "seel";
    cout << see;
}