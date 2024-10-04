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
        bool uniquequestionmark();

        /// @brief 
        void enternum();

        /// @brief 
        /// @return 
        bool solver();

        /// @brief 
        void generate();

        /// @brief 
        void remover();

        /// @brief 
        void display();

        /// @brief 
        void giveanswer();

        /// @brief 
        /// @return 
        int sudoku();
}

#endif // SUDOKUUUU_H