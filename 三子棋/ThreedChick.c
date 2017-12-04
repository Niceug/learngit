#include"ThreeChick.h"
#include "menu.h"
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = '0';
		}
	}
}
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
void PlayerMove(char board[ROW][COL], int row, int col)
{
	int x, y;
	while (1)
	{
		printf("请输入坐标:\n");
		scanf("%d%d", &y, &x);
		if (board[x - 1][y - 1] == '0')
		{
			board[x - 1][y - 1] = '1';
			break;
		}
		printf("输入坐标不合法\n");
			
	}
	
}
void Computermove(char board[ROW][COL], int row, int col)
{
	int Computer_x = 0;
	int Computer_y = 0;
	if (ComputerHas2(board, row, col) == 1)
	{
		return;
	}
	if (playerHas2(board, row, col) == 1)
	{
		return;
	}
	while (1)
	{
		Computer_x = rand() % row;
		Computer_y = rand() % col;
		if (board[Computer_x][Computer_y] == '0')
		{
			board[Computer_x][Computer_y] = '*';
			break;
		}
	}
}
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	int Computer_winFlag = 0;
	int Player_winFlag = 0;

	///////////////////////////////////////////////////////////////
	//////////////////////判断电脑是否胜利/////////////////////////
	///////////////////////////////////////////////////////////////
	//判断电脑三个横着的
	Computer_winFlag = 0;
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[i][j] == '*')
			{
				Computer_winFlag++;
			}
		}
		if (Computer_winFlag == 3)
		{
			return '*';
		}
		Computer_winFlag = 0;
	}
	//判断电脑三个竖着的
	Computer_winFlag = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[j][i] == '*')
			{
				Computer_winFlag++;
			}
		}
		if (Computer_winFlag == 3)
		{
			return '*';
		}
		Computer_winFlag = 0;
	}
	Computer_winFlag = 0;
	//电脑三个斜着的1
	if ((board[0][0] == '*') && (board[1][1] == '*') && (board[2][2] == '*'))
	{
		return '*';
	}

	//电脑三个斜着的2
	if ((board[0][2] == '*') && (board[1][1] == '*') && (board[2][0] == '*'))
	{
		return '*';
	}

///////////////////////////////////////////////////////////////
//////////////////////判断玩家是否胜利/////////////////////////
///////////////////////////////////////////////////////////////
//判断玩家三个横着的
	Player_winFlag = 0;
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[i][j] == '1')
			{
				Player_winFlag++;
			}
		}
		if (Player_winFlag == 3)
		{
			return '1';
		}
		Player_winFlag = 0;
	}
	Player_winFlag = 0;
	//判断玩家三个竖着的

	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[j][i] == '1')
			{
				Player_winFlag++;
			}
		}
		if (Player_winFlag == 3)
		{
			return '1';
		}
		Player_winFlag = 0;
	}
	Player_winFlag = 0;
	//玩家三个斜着的1
	if ((board[0][0] == '1') && (board[1][1] == '1') && (board[2][2] == '1'))
	{
		return '1';
	}

	//玩家三个斜着的2
	if ((board[0][2] == '1') && (board[1][1] == '1') && (board[2][0] == '1'))
	{
		return '1';
	}
	return '0';
}

//判断玩家是否有两个连着的
int playerHas2(char board[ROW][COL], int row, int col)
{
	int i, j;
	int flag = 0;
	//判断玩家是否横着有2个
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[i][j] == '1')
			{
				flag++;
			}
		}
		//表示检测到有两个
		if (flag == 2)
		{
			flag = 0;
			if (board[i][0] == '0')
			{
				board[i][0] = '*';
				return 1;
			}
			else if (board[i][1] == '0')
			{
				board[i][1] = '*';
				return 1;
			}
			else if (board[i][2] == '0')
			{
				board[i][2] = '*';
				return 1;
			}
		}
		flag = 0;
	}
	flag = 0;
	//判断两个竖行
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[j][i] == '1')
			{
				flag++;
			}
		}
		//表示检测到有两个竖行
		if (flag == 2)
		{
			flag = 0;
			if (board[0][i] == '0')
			{
				board[0][i] = '*';
				return 1;
			}
			else if (board[1][i] == '0')
			{
				board[1][i] = '*';
				return 1;
			}
			else if (board[2][i] == '0')
			{
				board[2][i] = '*';
				return 1;
			}
		}
		flag = 0;
	}

	//////判断玩家是否有两个斜着的1///
	for (i = 0; i < row; i++)
	{
		if (board[i][i] == '1')
		{
			flag++;
		}
	}
	if (flag == 2)
	{
		flag = 0;
		if (board[0][0] == '0')
		{
			board[0][0] = '*';
			return 1;
		}
		else if (board[1][1] == '0')
		{
			board[1][1] = '*';
			return 1;
		}
		else if (board[2][2] == '0')
		{
			board[2][2] = '*';
			return 1;
		}
	}
	flag = 0;

	//////////判断玩家是否有两个斜着的1//////////
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == '1' && i + j == 2)
			{
				flag++;
			}
		}
	}
	if (flag == 2)
	{
		flag = 0;
		if (board[0][2] == '0')
		{
			board[0][2] = '*';
			return 1;
		}
		else if (board[1][1] == '0')
		{
			board[1][1] = '*';
			return 1;
		}
		else if (board[2][0] == '0')
		{
			board[2][0] = '*';
			return 1;
		}
	}
	flag = 0;
	return 0;
}

int ComputerHas2(char board[ROW][COL], int row, int col)
{
	int i, j;
	int flag = 0;
	//判断玩家是否横着有2个
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[i][j] == '*')
			{
				flag++;
			}
		}
		//表示检测到有两个
		if (flag == 2)
		{
			flag = 0;
			if (board[i][0] == '0')
			{
				board[i][0] = '*';
				return 1;
			}
			else if (board[i][1] == '0')
			{
				board[i][1] = '*';
				return 1;
			}
			else if (board[i][2] == '0')
			{
				board[i][2] = '*';
				return 1;
			}
		}
		flag = 0;
	}
	flag = 0;
	//判断两个竖行
	for (i = 0; i < col; i++)
	{
		for (j = 0; j < row; j++)
		{
			if (board[j][i] == '*')
			{
				flag++;
			}
		}
		//表示检测到有两个竖行
		if (flag == 2)
		{
			flag = 0;
			if (board[0][i] == '0')
			{
				board[0][i] = '*';
				return 1;
			}
			else if (board[1][i] == '0')
			{
				board[1][i] = '*';
				return 1;
			}
			else if (board[2][i] == '0')
			{
				board[2][i] = '*';
				return 1;
			}
		}
		flag = 0;
	}
	flag = 0;
	//////判断玩家是否有两个斜着的1///
	for (i = 0; i < row; i++)
	{
		if (board[i][i] == '*')
		{
			flag++;
		}
	}
	if (flag == 2)
	{
		flag = 0;
		if (board[0][0] == '0')
		{
			board[0][0] = '*';
			return 1;
		}
		else if (board[1][1] == '0')
		{
			board[1][1] = '*';
			return 1;
		}
		else if (board[2][2] == '0')
		{
			board[2][2] = '*';
			return 1;
		}
	}
	flag = 0;
	//////////判断玩家是否有两个斜着的1//////////
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == '*' && (i + j == 2))
			{
				
				flag++;
			}
		}
	}
	if (flag == 2)
	{
		flag = 0;
		if (board[0][2] == '0')
		{
			board[0][2] = '*';
			return 1;
		}
		else if (board[1][1] == '0')
		{
			board[1][1] = '*';
			return 1;
		}
		else if (board[2][0] == '0')
		{
			board[2][0] = '*';
			return 1;
		}
	}
	flag = 0;
	return 0;
}

int main()
{
	srand((unsigned int)time(NULL));
	char board[ROW][COL];
	int stepCount = 0;//记录下棋步数，用来判断是否平局
	int option = 0;
	while (1)
	{
		option = showMenu();
		switch (option)
		{
		case 0: return 0;
		case 1: {
			InitBoard(board, ROW, COL);
			stepCount = 0;
			while (1)
			{
				DisplayBoard(board, ROW, COL);
				PlayerMove(board, ROW, COL);
				++stepCount;
				if (stepCount == ROW*COL)
				{
					printf("平局！\n");
					DisplayBoard(board, ROW, COL);
					break;
				}
				if (stepCount > 4)//从第5步开始判断游戏是否有人胜利
				{
					if (IsWin(board, ROW, COL) == '1')
					{
						printf("玩家胜利! \n");
						DisplayBoard(board, ROW, COL);
						break;
					}
				}
				Computermove(board, ROW, COL);
				++stepCount;
				if (stepCount > 4)//从第5步开始判断游戏是否有人胜利
				{
					if (IsWin(board, ROW, COL) == '*')
					{
						printf("电脑胜利! \n");
						DisplayBoard(board, ROW, COL);
						break;
					}
				}
			}
		}break;
		default: printf("选择错误！\n");
			break;
		}
	}
	return 0;
}