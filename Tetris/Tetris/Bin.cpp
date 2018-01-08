#include "stdafx.h"
#include "Bin.h"
CBin::CBin(unsigned int w, unsigned int h)
{
	width = w;
	height = h;
	image = new unsigned char*[height];
	for (unsigned int i = 0; i < height; i++)
	{
		image[i] = new unsigned char[width];
		for (unsigned int j = 0; j < width; j++)
			image[i][j] = 0;
	}
}

CBin::~CBin()
{
	for (unsigned int i = 0; i<height; i++)
	{
		delete image[i];
	}
	delete[] image;
}

void CBin::getImage(unsigned char** destImage)
{
	for (unsigned int i = 0; i < height; i++)
		for (unsigned int j = 0; j < width; j++)
			destImage[i][j] = image[i][j];
}


void CBin::setImage(unsigned char** srcImage)
{
	if (width == LocateOfPlayer1Game + 10)
	{
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = LocateOfPlayer1Game; j < width; j++)
			{
				image[i][j] = srcImage[i][j];
			}

		}
	}

	if (width == LocateOfPlayer2Game + 10)
	{
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = LocateOfPlayer2Game; j < width; j++)
			{
				image[i][j] = srcImage[i][j];
			}

		}
	}
}

unsigned int CBin::removeFullLines()
{
	unsigned int flag, EmptyLine = 0;
	unsigned int i, j, m;


	//玩家1方块满行消除
	if (width == LocateOfPlayer1Game + 10)
	{
		for (i = 0; i < height; i++)
		{
			flag = 0;
			for (j = LocateOfPlayer1Game; j < width; j++)
			{
				if (image[i][j] == 0)
					flag = 1;
			}
			//当一行被完全填满
			if (flag == 0)
			{
				for (j = LocateOfPlayer1Game; j < width; j++)
				{
					image[i][j] = 0; //当前行清零，即删除
				}
				//上面的砖块下落
				for (m = i; m > 0; m--)
				{
					for (j = LocateOfPlayer1Game; j < width; j++)
					{
						image[m][j] = image[m - 1][j];
					}
				}
				for (j = LocateOfPlayer1Game; j < width; j++)
				{
					image[0][j] = 0;
				}
				EmptyLine++; //记录被删除的行数
				i--;
			}
		}
	}

	//玩家2方块满行消除
	if (width == LocateOfPlayer2Game + 10)
	{
		for (i = 0; i < height; i++)
		{
			flag = 0;
			for (j = LocateOfPlayer2Game; j < width; j++)
			{
				if (image[i][j] == 0)
					flag = 1;
			}
			//当一行被完全填满
			if (flag == 0)
			{
				for (j = LocateOfPlayer2Game; j < width; j++)
				{
					image[i][j] = 0; //当前行清零，即删除
				}
				//上面的砖块下落
				for (m = i; m > 0; m--)
				{
					for (j = LocateOfPlayer2Game; j < width; j++)
					{
						image[m][j] = image[m - 1][j];
					}
				}
				for (j = LocateOfPlayer2Game; j < width; j++)
				{
					image[0][j] = 0;
				}
				EmptyLine++; //记录被删除的行数
				i--;
			}
		}
	}
	return EmptyLine;
}
