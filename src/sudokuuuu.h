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
        /// @brief 
        Sudokuuuu();

        /// @brief 
        /// @return 
        bool uniquequestionmark(int grid[9][9], int row, int col, int num);

        /// @brief 
        void enternum(int grid[9][9]);

        /// @brief 
        /// @return 
        bool solver(int grid[9][9]);

        /// @brief 
        void generate(int grid[9][9]);

        /// @brief 
        void remover(int grid[9][9], int count);

        /// @brief 
        void display(int grid[9][9]);

        /// @brief 
        void giveanswer(int original[9][9]);

        /// @brief 
        /// @return 
        int sudoku();
};

#endif // SUDOKUUUU_H