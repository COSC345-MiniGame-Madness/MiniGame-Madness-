#include <iostream>
#include <sstream>
#include "minesweep.h"

int widened = 8;

int grid[25][25]; // grid and revealed arrays
bool revealed[25][25];

void Minsweep::endgame()
{
    winquestionmark = true;
}

void Minsweep::populategrid(string diff)
{
    int max, min, mines;

    if (diff == "e")
    {
        widened = 8;
        max = 10;
        min = 8;
    }
    else if (diff == "m")
    {
        widened = 14;
        max = 10;
        min = 8;
    }
    else if (diff == "h")
    {
        widened = 25;
        max = 10;
        min = 8;
    }

    mines = min + (rand() % max);

    for (int i = 0; i < widened; i++) // initialize grid and revealed arrays
    {
        for (int j = 0; j < widened; j++)
        {
            grid[i][j] = 0;
            revealed[i][j] = false;
        }
    }

    while (mines > 0) // place mines
    {
        int xrand = rand() % widened, yrand = rand() % widened;

        if (grid[xrand][yrand] != 9)
        {
            grid[xrand][yrand] = 9; // Mine
            mines--;

            for (int dx = -1; dx <= 1; dx++) // update neighbors
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int nx = xrand + dx, ny = yrand + dy;

                    if (nx >= 0 && nx < widened && ny >= 0 && ny < widened && grid[nx][ny] != 9)
                    {
                        grid[nx][ny]++;
                    }
                }
            }
        }
    }
}

void Minsweep::floodFill(int x, int y)
{
    if (x < 0 || x >= widened || y < 0 || y >= widened) // check if coords within grid
    {
        return;
    }

    if (revealed[x][y] || grid[x][y] == 9) // If cell already revealed or is a mine, stop
    {
        return;
    }

    revealed[x][y] = true; // reveal current cell

    if (grid[x][y] != 0) // if current cell not empty, don't continue
    {
        return;
    }

    for (int dx = -1; dx <= 1; dx++) // recursively reveal adjacent cells (8 directions)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0) // exclude center cell
            {
                floodFill(x + dx, y + dy);
            }
        }
    }
}

void Minsweep::checkwin()
{
    for (int i = 0; i < widened; i++)
    {
        for (int j = 0; j < widened; j++)
        {
            if (grid[i][j] != 9 && !revealed[i][j])
            {
                return; // still tiles to reveal
            }
        }
    }
    winquestionmark = true; // all non-mine tiles are revealed
}

void Minsweep::kaboom()
{
    kaboomquestionmark = true;
}

void Minsweep::makemove()
{
    screenBuffer.writeToScreen(0, 16, L"Enter coordinates in format of 'x y'");

    string input = screenBuffer.getBlockingInput();

    istringstream ss(input);

    int xinp, yinp;

    ss >> xinp >> yinp;

    if (xinp < 0 || xinp >= widened || yinp < 0 || yinp >= widened)
    {
        screenBuffer.writeToScreen(0, 18, L"Invalid coordinates, try again");
        return;
    }

    if (grid[xinp][yinp] == 9) // mine
    {
        kaboom();
    }
    else
    {
        revealed[xinp][yinp] = true; // reveal the selected cell

        if (grid[xinp][yinp] == 0) // if selected cell empty, perform flood fill
        {
            floodFill(xinp, yinp);
        }
    }
}

void Minsweep::display()
{
    for (int i = 0; i < widened; i++)
    {
        for (int j = 0; j < widened; j++)
        {
            if (revealed[i][j])
            {
                if (grid[i][j] == 9)
                {
                    screenBuffer.writeToScreen(i, j, L"M"); // mine
                }
                else
                {
                    screenBuffer.writeToScreen(i, j, to_wstring(grid[i][j]));
                }
            }
            else
            {
                screenBuffer.writeToScreen(i, j, L"*"); // unrevealed
            }
        }
    }
}

int Minsweep::minesweep()
{
    screenBuffer.setActive();
    string difficulty = "x";

    do
    {
        screenBuffer.writeToScreen(0, 14, L"Choose difficulty: e for easy, m for medium, h for hard\n");

        difficulty = screenBuffer.getBlockingInput(); // choose difficulty
    } while (difficulty != "e" && difficulty != "m" && difficulty != "h");

    populategrid(difficulty);

    bool win = false;

    while (!finquestionmark)
    {
        if (kaboomquestionmark)
        {
            win = false;
            break;
        }

        checkwin();

        if (winquestionmark)
        {
            win = true;
            break;
        }

        display(); // show current state of grid
        makemove();    // let player make a move
    }

    endgame();

    if (win) // return win status
    {
        screenBuffer.writeToScreen(0, 20, L"Congratulations! You won!\n");
    }
    else
    {
        screenBuffer.writeToScreen(0, 20, L"You hit a mine. Game Over.\n");
    }

    return win ? 1 : 0;
}