#ifndef AI_H
#define AI_H

#include <vector>
#include <iostream>

using namespace std;

class AI
{
    public:
        AI();
        AI(int givenSize);
        vector<vector<int> > checkPossibleMoves(vector<vector<char> > _board,int _turn);
        vector<int> checkDownLeft(int row,int col);
        vector<int> checkDownRight(int row,int col);
        vector<int> checkUpLeft(int row,int col);
        vector<int> checkUpRight(int row,int col);
        int findPosition(int row,int col);

        void setPieces(int _turn);

    private:
        char myPiece, myBigPiece, oppPiece, bigOppPiece, emptySpace;
        int boardSize;
        vector<vector<char> > board;
};

#endif // AI_H
