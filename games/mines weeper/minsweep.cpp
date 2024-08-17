#include <iostream>
#include <string>

//char grid[][];
int wide;
bool finquestionmark = false, winquestionmark = false, kaboomquestionmark = false;

bool endgame() // g
{
    return false;
}

void populategrid(char diff)
{
    int max, min, mines;

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
    
    char grid[wide][wide];

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
        grid[rand() % wide][rand() % wide] = 9;
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

int main()
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
    }
}