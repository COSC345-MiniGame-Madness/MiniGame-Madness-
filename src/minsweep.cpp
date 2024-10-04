#include <iostream>
#include "minsweep.h"
#include "screenBuffer.h"

//char grid[][];
int widened = 8;
bool finquestionmark = false, winquestionmark = false, kaboomquestionmark = false;

void endgame() // g
{
    winquestionmark = false;
}

void populategrid(string diff)
{
    int max, min, mines, wide = 8;

    if (diff == "e")
    {
        wide = 8;
        max = 10;
        min = 8;
    } else if (diff == "m")
    {
        wide = 14;
        max = 10;
        min = 8;
    } else if (diff == "h")
    {
        wide = 25;
        max = 10;
        min = 8;
    }
    
    widened = wide;
    int grid[wide][wide];

    mines = min + (rand() % max);

    for(int i = 0; i < wide; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            grid[i][j] = 0;
        }
    }

    while(mines > 0)
    {
        int xrand = rand() % wide, yrand = rand() % wide;
        grid[xrand][yrand] = 9;

        if (xrand != 0) // == 0? or != 0? for EVERY grid pos
        {
            grid[xrand + 1][yrand] += 1;

            if (yrand != 0)
            {
                grid[xrand + 1][yrand + 1] += 1;
            }

            if (yrand != wide - 1)
            {
                grid[xrand + 1][yrand - 1] += 1;
            }
        }

        if (xrand != wide - 1)
        {
            grid[xrand - 1][yrand] += 1;

            if (yrand != 0)
            {
                grid[xrand][yrand + 1] += 1;
            }

            if (yrand != wide - 1)
            {
                grid[xrand - 1][yrand - 1] += 1;
            }
        }

        if (yrand != 0)
        {
            grid[xrand][yrand + 1] += 1;
        }

        if (yrand != wide - 1)
        {
            grid[xrand][yrand - 1] += 1;
        }

        mines--;
    }
}

void checkwin()
{
    for(int i = 0; i < widened; i++)
    {
        for(int j = 0; j < widened; j++)
        {
            
        }
    }
}

void kaboom()
{
    kaboomquestionmark = true;
}

void makemove(/*int xcoords, int ycoords*/)
{
    screenBuffer.writeToScreen(0, 16, L"Enter coordinates in format of 'x y'");
    string input = screenBuffer.getBlockingInput();

    int xinp = stoi(""), yinp = stoi("");

    
}

int minsweep()
{
    string difficulty = "x";

    do
    {
        screenBuffer.writeToScreen(0, 14, L"choose difficulty: e for easy, m for medium, h for hard\n");
        difficulty = screenBuffer.getBlockingInput(); // choose difficulty
    } 
    while (difficulty != "e" && difficulty != "m" && difficulty != "h");

    populategrid(difficulty);

    bool win;

    while (finquestionmark == false)
    {
        if (kaboomquestionmark == true)
        {
            win = false;
            break;
        }

        checkwin();

        if (winquestionmark == true)
        {
            win = true;
            break;
        }

        makemove();
    }

    endgame();
}