#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define CLS() (system("cls"))
#define PAUSE() (system("pause"))
#define OPPONENT 1
#define PLAYER 2
#define PIXEL_RATIO 1
#define SCREEN_WIDTH 600
#define SCREEN_HRIGHT 620

class TicTacToe : public olc::PixelGameEngine
{
public:
    TicTacToe()
    {
        sAppName = "Tic Tac Toe";
    }

    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        displayBoard();
        return true;
    }

private:
    short board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };
    short PLAYER_ONE = 1;
    short PLAYER_TWO = 2;
    short *CURRENT_PLAYER = &PLAYER_ONE;

    void displayBoard()
    {
        /* Display the board on to the screen */
        // Draw the horizontal line
        DrawLine(10, 10, 590, 10);
        DrawLine(10, 210, 590, 210);
        DrawLine(10, 410, 590, 410);
        DrawLine(10, 610, 590, 610);
        // Draw the vertical lines
        DrawLine(10, 10, 10, 610);
        DrawLine(210, 10, 210, 610);
        DrawLine(410, 10, 410, 610);
        DrawLine(590, 10, 590, 610);
        // Draw the players
        for (short row = 0; row < 3; row++)
        {
            for (short col = 0; col < 3; col++)
            {
                if (!board[row][col])
                {
                    continue;
                }
                else if (board[row][col] == OPPONENT)
                {
                    // TODO: Implement drawing of the human
                }
                else {
                    // TODO: implement drawing of the computer
                }
            }
        }
    }

    void drawCircle(int32_t x, int32_t y)
    {
        // Draw the player represented by the circle
    }

    void getUserInput()
    {
        /* Detect and pass the user input */
    }

    short isFree(short x, short y)
    {
        /* Check if a certain position on the game board is free for a certain player
	if the position is free, it will return 1, if not will return 0 */
        return (!board[x][y]) ? 1 : 0;
    }

    short movePlayer(short x, short y)
    {
        /* Move the current player to the specified opsition on the board
	returns -1 if the position is already taken by another player */
        if (isFree(x, y) && x < 3 && y < 3 && x >= 0 && y >= 0)
        {
            board[x][y] = *CURRENT_PLAYER;
            return 0;
        }
        return -1;
    }

    void switchPlayer()
    {
        /* Switch the current player */
        if (CURRENT_PLAYER == &PLAYER_ONE)
        {
            CURRENT_PLAYER = &PLAYER_TWO;
        }
        else if (CURRENT_PLAYER == &PLAYER_TWO)
        {
            CURRENT_PLAYER = &PLAYER_ONE;
        }
    }

    short isBoardFilled()
    {
        /* Check if a tie situation has come to `play` */
        for (short row = 0; row < 3; row++)
        {
            for (short i = 0; i < 3; i++)
            {
                if (!board[row][i])
                {
                    return 0;
                }
            }
        }
        return 1;
    }

    short hasWon()
    {
        /* Check the game for any winners */
        // Go through 1 and 2, the players
        for (short player = 1; player < 3; player++)
        {
            // Search the rows for winners
            for (short row = 0; row < 3; row++)
            {
                if (board[row][0] == player && board[row][1] == player && board[row][2] == player)
                {
                    return player;
                }
            }
            // search each column
            for (short col = 0; col < 4; col++)
            {
                if (board[0][col] == player && board[1][col] == player && board[2][col] == player)
                {
                    return player;
                }
            }
            // Search the cross sections
            if (board[1][1] == player)
            {
                if (board[0][0] == player && board[2][2] == player)
                {
                    return player;
                }
                if (board[0][2] == player && board[2][0] == player)
                {
                    return player;
                }
            }
        }
        return 0;
    }

    int evaluateBoard()
    {
        /* Evaluate the board for the usage of the minmax function */
        switch (hasWon())
        {
        case OPPONENT:
            return -10;
        case PLAYER:
            return 10;
        case 0:
            return 0;
        default:
            exit(EXIT_FAILURE);
        }
    }

    int minMax(int depth)
    {
        /* considers all the possible ways the game can go and return the value of the board */
        int score = evaluateBoard();
        if (score == 10 && score == -10)
            return score;
        if (isBoardFilled())
            return 0;

        if (CURRENT_PLAYER == &PLAYER_TWO)
        {
            int best = -1000;
            for (short row = 0; row < 3; row++)
            {
                for (short col = 0; col < 3; col++)
                {
                    if (isFree(row, col))
                    {
                        movePlayer(row, col);
                        best = std::max(best, minMax(depth + 1));
                        board[row][col] = 0;
                    }
                }
            }
            return best;
        }

        else
        {
            int best = 1000;
            for (short row = 0; row < 3; row++)
            {
                for (short col = 0; col < 3; col++)
                {
                    if (isFree(row, col))
                    {
                        movePlayer(row, col);
                        best = std::min(best, minMax(depth + 1));
                    }
                }
            }
            return best;
        }
    }

    void findBestMove(short *x, short *y)
    {
        /* Find the optimal move for the computer player, using the min_max algorithm and recursion */
        int bestVal = -1000;
        *x = -1;
        *y = 1;
        // move through every position of the board and try the spots
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                if (isFree(row, col))
                {
                    movePlayer(row, col);
                    int moveVal = minMax(0);
                    board[row][col] = 0;

                    if (moveVal > bestVal)
                    {
                        *x = row;
                        *y = col;
                        bestVal = moveVal;
                    }
                }
            }
        }
    }
};

int main(int argc, char **argv)
{
    TicTacToe tic;
    if (tic.Construct(SCREEN_WIDTH, SCREEN_HRIGHT, PIXEL_RATIO, PIXEL_RATIO))
        tic.Start();
    return 0;
}
