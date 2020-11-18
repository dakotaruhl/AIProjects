/* Tic-tac-toe by Dakota Ruhl, Kaylin Y, and Nicole Beltran.

    The main function will determine the next best move for the game piece. We need to loop this and finish creating the
    entire board to determine a winner or a loser.
*/

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

//EVALUATION FUNCTION 1 (only +-100 for 3 in a row)
//REWRITE YOURS HERE
//int evaluate(char gb[3][3])
//{
//    //counters
//    int rowC,
//        colC,
//        diagC = 0;
//    //we assume 'o' is the opponent, and assign negative scores
//
//    //Check rows
//    for (int row = 0; row<3; row++)
//    {
//        rowC++; //increment row counter
//        if (gb[row][0]==gb[row][1] &&
//            gb[row][1]==gb[row][2])
//        {
//            nodesGenerated += 3; //3 nodes generated each pass
//            if (gb[row][0]==player)
//            {
//                gameLength += rowC + colC;
//                return +100;
//            }
//            else if (gb[row][0]==opponent)
//            {
//                gameLength += rowC + colC;
//                return -100;
//            }
//        }
//    }
//    //Checking columns
//    for (int col = 0; col<3; col++)
//    {
//        colC++; //increment column counter
//        if (gb[0][col]==gb[1][col] &&
//            gb[1][col]==gb[2][col])
//        {
//            nodesGenerated += 3; //3 nodes generated each pass
//            if (gb[0][col]==player)
//            {
//                gameLength =+ rowC + colC;
//                return +100;
//            }
//            else if (gb[0][col]==opponent)
//            {
//                gameLength += rowC + colC;
//                return -100;
//            }
//        }
//    }
//    //Checking diagonals
//    if (gb[0][0]==gb[1][1] && gb[1][1]==gb[2][2])
//    {
//        diagC++;  //increment diagonal counter
//        nodesGenerated += 3; //3 nodes generated
//        if (gb[0][0]==player)
//        {
//            gameLength = gameLength + rowC + colC + diagC;
//            return +100;
//        }
//        else if (gb[0][0]==opponent)
//        {
//            gameLength = gameLength + rowC + colC + diagC;
//            return -100;
//        }
//    }
//    if (gb[0][2]==gb[1][1] && gb[1][1]==gb[2][0])
//    {
//        diagC += 2; //increment twice to include first check
//        nodesGenerated += 6;
//        if (gb[0][2]==player)
//        {
//            gameLength = gameLength + rowC + colC + diagC;
//            return +100;
//        }
//        else if (gb[0][2]==opponent)
//        {
//            gameLength = gameLength + rowC + colC + diagC;
//            return -100;
//        }
//    }
//    //Return 0 if no winners
//    gameLength = 81;  //max traverse 3x3 + 12
//    nodesGenerated = 81;
//    return 0;
//}

//EVALUATION FUNCTION 2 (in addition to E1, it also +- 1 point for EACH 1-in-a-line (with two empty cells).)
int evaluate(char gb[3][3])
{
    //counters
    int rowC,
        colC,
        diagC = 0;

    //Check rows
    for (int row = 0; row<3; row++)
    {
        rowC++; //increment row counter
        if (gb[row][0]==gb[row][1] &&
            gb[row][1]==gb[row][2])
        {
            nodesGenerated += 3; //3 nodes generated each pass
            if (gb[row][0]==player)
            {
                gameLength += rowC + colC;
                return +100;
            }
            else if (gb[row][0]==opponent)
            {
                gameLength += rowC + colC;
                return -100;
            }
        }
        //+- 1 point for 1-in-a-line with two empty cells beside
        if (gb[row][0] != '_' && gb[row][1]== '_' && gb[row][2]=='_')
        {
            nodesGenerated += 3;
            if (gb[row][0]==player)
            {
                gameLength += rowC + colC;
                return +1;
            }
            else if (gb[row][0]==opponent)
            {
                gameLength += rowC + colC;
                return -1;
            }
        }
    }
    //Checking columns
    for (int col = 0; col<3; col++)
    {
        colC++; //increment column counter
        if (gb[0][col]==gb[1][col] &&
            gb[1][col]==gb[2][col])
        {
            nodesGenerated += 3; //3 nodes generated each pass
            if (gb[0][col]==player)
            {
                gameLength =+ rowC + colC;
                return +100;
            }
            else if (gb[0][col]==opponent)
            {
                gameLength += rowC + colC;
                return -100;
            }
        }
        //+- 1 point for 1-in-a-line with two empty cells beside
        if (gb[0][col] != '_' && gb[1][col]== '_' && gb[2][col]=='_')
        {
            nodesGenerated += 3;
            if (gb[col][0]==player)
            {
                gameLength += rowC + colC;
                return +1;
            }
            else if (gb[col][0]==opponent)
            {
                gameLength += rowC + colC;
                return -1;
            }
        }
    }
    //Checking diagonals
    if (gb[0][0]==gb[1][1] && gb[1][1]==gb[2][2])
    {
        diagC++;  //increment diagonal counter
        nodesGenerated += 3; //3 nodes generated
        if (gb[0][0]==player)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return +100;
        }
        else if (gb[0][0]==opponent)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return -100;
        }
    }
    if (gb[0][2]==gb[1][1] && gb[1][1]==gb[2][0])
    {
        diagC += 2; //increment twice to include first check
        nodesGenerated += 6;
        if (gb[0][2]==player)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return +100;
        }
        else if (gb[0][2]==opponent)
        {
            gameLength = gameLength + rowC + colC + diagC;
            return -100;
        }
    }

    //+- 1 point for 1-in-a-line with two empty cells beside (diagonals)
    if (gb[0][0] != '_' && gb[1][1]== '_' && gb[2][2]=='_')
    {
        diagC += 3; //+3 for three checks
        nodesGenerated += 9;
        if (gb[0][0]==player)
        {
            gameLength += rowC + colC;
            return +1;
        }
        else if (gb[0][0]==opponent)
        {
            gameLength += rowC + colC;
            return -1;
        }
    }
    if (gb[0][2] != '_' && gb[1][1]== '_' && gb[2][0]=='_')
    {
        diagC += 3; //+3 for three checks
        nodesGenerated += 9;
        if (gb[0][0]==player)
        {
            gameLength += rowC + colC;
            return +1;
        }
        else if (gb[0][0]==opponent)
        {
            gameLength += rowC + colC;
            return -1;
        }
    }
    if (gb[2][2] != '_' && gb[1][1]== '_' && gb[2][2]=='_')
    {
        diagC += 3; //+3 for three checks
        nodesGenerated += 9;
        if (gb[0][0]==player)
        {
            gameLength += rowC + colC;
            return +1;
        }
        else if (gb[0][0]==opponent)
        {
            gameLength += rowC + colC;
            return -1;
        }
    }
    if (gb[2][0] != '_' && gb[1][1]== '_' && gb[2][0]=='_')
    {
        diagC += 3; //+3 for three checks
        nodesGenerated += 9;
        if (gb[0][0]==player)
        {
            gameLength += rowC + colC;
            return +1;
        }
        else if (gb[0][0]==opponent)
        {
            gameLength += rowC + colC;
            return -1;
        }
    }
    //Return 0 if no winners
    gameLength = 81;  //max traverse 3x3 + 12
    nodesGenerated = 81;
    return 0;
}

//Returns game board values MiniMax
int minimax(char gameBoard[3][3], int depth, bool isMax)
{
    int score = evaluate(gameBoard);

    //Return score if game is won by max
    if (score == 100)
        return score;

    //Return score if game is won by min
    if (score == -100)
        return score;

    //Tie game
    if (isMovesLeft(gameBoard)==false)
        return 0;

    //Maximizer's move
    if (isMax)
    {
        int highest = -1000;
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
        int highest = 1000;
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
    return bestMove;
}

void printBoard(char matrix[3][3])
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

char winnerCheck(char gameBoard[3][3])
{
    for (int row=0;row<3;row++)  //check rows
    {
        if (gameBoard[row][0] == gameBoard[row][1] &&
            gameBoard[row][1] == gameBoard[row][2] &&
            gameBoard[row][0] != '_')
        {
            return gameBoard[row][0];
        }
    }

    for (int col=0;col<3;col++)  //check columns
    {
        if (gameBoard[0][col] == gameBoard[1][col] &&
            gameBoard[1][col] == gameBoard[2][col] &&
            gameBoard[0][col] != '_')
        {
            return gameBoard[0][col];
        }
    }

    if (gameBoard[0][0] == gameBoard[1][1] &&
        gameBoard[1][1] == gameBoard[2][2] &&
        gameBoard[0][0] != '_')
    {
        return gameBoard[0][0];
    }
    return 'I';
}

int main()
{
    char gameBoard[3][3] =
    {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };
    cout << "Initial State of Game Board:" << endl;
    printBoard(gameBoard);
    cout << "---------------------------------" << endl;

    int gameLengthTotal = 0;
    int nodesGeneratedTotal = 0;
    int i = 0;
    rowCols bestMove;
    bool movesLeft = true;
    char winner;

    //main loop finds X and O positions
    while (movesLeft)
    {
        bestMove = findBestMove(gameBoard);
        //alternate x and o's (turns)
        if (i == 0)
            gameBoard[bestMove.row][bestMove.col] = 'x';
        if (i%2 == 1)
            gameBoard[bestMove.row][bestMove.col] = 'o';
        if (i%2 == 0)
            gameBoard[bestMove.row][bestMove.col] = 'x';
        i++;


        printf("The Optimal Move is: ROW %d COL %d\n\n", bestMove.row, bestMove.col);
        printf("Game Length: %d\n", gameLength);
        gameLengthTotal += gameLength;
        printf("Nodes Generated: %d\n", nodesGenerated);
        nodesGeneratedTotal += nodesGenerated;
        printBoard(gameBoard);
        printf("\n---------------------------------\n");
        if (winnerCheck(gameBoard) == 'I')
        movesLeft = isMovesLeft(gameBoard);
        else
        movesLeft = false;
    }

    cout << "Game Length Total: " << gameLengthTotal << endl
             << "Total Nodes Generated: " << nodesGeneratedTotal << endl;

    winner = toupper(winnerCheck(gameBoard));
    cout << "The winner is " << winner << "!";
    return 0;
}
