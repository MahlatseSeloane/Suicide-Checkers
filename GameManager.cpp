#include "GameManager.h"

GameManager::GameManager()
{
    //ctor
}

//The GameManager constructor function is used to create a new game and set the initial conditions of the game
GameManager::GameManager(int givenSize)
{
    boardSize = givenSize;

    //Used to store the current term using the current board size. i.e., if the sizeOfGrid = 6, then term = 1 and if sizeOfGrid = 7, tne term = 2 etc.
    term = (boardSize/2) - 2;

    //Used to store the total number of pieces each player has at the beginning of the game
    numOfPieces = (term * term) + 3 * term + 2;

    //Used to determine whose turn it is
    turn = false;

    //Used to check the state of the  game (Whether it is over or not)
    continuePlaying = true;

    //Used to create the board with the correct dimensions for the current board size the players are to play on
    board.resize(boardSize, vector<char>(boardSize,' '));

    p1Small = '/', p1Big = 'X';
    p2Small = '*', p2Big = 'O';

    int counter = 0;
    //This nested for-loop is used to configure the board such that each player's pieces are lined up in either the first
    //and last two, three or four rows on either side of the board, depending on on the current board size.
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            //Used to ensure that all pieces are placed only on the occupiable blocks(black squares) of the board
            if((i + j) % 2 != 0)
            {
                //Used to line up each player's piece on the board before the game begins
                if(counter < numOfPieces)
                    board[i][j] = p1Small;
                else if(counter < numOfPieces + boardSize)
                    board[i][j] = '-';
                else
                    board[i][j] = p2Small;

                counter++;
            }
        }
    }
}

//The setTurn fucntion is used to alternate turns between players
void GameManager::setTurn(int _turn)
{
    turn = !turn;
}

//The getTurn function is used to get whose turn it is
bool GameManager::getTurn()
{
    return turn;
}

//The setContinuePlaying function is used to set the current state of the game
void GameManager::setContinuePlaying()
{
    continuePlaying = !continuePlaying;
}

//The getContinuePlaying function is used to get the current state of the game to determine whether it is over or not
bool GameManager::getContinuePlaying()
{
    return continuePlaying;
}

//The getP1numOfPieces function is used to get the number of pieces player 1 has on the board when the game is over
int GameManager::getP1numOfPieces()
{
    return p1Pieces;
}

//The getP2numOfPieces function is used to get the number of pieces player 2 has on the board when the game is over
int GameManager::getP2numOfPieces()
{
    return p2Pieces;
}

//The getBoard function is used to get the current board
vector<vector<char> > GameManager::getBoard()
{
    return board;
}

//The updateBoard function is used to update the board accordingly after a move was made, by moving the piece the current
//player moved from the block it was moved from, to the block it was moved to. And if a jump was invloved, removing the
//the opponent's jumped piece off the board.
void GameManager::updateBoard()
{
    int row, col;
    char temp;

    //Used to find the row and col of the block number the current player's piece was moved from
    findPosition(row,col,startPos);
    temp = board[row][col];
    //Used to replace the
    board[row][col] ='-';

    //Used to find the row and col of the block number the current player's piece was moved to
    findPosition(row,col,endPos);
    board[row][col] = temp;

    //Used to check if there was a piece that was jumped.
    if(jumpPos != 0)
    {
        //If there was a piece that was jumped, jumpPos is non-zero

        //Used to find the row and col of the block number where the opponent's piece was when it was jumped
        findPosition(row,col,jumpPos);
        //Used to replace the
        board[row][col] = '-';
    }

    //Used to crown any piece of either player that has reached the furtherest row from thir starting side
    crown();
}

//The playToBeMade function is used to relay the information to the game manager about where the current player wishes to
//moving so it can update the board accordingly after a move was made
void GameManager::playToBeMade(int _SP,int _JP,int _EP)
{
    startPos = _SP;
    jumpPos = _JP;
    endPos = _EP;

    //Used to update the board accordingly
    updateBoard();
}

//The findPosition function is used to find the corresponding row and col of a specific block number
void GameManager::findPosition(int &row,int &col,int _pos)
{
    int counter = 1;

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            //Used to ensure that only occupiable blocks(black squares) of the board  are checked
            if((i + j) % 2 != 0)
            {
                //Used to check if the counter matches the block number passed to the function. If it does, then the row
                //and col of the corresponding block number are returned.
                if(counter == _pos)
                {
                    row = i, col = j;
                    return;
                }

                counter++;
            }
        }
    }
}

//The crown function is used to crown any piece of either player that has reached the furtherest row from thir starting
//side
void GameManager::crown()
{
    for(int i = 0; i < boardSize; i++)
    {
        if(board[boardSize-1][i] == p1Small)
            board[boardSize-1][i] = p1Big;
        else if(board[0][i] == p2Small)
            board[0][i] = p2Big;
    }
}

//The countNumberOfPiecesOnBoard function is used to count the number of pieces each player has at the end of the game on
//the board
void GameManager::countNumberOfPiecesOnBoard()
{
    p1Pieces = 0, p2Pieces = 0;
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            if(board[i][j] == p1Small || board[i][j] == p1Big)
                p1Pieces++;
            else if(board[i][j] == p2Small || board[i][j] == p2Big)
                p2Pieces++;
        }
    }
}
