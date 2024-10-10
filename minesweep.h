#ifndef MINSWEEP_H
#define MINSWEEP_H

#include "screenBuffer.h"

using namespace std;

/*!
 * @file minsweep.h
 * @brief Contains the declaration of the Minsweep class and its member functions.
 */

 /*!
  * @class Minsweep.h
  * @brief Class to handle the Minesweeper game logic.
  */
class Minsweep
{
private:
    int grid[25][25]; // assuming maximum size is 25x25
    bool revealed[25][25]; // tracks revealed tiles
    int widened;

    ScreenBuffer screenBuffer;

public:

    /// @brief ends game loop if called
    void endgame();

    /// @brief randomly places mines in grid
    /// @param diff sets difficulty
    void populategrid(string diff);

    /// @brief checks if win conditions are met
    void checkwin();

    /// @brief sets status as lose when mine is chosen
    void kaboom();

    /// @brief reveals all empty neighbours
    /// @param x x coords
    /// @param y y coords
    void floodFill(int x, int y);

    /// @brief lets player make a move
    void makemove();

    /// @brief displays grid on screen buffer
    void display();

    /// @brief method that runs the game
    int minesweep();
};

#endif //