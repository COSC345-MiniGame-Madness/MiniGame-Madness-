#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include <locale>
#include <codecvt>
#include "sudokuuuu.h"
#include "screenBuffer.h"

using namespace std;

Sudokuuuu::Sudokuuuu()
{
    generate(input); // Generate a randomized Sudoku grid
}

bool Sudokuuuu::uniquequestionmark(int grid[9][9], int row, int col, int num)
{
    // Check if num is present in the row or column
    for (int x = 0; x < 9; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num)
        {
            return false;
        }
    }

    // Check if num is present in the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

void Sudokuuuu::enternum(int grid[9][9])
{
    int answer, x, y;

    bool numbercheck = false;

    do // Repeats until valid input is given
    {
        screenBuffer.writeToScreen(0, 21, L"Enter number and coordinates in the format 'number row*column'");

        screenBuffer.writeToScreen(0, 22, L"or type in '9999' to surrender: ");

        string input = screenBuffer.getBlockingInput(); // Capture input using screenBuffer

        if (stoi(input) == 9999)
        {
            surrender = true, numbercheck = true;
            answer = 0, x = 0, y = 0;
        } else
        {
            wstring_convert<codecvt_utf8<wchar_t>> converter;

            wstring wide_input = converter.from_bytes(input);

            try {
                size_t pos = wide_input.find(L' ');
                if (pos == wstring::npos) throw invalid_argument("Missing space");

                wstring num = wide_input.substr(0, pos);
                wide_input.erase(0, pos + 1);

                pos = wide_input.find(L'*');
                if (pos == wstring::npos) throw invalid_argument("Missing '*'");

                wstring xpos = wide_input.substr(0, pos);
                wstring ypos = wide_input.substr(pos + 1);

                answer = stoi(num);
                x = stoi(xpos);
                y = stoi(ypos);

                // Ensure coordinates are within bounds
                if (x < 1 || x > 9 || y < 1 || y > 9) 
                {
                    screenBuffer.writeToScreen(0, 19, L"Coordinates out of bounds. Enter positions between 1 and 9.");
                    continue;
                }

                // Adjust for array's zero-based indexing
                x -= 1;
                y -= 1;

                numbercheck = true;

            }
            catch (invalid_argument& e) 
            {
                screenBuffer.writeToScreen(0, 10, L"Invalid input format. Please try again.");
            }
            catch (out_of_range& e) 
            {
                screenBuffer.writeToScreen(0, 10, L"Input is out of range. Please enter smaller numbers.");
            }    
        }
    } while (!numbercheck);

    // Assign the input number to the grid
    grid[x][y] = answer;
}

bool Sudokuuuu::solver(int grid[9][9])
{
    int row, col;
    bool empty = false;

    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == 0)
            {
                empty = true;
                break;
            }
        }
        if (empty) break;
    }

    if (!empty) return true; // All cells filled

    int nums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    random_device rd;

    mt19937 g(rd());

    shuffle(nums, nums + 9, g); // Shuffle numbers to randomize

    for (int i = 0; i < 9; i++)
    {
        int num = nums[i];

        if (uniquequestionmark(grid, row, col, num))
        {
            grid[row][col] = num;

            if (solver(grid))
            {
                return true;
            }

            grid[row][col] = 0; // Backtrack
        }
    }

    return false; // Trigger backtracking
}

void Sudokuuuu::generate(int grid[9][9])
{
    solver(grid); // Solve the Sudoku grid
}

void Sudokuuuu::remover(int grid[9][9], int count)
{
    while (count > 0)
    {
        int row = rand() % 9;
        int col = rand() % 9;

        if (grid[row][col] != 0)
        {
            grid[row][col] = 0;
            count--;
        }
    }
}

void Sudokuuuu::display(int grid[9][9])
{
    screenBuffer.writeToScreen(6, 0, L"1   2   3   4   5   6   7   8   9 ");
    screenBuffer.writeToScreen(4, 1, L"_____________________________________");

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
        screenBuffer.writeToScreen(4, offset++, L"-------------------------------------");
    }
}

void Sudokuuuu::giveanswer(int original[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            answer[row][col] = original[row][col];
        }
    }
}

int Sudokuuuu::givepos(int row, int col)
{
    return answer[row][col];
}

int Sudokuuuu::sudoku()
{
    screenBuffer.setActive();

    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    generate(input);

    giveanswer(input); // Copy generated solution grid to answer grid

    remover(input, 30); // Remove 40 numbers to create the puzzle

    do
    {
        screenBuffer.clearScreen();

        display(input); // Display the current grid state

        enternum(input); // Allow user to input a number

        if (surrender == true)
        {
            break;
        }

    } while (memcmp(answer, input, sizeof(answer)) != 0); // Continue until puzzle is solved

    screenBuffer.clearScreen();

    display(input);

    if (surrender == true)
    {
        screenBuffer.writeToScreen(0, 21, L"Surrendered. Press enter to return to menu.");
    } else 
    {
        screenBuffer.writeToScreen(0, 21, L"You are the winner! Congratulations!. Press enter to return to menu.", ScreenBuffer::GREEN, ScreenBuffer::BACKGROUND_NORMAL);
    }

    screenBuffer.getBlockingInput();

    return 0;
}
