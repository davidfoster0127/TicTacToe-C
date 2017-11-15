/*H**********************************************************************
* FILENAME :        tictactoe.c             
*
* DESCRIPTION :
*       1 or 2 player console TicTacToe implementation
*
* PUBLIC FUNCTIONS :
*       void    drawBoard(char board[])
*       bool    checkWin(char board[], char player)
*       int     getPlayerMove(char board[])
*       int     getComputerMove(char board[], char computer)
*
* AUTHOR :    David Foster        START DATE :    11 Nov 2017
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

void drawBoard(char board[])
{
    printf("\n %c | %c | %c ", board[0], board[1], board[2]);
    printf("\n---+---+---");
    printf("\n %c | %c | %c ", board[3], board[4], board[5]);
    printf("\n---+---+---");
    printf("\n %c | %c | %c ", board[6], board[7], board[8]);
}

bool checkWin(char board[], char player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == player && board[3+i] == player && board[6+i] == player) return true;
        else if (board[(i*3)] == player && board[(i*3)+1] == player && board[(i*3)+2] == player) return true;
    }
    if (board[0] == player && board[4] == player && board[8] == player) return true;
    else if (board[2] == player && board[4] == player && board[6] == player) return true;
    else return false;
}

int getPlayerMove(char board[])
{
    int move = 0;
    do
    {
        printf("\nChoose where to play [0-8]: ");
        
        int result = scanf("%d", &move);
        while ((getchar()) != '\n');
        if (result != 1) move = -1;

    } while (move >= 9 || move < 0 || board[move] != ' ');
    
    return move;
}

/*
*   getComputerMove checks for the eligibility of each move position in turn and, if the move is available, it checks to see if it is a winning move.
*   If the move is a winning move, it returns that move. If it detects no winning moves, it checks the board for plays that would allow player 1 to win. 
*   If so, it returns that move. It then checks if the center tile is available and if it is, returns the middle position.
*   Lastly, it randomly generates numbers up to 8 until the move it chooses isn't occupied and returns that move.
*/
int getComputerMove(char board[], char computer, char player)
{
    int move = 0;
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == ' ')
        {
            move = i;
            board[move] = computer;
            if (checkWin(board, computer)) return move;
            board[move] = ' ';
        }
    }
    
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == ' ')
        {
            move = i;
            board[move] = player;
            if (checkWin(board, player)) return move;
            board[move] = ' ';
        }
    }

    if (board[4] == ' ') return 4;

    for (;;)
    {
        move = rand() % 9;
        if (board[move] == ' ') return move;
    }
}

int main(int agrc, char *argv[])
{
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player, computer, nextTurn, mode = ' ';
    int move = 0;
    bool pwin, cwin = false;
    
    printf("Welcome to TicTacToe! ");

    while (player != 'X' && player != 'O')
    {
        printf("\nWould you like to play Xs or Os? ");
        player = getchar();
        while ((getchar()) != '\n');
        player = toupper(player);
    }

    if (player == 'X') computer = 'O';
    else computer = 'X';
    
    while (mode != 'H' && mode != 'C')
    {
        printf("\nWould you like to play against another human (H) or against a computer (C)? ");
        mode = getchar();
        while ((getchar()) != '\n');
        mode = toupper(mode);
    }

    if (mode == 'H') printf("\nGood luck to both of you!");
    else printf("\nGood luck against TicTacToeBot 3000!");
    printf("\nSelecting who goes first....");
    
    srand(time(0));
    nextTurn = (rand() % 2) == 0 ? player : computer;
    
    if (nextTurn == player) printf("\nYou (%c) go first!", player);
    else printf("\nPlayer 2 (%c) goes first!", computer);

    for (int turn = 0; turn < 9 && !pwin && !cwin; turn++)
    {
        drawBoard(board);

        if(nextTurn == player)
        {
            printf("\nPlayer 1's move (%c): ", player);
            move = getPlayerMove(board);
            board[move] = player;
            pwin = checkWin(board, player);
            nextTurn = computer;
        }
        else
        {
            if (mode == 'H') printf("\nPlayer 2's move (%c): ", computer);
            else printf("\nTicTacToeBot 3000's move (%c):", computer);
            move = (mode == 'H') ? getPlayerMove(board) : getComputerMove(board, computer, player);
            board[move] = computer;
            cwin = checkWin(board, computer);
            nextTurn = player;
        }
    }

    drawBoard(board);
    if (pwin) printf("\nPlayer 1 is victorious!!!");
    else if (cwin) 
    {
        if (mode == 'H') printf("\nPlayer 2 has crushed the competition!!");
        else printf("\nTicTacToeBot 3000 is victorious once again! Puny human!");
    }
    else printf("\nIt's a cat's game! Oh well...");

    printf("\nThank you for playing!\n");
        
    return 0;
}