#include <iostream>
#include <algorithm>
#include <vector>

int grid[9][9];
int answer[9][9];
int player = 1;
int currentplayer;
bool winquestionmark = false;

void enternum()
{
	
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
						verticalcheck.pop_back
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
			
			horizontalcheck.remove(numtoplacein)
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