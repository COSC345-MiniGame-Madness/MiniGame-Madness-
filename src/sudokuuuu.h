#ifndef SUDOKUUUU_h
#define SUDOKUUUU_h

#include "screenBuffer.h"

using namespace std;

/*!
 * @file sudokuuuu.h
 * @brief Contains the declaration of the sudokuuuu class and its member functions.
 */

/*!
 * @class Sudokuuuu
 * @brief Class to handle the Sudoku game logic.
 */
class Sudokuuuu
{
    private:

        int answer[9][9] = {0};
        int input[9][9] = {0};

        ScreenBuffer screenBuffer;

    public:

        /// @brief constructor
        Sudokuuuu();

        /// @brief checks if line has 1 instance of each number
        /// @return 
        bool uniquequestionmark(int grid[9][9], int row, int col, int num);

        /// @brief lets player input numbers
        void enternum(int grid[9][9]);

        /// @brief inputs number into grid
        bool solver(int grid[9][9]);

        /// @brief generates sudoku grid
        void generate(int grid[9][9]);

        /// @brief removes number from grid
        void remover(int grid[9][9], int count);

        /// @brief displays grid
        void display(int grid[9][9]);

        /// @brief copies solution grid to answer array
        void giveanswer(int original[9][9]);

        /// @brief return number at specific position
        int givepos(int row, int col);

        /// @brief game loop for playing
        int sudoku();
};

#endif // SUDOKUUUU_H