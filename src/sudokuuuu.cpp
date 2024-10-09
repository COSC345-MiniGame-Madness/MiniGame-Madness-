#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <string>
#include "sudokuuuu.h"
#include "screenBuffer.h"

using namespace std;

//int answer[9][9] = { 0 };

Sudokuuuu::Sudokuuuu()
{
    generate(answer); //randomize grid
}

bool Sudokuuuu::uniquequestionmark(int grid[9][9], int row, int col, int num) // checks if number is in the row, column or inner square
{
    for (int x = 0; x < 9; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num)
        {
            return false;
        }
    }

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
        string input;
        screenBuffer.writeToScreen(0, 10, L"\nEnter number and coordinates in the format of 'number row*column': ");
        getline(cin, input);

        try {
            size_t pos = input.find(' ');
            if (pos == string::npos) throw invalid_argument("Missing space");

            string num = input.substr(0, pos);
            input.erase(0, pos + 1);

            pos = input.find('*');
            if (pos == string::npos) throw invalid_argument("Missing '*'");

            string xpos = input.substr(0, pos);
            string ypos = input.substr(pos + 1);

            answer = stoi(num);
            x = stoi(xpos);
            y = stoi(ypos);

            // Ensure coordinates are within bounds
            if (x < 1 || x > 9 || y < 1 || y > 9) {
                screenBuffer.writeToScreen(0, 10, L"Coordinates out of bounds. Enter positions between 1 and 9.\n");
                continue;
            }

            //adjust for array's zero positions
            x -= 1;
            y -= 1;

            numbercheck = true;

        }
        catch (invalid_argument& e) {
            screenBuffer.writeToScreen(0, 10, L"Invalid input format. Please try again.\n");
        }
        catch (out_of_range& e) {
            screenBuffer.writeToScreen(0, 10, L"Input is out of range. Please enter smaller numbers.\n");
        }
    } while (!numbercheck);

    grid[x][y] = answer;
}

bool Sudokuuuu::solver(int grid[9][9]) // attempts to fill every empty cell with a valid number
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

    if (!empty)
    {
        return true; // all cells filled
    }

    int nums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    random_device rd;
    mt19937 g(rd());

    std::shuffle(nums, nums + 9, g); //randomize order of numbers

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

            grid[row][col] = 0; //backtrack
        }
    }

    return false; //trigger backtracking
}

void Sudokuuuu::generate(int grid[9][9])
{
    solver(grid);
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
    screenBuffer.writeToScreen(5, 0, L" 1   2   3   4   5   6   7   8   9 ");
    screenBuffer.writeToScreen(3, 1, L"_____________________________________");

    int offset = 2;

    for (int row = 0; row < 9; row++)
    {
        std::wstring rowDisplay = L" |";

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
        screenBuffer.writeToScreen(3, offset++, L"-------------------------------------");
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

    srand(time(0)); //random number generator

    int grid[9][9] = { 0 }; //grid

    //generate(answer); //randomize grid

    giveanswer(input); // and save it to a second grid

    remover(input, 40); //remove numbers

    do
    {
        display(input);
        //cout << "\n\n";
        //display(answer);

        enternum(input);
    } while (memcmp(answer, input, sizeof(answer)) != 0);

    screenBuffer.writeToScreen(0, 10, L"You are winner. Now go outside");

    return 0;
}
