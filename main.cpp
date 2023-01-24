// <2097552>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include "GameManager.h"
#include "AI.h"

using namespace std;

void AI1(vector<vector<int> > AllPossibleMoves,int &startPos,int &jumpPos,int &endPos);
void AI2(vector<vector<int> > AllPossibleMoves,int &startPos,int &jumpPos,int &endPos);

int main()
{
    ifstream inData;
    ofstream outData;
    inData.open("input.txt");
    outData.open("results.txt");

    //Used to store the various sizes of the board read in from the input file
    int givenSize;

    //Used to read in an unspecified number of board sizes from a file.
    while(inData >> givenSize)
    {
        //Used to check if the current board size meets the requirements
        if(givenSize % 2 == 0 && (givenSize >= 6 && givenSize <= 12))
        {
            //Used to create a new game and set the initial conditions of the game
            GameManager newGame(givenSize);

            //Outputting the size of the current board to be played on
            outData << givenSize << endl;

            //Used to store the block numbers of where a piece was moved from, where it was moved to, and if a jump was
            //involved, the block number of where the other player's piece was jumped, respectively.
            int startPos, jumpPos, endPos;

            //Used to
            AI Player(givenSize);

            //Used to collect all the possible moves the current player can make on the board and storing them in an vector
            //to make it easier to pick a move for either player
            vector<vector<int> > AllPossibleMoves;
            //Used to stop play for the cureent board size if there are no possible moves for the current player to make.
            bool continuePlaying = true;

            //Used to ensure that the game continues for as long as the game state is true and the game is not over
            while(newGame.getContinuePlaying() == true)
            {
                //Collecting all the possible moves the current player can make on the board and storing them in an vector
                //to make it easier to pick a move
                AllPossibleMoves = Player.checkPossibleMoves(newGame.getBoard(),newGame.getTurn() + 1);

                //Used to check if there were any possible moves the current player could make. If there are zero possible
                //moves, either the current player's pieces are positioned such that they can't make any further moves or
                //they have all be jumped, and therefore removed from the board. The game state of the current game is
                //then changed and the game ends
                if(AllPossibleMoves.size() == 0)
                    newGame.setContinuePlaying();

                if(newGame.getContinuePlaying())
                {
                    startPos = 0, jumpPos = 0, endPos = 0;

                    if(newGame.getTurn()+ 1 == 1)
                        //Allowing player 1 to play their turn
                        AI1(AllPossibleMoves,startPos,jumpPos,endPos);
                    else if(newGame.getTurn() + 1  == 2)
                        //Allowing player 2 to play their turn
                        AI2(AllPossibleMoves,startPos,jumpPos,endPos);

                    //Outputting the block numbers of where one of the current player piece was moved from, where it was
                    //moved to, and if a jump was involved, the block number of where the othe player's piece was jumped.
                    outData << "p" << newGame.getTurn() + 1 << " " << startPos;
                    jumpPos == 0 ? (outData << "-" << endPos): outData << "x" << endPos << "(" << jumpPos  << ")";
                    outData << endl;

                    //Used to relay the information about where the current player wishes to moving, to the game manager
                    //so it can update the board accordingly after a move was made
                    newGame.playToBeMade(startPos,jumpPos,endPos);

                    //Used to alternating turns between the players
                    newGame.setTurn(!newGame.getTurn());
                }
            }

            //Used to count the number of each player's pieces on the board to determine the winner.
            newGame.countNumberOfPiecesOnBoard();

            //Outputting the number of pieces each player has on the board
            outData << "tp1 " << newGame.getP1numOfPieces() << endl;
            outData << "tp2 " << newGame.getP2numOfPieces() << endl;

            //Outputting the player that won the fame for the current board size
            if(newGame.getP1numOfPieces() == newGame.getP2numOfPieces())
                outData << "      d" << endl;
            else if (newGame.getP1numOfPieces() < newGame.getP2numOfPieces())
                outData << "      wp1" << endl;
            else if (newGame.getP1numOfPieces() > newGame.getP2numOfPieces())
                outData << "      wp2" << endl;
        }
    }

    inData.close();
    outData.close();

    return 0;
}

//The A1 function is used to
void AI1(vector<vector<int> > AllPossibleMoves,int &startPos,int &jumpPos,int &endPos)
{
    //Theese 2D vectors are used to store all the advantageous and compulsary moves that player 1 could/should make during
    //their turn
    vector<vector<int> > advantageousMoves, compulsaryMoves;

    //The for-loop is used to go through the AllPossibleMoves vector which has all the possible moves whcih the player can
    //make.
    for(int i = 0; i < AllPossibleMoves.size(); i++)
    {
        //Used to check if the AllPossibleMoves vector has either any advantageous or compulsary moves.
        //If the value at the index is zero, then there are no advantageous or compulsary moves
        if(AllPossibleMoves[i][2] != 0)
        {
            if(AllPossibleMoves[i][0] < AllPossibleMoves[i][2])
            {
                if(AllPossibleMoves[i][2] > AllPossibleMoves[i][1])
                    advantageousMoves.push_back(AllPossibleMoves[i]);
                else
                    compulsaryMoves.push_back(AllPossibleMoves[i]);
            }
            else
            {
                if(AllPossibleMoves[i][2] < AllPossibleMoves[i][1])
                    advantageousMoves.push_back(AllPossibleMoves[i]);
                else
                    compulsaryMoves.push_back(AllPossibleMoves[i]);
            }
        }
    }

    srand(time(0));
    int random = rand();
    //Used to check if there are jumps that need to be performed
    if(compulsaryMoves.size() != 0)
    {
        //If there are multiple compulsary moves that can made, then one is randomly picked from the bunch
        random = random % compulsaryMoves.size();
        //Used to store the block numbers of where a piece was moved from, where the opponent's s piece was jumped,
        //and where the piece was moved to respectively.
        startPos = compulsaryMoves[random][0], jumpPos = compulsaryMoves[random][2], endPos = compulsaryMoves[random][1];
    }
    //Used to check if there are an advantageous moves that can be performed
    else if(advantageousMoves.size() != 0)
    {
        //If there are multiple advantageous moves that can made, then one is randomly picked from the bunch
        random = random % advantageousMoves.size();
        //Used to store the block numbers of where a piece was moved from, and where the piece was moved to respectively.
        startPos = advantageousMoves[random][0], jumpPos = 0, endPos = advantageousMoves[random][1];
    }
    //Used to check if there are any mores that can be made at all
    else if(AllPossibleMoves.size() != 0)
    {
        //If there no advantageous or compulsary moves, then one is randomly picked from the AllPossibleMoves vector
        random = random % AllPossibleMoves.size();
        //Used to store the block numbers of where a piece was moved from, and where the piece was moved to respectively.
        startPos = AllPossibleMoves[random][0], jumpPos = 0, endPos = AllPossibleMoves[random][1];
    }
}

void AI2(vector<vector<int> > AllPossibleMoves,int &startPos,int &jumpPos,int &endPos)
{
    vector<vector<int> > compulsaryMoves;

    for(int i = 0; i < AllPossibleMoves.size(); i++)
    {
        //Used to check if the AllPossibleMoves vector has any compulsary moves.
        //If the value at the index is zero, then there are no compulsary moves
        if(AllPossibleMoves[i][2] != 0)
        {

            if(AllPossibleMoves[i][0] < AllPossibleMoves[i][2])
            {
                if(AllPossibleMoves[i][2] < AllPossibleMoves[i][1])
                    compulsaryMoves.push_back(AllPossibleMoves[i]);
            }
            else
            {
                if(AllPossibleMoves[i][2] > AllPossibleMoves[i][1])
                    compulsaryMoves.push_back(AllPossibleMoves[i]);
            }
        }
    }

    srand(time(0));
    int random = rand();
    if(compulsaryMoves.size() != 0)
    {
        random = random % compulsaryMoves.size();
        startPos = compulsaryMoves[random][0], jumpPos = compulsaryMoves[random][2], endPos = compulsaryMoves[random][1];
    }
    else if(AllPossibleMoves.size() != 0)
    {
        random = random % AllPossibleMoves.size();
        startPos = AllPossibleMoves[random][0], jumpPos = 0, endPos = AllPossibleMoves[random][1];
    }
}
