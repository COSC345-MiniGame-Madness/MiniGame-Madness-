// chckrs.h

#ifndef CHCKRS_H
#define CHCKRS_H

#include "ScreenBuffer.h"

using namespace std;

class Checkers
{
    private:
        int checkersGrid[8][8];
        int player1 = 1, player2 = 2, currentplayer = 1;
        bool winnerquestionmark = false;

        ScreenBuffer screenBuffer;

    public:
        Checkers();

        void populateCheckersGrid();

        void forcejump(int playerturn);

        void checkwin();

        void playerturn(int curre);

        int randomstarter();

        void swapturn(int playert);

        void display();

        void checkersGam();
};
#endif // CHCKRS_H