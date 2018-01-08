#include "stdafx.h"
#include "IBrick.h"
#include "Brick.h"
#include <string.h>
#include <malloc.h>

int CIBrick::shiftLeft(CBin* bin)
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
int CIBrick::shiftDown(CBin* bin)
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
int CIBrick::shiftRight(CBin* bin)
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
int CIBrick::rotateClockwise(CBin* bin)
{
	unsigned int orientation, oldOrientation;
	orientation = getOrientation();
	oldOrientation = orientation;
	if (orientation == 3)
		orientation = 0;
	else
		orientation = orientation + 1;
	setOrientation(orientation);
	if (checkCollision(bin) == 0) {
		setOrientation(oldOrientation);
		return 0;
	}
	return 1;
}
int CIBrick::checkCollision(CBin* bin)
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
	// I-brick Îª×´Ì¬ 0
	if (width == 10 + LocateOfPlayer1Game)
	{
		if (orientation == 0)
		{
			//×©¿é³¬³ö±ß½ç
			if ((posX + 1 < LocateOfPlayer1Game + 1) || (posX > width - 1) || (posY<1) || (posY + 2>height - 1))
				return 0;
			//×©¿éÍ¬ÆäËû×©¿éÖØµþ
			if ((image[posY - 1][posX] != 0) || (image[posY][posX] != 0) ||
				(image[posY + 1][posX] != 0) || (image[posY + 2][posX] != 0))
				return 0;
		}
		// I-brick Îª×´Ì¬ 1
		if (orientation == 1)
		{
			if ((posX - 1 < LocateOfPlayer1Game + 1) || (posX + 1 > width - 1) || (posY + 1 < 1) || (posY > height - 1))
				return 0;
			if ((image[posY][posX - 2] != 0) || (image[posY][posX - 1] != 0) ||
				(image[posY][posX] != 0) || (image[posY][posX + 1] != 0))
				return 0;
		}
		// I-brick Îª×´Ì¬ 2
		if (orientation == 2)
		{
			if ((posX + 1 < LocateOfPlayer1Game + 1) || (posX > width - 1) || (posY<2) || (posY + 1>height - 1))
				return 0;
			if ((image[posY - 2][posX] != 0) || (image[posY - 1][posX] != 0) ||
				(image[posY][posX] != 0) || (image[posY + 1][posX] != 0))
				return 0;
		}
		// I-brick Îª×´Ì¬ 3
		if (orientation == 3)
		{
			if ((posX<LocateOfPlayer1Game + 1) || (posX + 2>width - 1) || (posY + 1 < 1) || (posY > height - 1))
				return 0;
			if ((image[posY][posX - 1] != 0) || (image[posY][posX] != 0) ||
				(image[posY][posX + 1] != 0) || (image[posY][posX + 2] != 0))
				return 0;
		}
	}

	if (width == 10 + LocateOfPlayer2Game)
	{
		if (orientation == 0)
		{
			//×©¿é³¬³ö±ß½ç
			if ((posX + 1 < LocateOfPlayer2Game + 1) || (posX > width - 1) || (posY<1) || (posY + 2>height - 1))
				return 0;
			//×©¿éÍ¬ÆäËû×©¿éÖØµþ
			if ((image[posY - 1][posX] != 0) || (image[posY][posX] != 0) ||
				(image[posY + 1][posX] != 0) || (image[posY + 2][posX] != 0))
				return 0;
		}
		// I-brick Îª×´Ì¬ 1
		if (orientation == 1)
		{
			if ((posX - 1 < LocateOfPlayer2Game + 1) || (posX + 1 > width - 1) || (posY + 1 < 1) || (posY > height - 1))
				return 0;
			if ((image[posY][posX - 2] != 0) || (image[posY][posX - 1] != 0) ||
				(image[posY][posX] != 0) || (image[posY][posX + 1] != 0))
				return 0;
		}
		// I-brick Îª×´Ì¬ 2
		if (orientation == 2)
		{
			if ((posX + 1 < LocateOfPlayer2Game + 1) || (posX > width - 1) || (posY<2) || (posY + 1>height - 1))
				return 0;
			if ((image[posY - 2][posX] != 0) || (image[posY - 1][posX] != 0) ||
				(image[posY][posX] != 0) || (image[posY + 1][posX] != 0))
				return 0;
		}
		// I-brick Îª×´Ì¬ 3
		if (orientation == 3)
		{
			if ((posX<LocateOfPlayer2Game + 1) || (posX + 2>width - 1) || (posY + 1 < 1) || (posY > height - 1))
				return 0;
			if ((image[posY][posX - 1] != 0) || (image[posY][posX] != 0) ||
				(image[posY][posX + 1] != 0) || (image[posY][posX + 2] != 0))
				return 0;
		}
	}
	return 1;
}
void CIBrick::operator>>(unsigned char** binImage)
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
		binImage[posY - 1][posX] = colour;
		binImage[posY][posX] = colour;
		binImage[posY + 1][posX] = colour;
		binImage[posY + 2][posX] = colour;
	}
	if (orientation == 1)
	{
		binImage[posY][posX - 2] = colour;
		binImage[posY][posX - 1] = colour;
		binImage[posY][posX] = colour;
		binImage[posY][posX + 1] = colour;
	}
	if (orientation == 2)
	{
		binImage[posY - 2][posX] = colour;
		binImage[posY - 1][posX] = colour;
		binImage[posY][posX] = colour;
		binImage[posY + 1][posX] = colour;
	}
	if (orientation == 3)
	{
		binImage[posY][posX - 1] = colour;
		binImage[posY][posX] = colour;
		binImage[posY][posX + 1] = colour;
		binImage[posY][posX + 2] = colour;
	}
}
void CIBrick::putAtTop(unsigned int newOrient, unsigned int newPosX)
{
	setPosX(newPosX);
	setOrientation(newOrient);
	switch (newOrient)
	{
	case 0: setPosY(1); break;
	case 1: setPosY(0); break;
	case 2: setPosY(2); break;
	case 3: setPosY(0); break;
	}
}