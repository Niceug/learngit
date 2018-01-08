#pragma once
#include "Bin.h"
class CBrick {
protected:
	unsigned int orientation; //表示砖块的状态
	unsigned int posX; //砖块特定点的 X 坐标
	unsigned int posY; //砖块特定点的 Y 坐标
	unsigned char colour; //砖块的颜色
public:
	unsigned int getOrientation() { return orientation; };
	unsigned int getPosX() { return posX; };
	unsigned int getPosY() { return posY; };
	unsigned char getColour() { return colour; };
	void setOrientation(unsigned int newOrient) { orientation = newOrient; };
	void setPosX(unsigned int newPosX) { posX = newPosX; };
	void setPosY(unsigned int newPosY) { posY = newPosY; };
	void setColour(unsigned char newColour) { colour = newColour; };
	virtual int shiftLeft(CBin* bin) = 0;
	virtual int shiftRight(CBin* bin) = 0;
	virtual int shiftDown(CBin* bin) = 0;
	virtual int rotateClockwise(CBin* bin) = 0;
	virtual int checkCollision(CBin* bin) = 0;
	virtual void operator>>(unsigned char** binImage) = 0;
	virtual void putAtTop(unsigned int newOrient, unsigned int newPosX) = 0;
};

