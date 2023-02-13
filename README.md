<h1>Suicide Checkers</h1>
<p>For the project, using the IDE CodeBlocks, we were required to develop a computer program in C++ that facilitated the game of Suicide Checkers between two different algorithms. The program was to read a number of board sizes of n × n where 6 ≤ n ≤ 12 from a file named input.txt, and facilitate the game for each board size between the two algorithms and record the games in an output file</p>

<p>Suicide checkers, also known as Anti-Checkers, Giveaway Checkers and Losing draughts is a two player variant of the board game checkers where the goal outcome has been reversed - if you have no pieces left or if you cannot move anymore, you win. Players take alternating turns, moving their pieces according to the rules of checkers. The goal of the game is to have no pieces left.</p>

<h2>Code Requirements</h2>
<p>The requirements for the project were as follows:

- The should be no input prompt or output on the console.
-	No global variables may be used as this would result in immediate failure.
- Use of at least one Class.
- Use of a Function.
-	Reading in and writing to files.
</p>                       

<h2>Board format </h2>
<p>For moves made by the algorithms to be recorded in a meaningful way that can be understood easily, a standard labelling system is to be used. The checkers board is generally labelled as shown below:</p>

PUT PICTURE HERE

<p> Player 1 will have their pieces lined up on the side starting with 1 and player 2 will have their pieces lined up on the side with the maximum label number.</p>

<h2>Input format</h2>
<p>The input file would contain a list of board sizes, separated by newline characters, that would be used to test the two algorithms against each other. The input file had the following format</p>

PUT PICTURE HERE

<h2>Output format</h2>
<p>The program must produce an output file named results.txt. This file must contain the following:

- size of the board for the current game,
- The move made by each player, along with the player that made the corresponding move,
- The winner of the game.

- The player that made the corresponding move, along with the move made by that player,
  - If a player makes a move without taking pieces, list the block number the piece moved from, a dash and the block number the piece moved to, eg. "p1 4-7".
  - If a player makes a move that involves jumping the opponent's piece, list the block number the piece moved from, a "x", the block number the piece moved to and the block number where the opponent's piece was jumped, enclosed in brackets, eg. "p2 12x5(8)".
- If a player makes a move that involves multiple jumps of the opponent's piece(s), you would have the following "p2 17x12(14)12x5(8)"
- Once the game is over the total number of pieces for player 1 and player 2 should be listed on seperate lines.
- The final piece of information to include is who the winner is or if it is a draw.
  - If there is a winner write either "wp1" if player 1 wins or "wp2" if player 2 wins.
  - If there is a draw, write "d".

The history for each board size listed in the input file must be appended to this file with one empty line inbetween different games.

Below is an exapmle of the output file for the games of the boardsizes in the input file:
</p>

PUT PICTURE HERE
<p>Note that coordinates on the board are labelled using the value of the row (r) and column (c) where the top left position is r0c0 and bottom right is r5c5 for a board of size 4 x 4.</p>

Below is the graphical representation of the game play.
