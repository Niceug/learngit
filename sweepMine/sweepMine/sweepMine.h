#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10

void InitBoard(int board[ROW][COL], int row, int col);
void InitBoardImg(int boardImg[ROWS][COLS], int rows, int cols);
void DisplayBoard(int board[ROW][COL], int row, int col);
void SetMine(int boardImg[ROWS][COLS], int row, int col);
int GetMineCount();
int ClearMine(int board[ROW][COL]);
#endif//__GAME_H__