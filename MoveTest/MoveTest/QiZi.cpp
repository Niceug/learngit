#include "stdafx.h"
#include "QiZi.h"


bool CQiZi::AIPlay(int Location_x, int Location_y)
{
	g_Brick[Location_x + 1][Location_y + 1] = 3;
	printf("jinru\n");
	return 0;
}
int CQiZi::Robot4Qizi()
{
	//AI斜着4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{

			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i + 4][j + 4] == 0)
				{
					g_Brick[i + 4][j + 4] = 3;
					return 1;
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					g_Brick[i - 1][j - 1] = 3;
					return 1;
				}
				else if (g_Brick[i + 4][j + 4] != 0 && g_Brick[i - 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//AI斜着4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i - 4][j + 4] == 0)
				{
					g_Brick[i - 4][j + 4] = 3;
					return 1;
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					g_Brick[i + 1][j - 1] = 3;
					return 1;
				}
				else if (g_Brick[i - 4][j + 4] != 0 && g_Brick[i + 1][j - 1] != 0)
				{
					break;
				}
			}
		}

	//横着有4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j + 4] == 0)
				{
					g_Brick[i][j + 4] = 3;
					return 1;
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					g_Brick[i][j - 1] = 3;
					return 1;
				}
				if (g_Brick[i][j + 4] != 0 && g_Brick[i][j - 1] != 0)
				{
					break;
				}
			}
		}

	//竖着有4个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i + 4][j] == 0)
				{
					g_Brick[i + 4][j] = 3;
					return 1;
				}
				if (g_Brick[i - 1][j] == 0)
				{
					g_Brick[i - 1][j] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j] != 0 && g_Brick[i - 1][j] != 0)
				{
					break;
				}
			}
		}
	return 0;
}
int CQiZi::Robot3QiZi()
{
	//斜着WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 0 && g_Brick[i + 2][j + 2] == 3 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i - 1][j - 1] != 1)
				{
					g_Brick[i + 1][j + 1] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j + 4] != 1)
				{
					g_Brick[i + 1][j + 1] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j + 4] == 1 && g_Brick[i - 1][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 0 && g_Brick[i + 3][j + 3] == 3)
			{
				if (g_Brick[i - 1][j - 1] != 1)
				{
					g_Brick[i + 2][j + 2] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j + 4] != 1)
				{
					g_Brick[i + 2][j + 2] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j + 4] == 1 && g_Brick[i - 1][j - 1] == 1)
					break;
			}
		}
	//斜着WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 0 && g_Brick[i - 2][j + 2] == 3 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i + 1][j - 1] != 1)
				{
					g_Brick[i - 1][j + 1] = 3;
					return 1;
				}
				if (g_Brick[i - 4][j + 4] != 1)
				{
					g_Brick[i - 1][j + 1] = 3;
					return 1;
				}
				if (g_Brick[i - 4][j + 4] == 1 && g_Brick[i + 1][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 0 && g_Brick[i - 3][j + 3] == 3)
			{
				if (g_Brick[i + 1][j - 1] != 1)
				{
					g_Brick[i - 2][j + 2] = 3;
					return 1;
				}
				if (g_Brick[i - 4][j + 4] != 1)
				{
					g_Brick[i - 2][j + 2] = 3;
					return 1;
				}
				if (g_Brick[i - 4][j + 4] == 1 && g_Brick[i + 1][j - 1] == 1)
					break;
			}
		}
	//横着1101
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 0 && g_Brick[i][j + 2] == 3 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j - 1] != 1)
				{
					g_Brick[i][j + 1] = 3;
					return 1;
				}
				if (g_Brick[i][j + 4] != 1)
				{
					g_Brick[i][j + 1] = 3;
					return 1;
				}
				if (g_Brick[i][j + 4] == 1 && g_Brick[i][j - 1] == 1)
					break;
			}
		}

	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 0 && g_Brick[i][j + 3] == 3)
			{
				if (g_Brick[i][j - 1] != 1)
				{
					g_Brick[i][j + 2] = 3;
					return 1;
				}
				if (g_Brick[i][j + 4] != 1)
				{
					g_Brick[i][j + 2] = 3;
					return 1;
				}
				if (g_Brick[i][j + 4] == 1 && g_Brick[i][j - 1] == 1)
					break;
			}
		}
	//竖着WidthAndHigh01
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 0 && g_Brick[i + 2][j] == 3 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i - 1][j] != 1)
				{
					g_Brick[i + 1][j] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j] != 1)
				{
					g_Brick[i + 1][j] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j] == 1 && g_Brick[i - 1][j] == 1)
					break;
			}
		}
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 0 && g_Brick[i + 3][j] == 3)
			{
				if (g_Brick[i - 1][j] != 1)
				{
					g_Brick[i + 2][j] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j] != 1)
				{
					g_Brick[i + 2][j] = 3;
					return 1;
				}
				if (g_Brick[i + 4][j] == 1 && g_Brick[i - 1][j] == 1)
					break;
			}
		}
	//处理三个子的情况
	//AI斜着三个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j + 1] == 3 && g_Brick[i + 2][j + 2] == 3)
			{
				if (g_Brick[i + 3][j + 3] == 0)
				{
					g_Brick[i + 3][j + 3] = 3;
					return 1;
				}
				else if (g_Brick[i - 1][j - 1] == 0)
				{
					g_Brick[i - 1][j - 1] = 3;
					return 1;
				}
				else if (g_Brick[i + 3][j + 3] == 1 && g_Brick[i - 1][j - 1] == 1)
				{
					break;
				}
			}
		}

	//AI斜着三个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i - 1][j + 1] == 3 && g_Brick[i - 2][j + 2] == 3)
			{
				if (g_Brick[i - 3][j + 3] == 0)
				{
					g_Brick[i - 3][j + 3] = 3;
					return 1;
				}
				else if (g_Brick[i + 1][j - 1] == 0)
				{
					g_Brick[i + 1][j - 1] = 3;
					return 1;
				}
				else if (g_Brick[i - 3][j + 3] == 1 && g_Brick[i + 1][j - 1] == 1)
				{
					break;
				}
			}
		}


	//横着有3个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i][j + 1] == 3 && g_Brick[i][j + 2] == 3)
			{
				if (g_Brick[i][j + 3] == 0)
				{
					g_Brick[i][j + 3] = 3;
					return 1;
				}
				else if (g_Brick[i][j - 1] == 0)
				{
					g_Brick[i][j - 1] = 3;
					return 1;
				}
				if (g_Brick[i][j + 3] == 1 && g_Brick[i][j - 1] == 1)
				{
					break;
				}
			}
		}
	//竖着有3个子
	for (int i = 0; i < WidthAndHigh; i++)
		for (int j = 0; j < WidthAndHigh; j++)
		{
			if (g_Brick[i][j] == 3 && g_Brick[i + 1][j] == 3 && g_Brick[i + 2][j] == 3)
			{
				if (g_Brick[i + 3][j] == 0)
				{
					g_Brick[i + 3][j] = 3;
					return 1;
				}
				if (g_Brick[i - 1][j] == 0)
				{
					g_Brick[i - 1][j] = 3;
					return 1;
				}
				if (g_Brick[i + 3][j] == 1 && g_Brick[i - 1][j] == 1)
				{
					break;
				}
			}
		}
	return 0;
}
void CQiZi::RobotPlayer(int Location_x, int Location_y)
{}



