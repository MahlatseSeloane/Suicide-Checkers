#include "AI.h"

AI::AI()
{
    //ctor
}

AI::AI(int givenSize)
{
    boardSize = givenSize;
}

void AI::setPieces(int _turn)
{
    if(_turn == 1)
        myPiece = '/', myBigPiece = 'X', oppPiece = '*', bigOppPiece = 'O';
    else if(_turn == 2)
        myPiece = '*', myBigPiece = 'O', oppPiece = '/', bigOppPiece = 'X';

    emptySpace = '-';
}

//The checkAllPossibleMoves function is used to collect all the available possible moves the current player can make during their turn and stores them in the
//AllPossibleMoves vector beofre an player makes a move
vector<vector<int> > AI::checkPossibleMoves(vector<vector<char> > _board,int _turn)
{
    board = _board;
    setPieces(_turn);
    vector<vector<int> > AllPossibleMoves;
    vector<int> temp;

    //The nested for-loop is used to go through the board
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            //Used to ensure that only occupiable blocks are checked and also check if the piece at that block matches any
            //of the current player's pieces
            if((i + j) % 2 != 0 && (_board[i][j] == myPiece || _board[i][j] == myBigPiece))
            {
                //If the current player's piece matches either both player 1's pieces or player 2's big piece, the blocks
                //diagonally to the left and right of the current block are check to see if they are either empty and
                //therefore occupiable or if there is a jump to be performed.
                if(_board[i][j] == '/' || _board[i][j] == 'X' || _board[i][j] == 'O')
                {
                    //Used to check the block diagonally left to the current block whether its empty or there's a jump to
                    //be performed
                    temp = checkDownLeft(i,j);

                    //If the temp vector is empty, then the block is occupied and no jump can be performed
                    if(temp.size() != 0)
                        AllPossibleMoves.push_back(temp);

                    //Used to check the block diagonally right to the current block whether its empty or there's a jump to
                    //be performed
                    temp = checkDownRight(i,j);

                    //If the temp vector is empty, then the block is occupied and no jump can be performed
                    if(temp.size() != 0)
                        AllPossibleMoves.push_back(temp);
                }

                //Same as above
                if(board[i][j] == '*' || board[i][j] == 'O' || board[i][j] == 'X')
                {
                    temp = checkUpLeft(i,j);
                    if(temp.size() != 0)
                        AllPossibleMoves.push_back(temp);

                    temp = checkUpRight(i,j);
                    if(temp.size() != 0)
                        AllPossibleMoves.push_back(temp);
                }
            }
        }
    }

    return AllPossibleMoves;
}

//The checkDownLeft function is used to check if the blocks diagonally to the left and right of the current block if they
//are either empty and therefore occupiable or if there is a jump to be performed.
vector<int> AI::checkDownLeft(int row,int col)
{
    vector<int> temp;

    //Used to ensure that when performing a check, we do not go out of bounds from the board
    if(row + 2 <= boardSize - 1 && col - 2 >= 0)
    {
        //Used to check diagonally left if there is a jump to be performed
        if((board[row+1][col-1] == oppPiece || board[row+1][col-1] == bigOppPiece) && board[row+2][col-2] == emptySpace)
        {
            //If the immediately diagonally left is occupied by an opponent's piece and the diagonally empty to that block
            //is empty, then there is a jump to be performed. Therefore, the block number where the check started from, the
            //block number of the block oocupied by the opponent's block, and the block number of the block adjacen to that
            //are pushed into the the vector, and the vector is returned.
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row+2,col-2));
            temp.push_back(findPosition(row+1,col-1));
            return temp;
        }

        //Used to check diagonally left if there is an advantageous move that player 1 can +-
        if(board[row+1][col-1] == emptySpace && (board[row+2][col-2] == oppPiece || board[row+2][col-2] == bigOppPiece))
        {
            //Same thing happens as above
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row+1,col-1));
            temp.push_back(findPosition(row+2,col-2));
            return temp;
        }
    }

    //Used to ensure that when performing a check, we do not go out of bounds from the board
    if(row + 1 <= boardSize - 1 && col - 1 >= 0)
    {
        //Used to check diagonally right if there is a occupiable block
        if(board[row+1][col-1] == emptySpace)
        {
            //If the block immediately diagonally left is empty, then the block is occupiable. Therefore, the block number
            //where the check started from, the empty block's number and a zero(Used to indicate no information) are pushed
            //into the the vector.
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row+1,col-1));
            temp.push_back(0);
        }
    }

    return temp;
}

vector<int> AI::checkDownRight(int row,int col)
{
    vector<int> temp;

    if(row + 2 <= boardSize - 1 && col + 2 <= boardSize - 1)
    {
        if((board[row+1][col+1] == oppPiece || board[row+1][col+1] == bigOppPiece) && board[row+2][col+2] == emptySpace)
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row+2,col+2));
            temp.push_back(findPosition(row+1,col+1));
            return temp;
        }

        if(board[row+1][col+1] == emptySpace && (board[row+2][col+2] == oppPiece || board[row+2][col+2] == bigOppPiece))
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row+1,col+1));
            temp.push_back(findPosition(row+2,col+2));
            return temp;
        }
    }

    if(row + 1 <= boardSize - 1 && col + 1 <= boardSize - 1)
    {
        if(board[row+1][col+1] == emptySpace)
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row+1,col+1));
            temp.push_back(0);
        }
    }

    return temp;
}

vector<int> AI::checkUpLeft(int row,int col)
{
    vector<int> temp;

    if(row - 2 >= 0 && col - 2 >= 0)
    {
        if((board[row-1][col-1] == oppPiece || board[row-1][col-1] == bigOppPiece) && board[row-2][col-2] == emptySpace)
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row-2,col-2));
            temp.push_back(findPosition(row-1,col-1));
            return temp;
        }
    }

    if(row - 2 >= 0 && col - 2 >= 0)
    {
        if(board[row-1][col-1] == emptySpace && (board[row-2][col-2] == oppPiece || board[row-2][col-2] == bigOppPiece))
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row-1,col-1));
            temp.push_back(findPosition(row-2,col-2));
            return temp;
        }
    }

    if(row - 1 >= 0 && col - 1 >= 0)
    {
        if(board[row-1][col-1] == emptySpace)
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row-1,col-1));
            temp.push_back(0);
        }
    }

    return temp;
}

vector<int> AI::checkUpRight(int row,int col)
{
    vector<int> temp;

    if(row - 2 >= 0 && col + 2 <= boardSize - 1)
    {
        if((board[row-1][col+1] == oppPiece || board[row-1][col+1] == bigOppPiece) && board[row-2][col+2] == emptySpace)
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row-2,col+2));
            temp.push_back(findPosition(row-1,col+1));
            return temp;
        }
    }

    if(row - 2 >= 0 && col + 2 <= boardSize - 1)
    {
        if(board[row-1][col+1] == emptySpace && (board[row-2][col+2] == oppPiece || board[row-2][col+2] == bigOppPiece))
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row-1,col+1));
            temp.push_back(findPosition(row-2,col+2));
            return temp;
        }
    }

    if(row - 1 >= 0 && col + 1 <= boardSize - 1)
    {
        if(board[row-1][col+1] == emptySpace)
        {
            temp.push_back(findPosition(row,col));
            temp.push_back(findPosition(row-1,col+1));
            temp.push_back(0);
        }
    }

    return temp;
}

//The findPosition function is used to relate a certein row and col of the board to a unique number
int AI::findPosition(int row,int col)
{
    int position = 1;

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if((i + j) % 2 != 0)
            {
                if(i == row && j == col)
                    return position;

                position++;
            }
        }
    }

    return 0;
}
