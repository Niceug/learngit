#ifndef __GAME_H__
#define __GAME_H__
#define ROW 3
#define COL 3

void InitBoard(char board[ROW][COL], int row, int col);
void DisplayBoard(char board[ROW][COL], int row, int col);
void PlayerMove(char board[ROW][COL], int row, int col);
void Computermove(char board[ROW][COL], int row, int col);
char IsWin(char board[ROW][COL], int row, int col);
#endif //__GAME_H__