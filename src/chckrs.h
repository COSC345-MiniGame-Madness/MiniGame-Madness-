// chckrs.h

#ifndef CHCKRS_H
#define CHCKRS_H

#include "ScreenBuffer.h"

using namespace std;

class Checkers
{
    private:

    public:
        int checkersGrid[8][8];
        int player1, player2, currentplayer;
        bool winnerquestionmark;

        ScreenBuffer screenBuffer;

        void populateCheckersGrid();

        void forcejump(int playerturn);

        void checkwin();

        void playerturn(int curre);

        void move(int playerturn);

        int randomstarter();

        void swapturn(int playert);

        void display();

        void checkersGam();
};
#endif // CHCKRS_H