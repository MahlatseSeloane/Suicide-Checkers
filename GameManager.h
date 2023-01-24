#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class GameManager
{
    public:
        GameManager();
        GameManager(int givenSize);
        void setTurn(int _turn);
        bool getTurn();
        void setContinuePlaying();
        bool getContinuePlaying();
        int getP1numOfPieces();
        int getP2numOfPieces();
        vector<vector<char> > getBoard();

        void playToBeMade(int SP,int JP,int EP);
        void findPosition(int &row,int &col,int _pos);
        void crown();
        void countNumberOfPiecesOnBoard();

    private:
        void updateBoard();
        vector<vector<char> > board;
        int boardSize, term, numOfPieces, p1Pieces, p2Pieces, startPos, jumpPos, endPos;
        char p1Small, p1Big, p2Small, p2Big;
        bool turn, continuePlaying;
};

#endif // GAMEMANAGER_H
