#include <iostream>
#include <string>

//char grid[][];
int wide = 8;
bool finquestionmark = false, winquestionmark = false, kaboomquestionmark = false;

bool endgame() // g
{
    return false;
}

void populategrid(char diff)
{
    int max, min, mines;

    do
    {
        if (diff == 'e')
        {
            wide = 8;
            max = 10;
            min = 8;
        } else if (diff == 'm')
        {
            wide = 14;
            max = 10;
            min = 8;
        } else if (diff == 'h')
        {
            wide = 25;
            max = 10;
            min = 8;
        }
    } while (diff);
    
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
    for(int i = 0; i < wide; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            
        }
    }
}

void kaboom()
{
    kaboomquestionmark = true;
}

void makemove(int xcoords, int ycoords)
{
    if 
}

int minsweep()
{
    char difficulty = 'x';

    do
    {
        printf("choose difficulty: e for easy, m for medium, h for hard\n");
        scanf("%c", &difficulty); // choose difficulty
    } 
    while (difficulty != 'e' && difficulty != 'm' && difficulty != 'h');

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

        makemove()
    }

    endgame();
}