#include <iostream>
#include <algorithm>

int grid[9][9], answer[9][9];
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

	for (int i = 0; i < 9; i++)
	{
		int horizontalcheck = [1, 2, 3, 4, 5, 6, 7, 8, 9];

		for (int j = 0; j < 9; j++)
		{
			do
			{
				numtoplacein = 1 + (rand() % 9);

				int verticalcheck = [1, 2, 3, 4, 5, 6, 7, 8, 9]; // faster to randomly pick number from reduced list

				for (int h = i; h > 0; h--)
				{
					if (grid[h][j] == numtoplacein)
					{
						verticalcheck.remove(numtoplacein);
					}
				}

				grid[i][j] = numtoplacein; // find a way to ensure the number is unique for row & column & square
		
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