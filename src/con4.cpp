#include <iostream>
#include <string>

using namespace std;

int grid[7][6] = {0};
int player1 = 1, player2 = 2; //1 for player 1, 2 for 2, 0 for empty space.
int currentplayer;
bool winquestionmark = false;
/*
con4game::con4game()
{

}*/

void endgame() // 
{
    winquestionmark = true;
}

void dropcoin(int column, int playercoin)
{
    for (int i = 0; i < 6; i++)
    {
        if (grid[column][i+1] != 0 || i == 6)
        {
            grid[column][i] = playercoin;
            
            break;
        }
    }
}

void playerturn(int player)
{
    cout << "player " << player << "'s turn. Select a column to drop a coin.";

    string coldrop;

    getline(cin, coldrop);

    dropcoin(stoi(coldrop), player);
}

void populategrid()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; i < 6; i++)
        {
            grid[i][j] = 0;
        }
    }
}

void checkdraw()
{
    bool full = true;

    for(int i = 0; i < 6; i++)
    {
        if(grid[i][0] == 0)
        {
            full = false;
        }
    }

    if(full == true)
    {
        endgame();
    }
}

void checkwin()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; i < 6; i++)
        {
            if(i < 5) // horizontal, diagonal right
            {
                if (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j])
                {
                    endgame();
                }

                if (j < 3) // vertical
                {
                    if (grid[i][j] == grid[i + 1][j + 1] && grid[i + 1][j + 1] == grid[i + 2][j + 2] && grid[i + 2][j + 2] == grid[i + 3][j + 3])
                    {
                        endgame();
                    }
                }
            }

            if (i > 3 && j < 3) // diagonal left
            {
                if (grid[i][j] == grid[i - 1][j + 1] && grid[i - 1][j + 1] == grid[i - 2][j + 2] && grid[i - 2][j + 2] == grid[i - 3][j + 3])
                {
                    endgame();
                }
            }

            if (j < 3) // vertical
            {
                if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3])
                {
                    endgame();
                }
            }
        }
    }
}

int randomstarter()
{
    return 1 + (rand() % 2);
}

int swapturn(int playert)
{
    if (playert == 1)
    {
        return 2;
    }
    else {
        return 1;
    }
}

void setnum(int num, int row, int col)
{
    grid[row][col] = num;
}

int con4()
{
    cout << "Hello World";

    populategrid();

    currentplayer = randomstarter();

    do
    {
        currentplayer = swapturn(currentplayer);

        playerturn(currentplayer);

        checkwin();

        checkdraw(); 

    } while (winquestionmark == false);

    return 0;
    // sysout player # wins
}