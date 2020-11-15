/* Tic-tac-toe by Dakota Ruhl, Kaylin Y, and Nicole Beltran.

    The main function will determine the next best move for the game piece. We need to loop this and finish creating the
    entire board to determine a winner or a loser.
*/

//GIT TEST

//#include <bits/stdc++.h>  //every std library (Requries GCC).
//we just need these 2
#include <iostream>   //std::cout
#include <algorithm>  //std::max
using namespace std;

struct rowCols
{
    int row, col;
};

char player = 'x',
     opponent = 'o';

int gameLength = 0;
int nodesGenerated = 0;

//determines if there are moves left to play
bool isMovesLeft(char gameBoard[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (gameBoard[i][j]=='_')
                return true;
    return false;
}

//EVALUATION FUNCTION 1
//REWRITE YOURS HERE
int evaluate(char gb[3][3])
{
    //counters
    int rowC,
        colC,
        diagC = 0;
    //Check rows for victory
    for (int row = 0; row<3; row++)
    {
        rowC++; //increment row counter
        if (gb[row][0]==gb[row][1] &&
            gb[row][1]==gb[row][2])
        {
            nodesGenerated += 3; //3 nodes generated each pass
            if (gb[row][0]==player)
            {
                gameLength = gameLength + rowC + colC;
                return +1;
            }
            else if (gb[row][0]==opponent)
            {
                gameLength = gameLength + rowC + colC;
                return -1;
            }
        }
    }
    //Checking columns for victory
    for (int col = 0; col<3; col++)
    {
        colC++; //increment column counter
        if (gb[0][col]==gb[1][col] &&
            gb[1][col]==gb[2][col])
        {
            nodesGenerated += 3; //3 nodes generated each pass
            if (gb[0][col]==player)
            {
                gameLength = gameLength + rowC + colC;
                return +1;
            }
            else if (gb[0][col]==opponent)
            {
                gameLength = gameLength + rowC + colC;
                return -1;
            }
        }
    }
    //Checking diagonals for victory.
    if (gb[0][0]==gb[1][1] && gb[1][1]==gb[2][2])
    {
        diagC++;  //increment diagonal counter
        nodesGenerated += 3; //3 nodes generated
        if (gb[0][0]==player)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return +1;
        }
        else if (gb[0][0]==opponent)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return -1;
        }
    }
    if (gb[0][2]==gb[1][1] && gb[1][1]==gb[2][0])
    {
        diagC += 2; //increment twice to include first check
        nodesGenerated += 6;
        if (gb[0][2]==player)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return +1;
        }
        else if (gb[0][2]==opponent)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return -1;
        }
    }
    //Return 0 if no winners
    gameLength = sizeof(gb)^2;  //max traverse 3x3 + 12
    nodesGenerated = sizeof(gb)^2;
    return 0;
}

//Returns game board values MiniMax
int minimax(char gameBoard[3][3], int depth, bool isMax)
{
    int score = evaluate(gameBoard);

    //Return score if game is won by max
    if (score == 1)
        return score;

    //Return score if game is won by min
    if (score == -1)
        return score;

    //Tie game
    if (isMovesLeft(gameBoard)==false)
        return 0;

    //Maximizer's move
    if (isMax)
    {
        int highest = -100;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (gameBoard[i][j]=='_')
                {
                    gameBoard[i][j] = player;
                    highest = max( highest, minimax(gameBoard, depth+1, !isMax) );
                    gameBoard[i][j] = '_';
                }
            }
        }
        return highest;
    }
    //Minimizer's Move
    else
    {
        int highest = 100;
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (gameBoard[i][j]=='_')
                {
                    gameBoard[i][j] = opponent;
                    highest = min(highest, minimax(gameBoard, depth+1, !isMax));
                    gameBoard[i][j] = '_';
                }
            }
        }
        return highest;
    }
}

//Find the best move given a gameBoard
rowCols findBestMove(char gameBoard[3][3])
{
    int bestVal = -100;
    rowCols bestMove;
    bestMove.row = -1;
    bestMove.col = -1;


    //Evaluate minimax for each empty cell and return cell with highest value
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (gameBoard[i][j]=='_')
            {
                gameBoard[i][j] = player;
                int moveVal = minimax(gameBoard, 0, false);
                gameBoard[i][j] = '_';

                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;  //bestVal is highest value
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
            bestVal);
    return bestMove;
}


int main()
{
    char gameBoard[3][3] =
    {
        { 'x', 'o', 'x' },
        { 'o', 'o', 'x' },
        { '_', '_', '_' }
    };

    rowCols bestMove = findBestMove(gameBoard);

    //Adding 1 to end so matrix is labeled > 1, since C++ arrays start at 0.
    printf("The Optimal Move is :\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row+=1,
                                  bestMove.col+=1 );

    printf("Game Length: %d\n", gameLength);
    printf("Nodes Generated: %d\n", nodesGenerated);
    return 0;
}
