#include "stdafx.h"
#include "OBrick.h"
#include "Brick.h"
#include <string.h>
#include <malloc.h>

int COBrick::shiftLeft(CBin* bin)
{
	unsigned int posX;
	posX = getPosX();
	posX = posX - 1;
	setPosX(posX);
	if (checkCollision(bin) == 0) {
		setPosX(posX + 1);
		return 0;
	}
	return 1;
}
int COBrick::shiftDown(CBin* bin)
{
	unsigned int posY;
	posY = getPosY();
	posY = posY + 1;
	setPosY(posY);
	if (checkCollision(bin) == 0) {
		setPosY(posY - 1);
		return 0;
	}
	return 1;
}
int COBrick::shiftRight(CBin* bin)
{
	unsigned int posX;
	posX = getPosX();
	posX = posX + 1;
	setPosX(posX);
	if (checkCollision(bin) == 0) {
		setPosX(posX - 1);
		return 0;
	}
	return 1;
}
int COBrick::rotateClockwise(CBin* bin)
{
	unsigned int orientation, oldOrientation;
	orientation = getOrientation();
	oldOrientation = orientation;
	if (orientation == 0)
		orientation = 0;
	else
		orientation = orientation;
	setOrientation(orientation);
	if (checkCollision(bin) == 0) {
		setOrientation(oldOrientation);
		return 0;
	}
	return 1;
}
int COBrick::checkCollision(CBin* bin)
{
	unsigned int width;
	unsigned int height;
	unsigned char** image;
	unsigned int orientation;
	unsigned int posX;
	unsigned int posY;
	width = bin->getWidth();
	height = bin->getHeight();
	image = new unsigned char*[height];
	for (unsigned int i = 0; i<height; i++)
	{
		image[i] = new unsigned char[width];
	}
	bin->getImage(image);
	orientation = getOrientation();
	posX = getPosX();
	posY = getPosY();
	// O-brick 为状态 0
	if (width == 10 + LocateOfPlayer1Game)
	{
		if (orientation == 0)
		{
			//砖块超出边界
			if ((posX + 1 < LocateOfPlayer1Game + 1) || (posX > width - 2) || (posY + 1 < 1) || (posY + 1 > height - 1))
				return 0;
			//砖块同其他砖块重叠
			if ((image[posY][posX] != 0) || (image[posY][posX + 1] != 0) ||
				(image[posY + 1][posX] != 0) || (image[posY + 1][posX + 1] != 0))
				return 0;
		}
	}

	if (width == 10 + LocateOfPlayer2Game)
	{
		if (orientation == 0)
		{
			//砖块超出边界
			if ((posX + 1 < LocateOfPlayer2Game + 1) || (posX > width - 2) || (posY + 1 < 1) || (posY + 1 > height - 1))
				return 0;
			//砖块同其他砖块重叠
			if ((image[posY][posX] != 0) || (image[posY][posX + 1] != 0) ||
				(image[posY + 1][posX] != 0) || (image[posY + 1][posX + 1] != 0))
				return 0;
		}
	}
	return 1;
}
void COBrick::operator>>(unsigned char** binImage)
{
	unsigned int orientation;
	unsigned int posX;
	unsigned int posY;
	unsigned char colour;
	posX = getPosX();
	posY = getPosY();
	orientation = getOrientation();
	colour = getColour();
	if (orientation == 0)
	{
		binImage[posY][posX] = colour;
		binImage[posY][posX + 1] = colour;
		binImage[posY + 1][posX] = colour;
		binImage[posY + 1][posX + 1] = colour;
	}
}
void COBrick::putAtTop(unsigned int newOrient, unsigned int newPosX)
{
	setPosX(newPosX);
	setOrientation(newOrient);
	switch (newOrient)
	{
	case 0: setPosY(0); break;
	}
}
