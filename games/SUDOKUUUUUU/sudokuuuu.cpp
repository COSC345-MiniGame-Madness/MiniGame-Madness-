#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int grid[9][9];
int answer[9][9];
int player = 1;
int currentplayer;
bool winquestionmark = false;

void enternum()
{
	do // GO OVER THIS AGAIN & FIX IT
	{
		string input;
		int inp, pos, x, y;

		std::cout << "enter number and coordinates in the format of 'number x*y'" << std::endl;

		getline(cin, input);

		pos = input.find(' ');

		string num = input.substr(0, pos);

		inp = stoi(num);

		input.erase(0, pos + 1);

		string xpos = input.substr(0, input.find('*');

		x = stoi(xpos);

		pos = input.find('*');

		input.erase(0, pos + 1);

		y = stoi(ypos);

	} while (true);
}

void populate()
{
	int numtoplacein;
	//int horizontalcheck[9], verticalcheck[9];

	std::vector < int > horizontalcheck;
	std::vector < int > verticalcheck;

	for (int t = 1; t < 10; t++)
	{
		horizontalcheck.push_back(t);
		verticalcheck.push_back(t);
	}

	for (int i = 0; i < 9; i++)
	{
		//horizontalcheck = [1, 2, 3, 4, 5, 6, 7, 8, 9];

		for (int j = 0; j < 9; j++)
		{
			do
			{
				numtoplacein = 1 + (rand() % 9);

				//verticalcheck = [1, 2, 3, 4, 5, 6, 7, 8, 9]; // faster to randomly pick number from reduced list

				for (int h = i; h > 0; h--)
				{
					if (grid[h][j] == numtoplacein)
					{
						verticalcheck.pop_back;
					}
				}

				if (j < 3 && i < 3) // top left 3x3 square
				{
					for (int o = 0; o < 3; )
				}

				if (j >= 3 && j < 6 && i < 3)
				{

				}

				if (j >= 6 && i < 3)
				{

				}

				if (j < 3 && i >= 3 && i < 6)
				{

				}

				if (j >= 3 && j < 6 && i >= 3 && i < 6)
				{

				}

				if (j >= 6 && i >= 3 && i < 6)
				{

				}

				if (j < 3 && i >= 6)
				{

				}

				if (j >= 3 && j < 6 && i >= 6)
				{

				}

				if (j >= 6 && i >= 6)
				{

				}

				grid[i][j] = numtoplacein; // find a way to ensure the number is unique for row & column & square

				horizontalcheck.remove(numtoplacein);
		
			} while (std::find(horizontalcheck.begin(), horizontalcheck.end(), numtoplacein) && std::find(verticalcheck.begin(), verticalcheck.end(), numtoplacein));
			
			horizontalcheck.remove(numtoplacein);
		}
	}

	answer = grid;
}

void wincheck()
{

}

void main()
{

}