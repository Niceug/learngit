#pragma once
#include "Bin.h"
class CBrick {
protected:
	unsigned int orientation; //��ʾש���״̬
	unsigned int posX; //ש���ض���� X ����
	unsigned int posY; //ש���ض���� Y ����
	unsigned char colour; //ש�����ɫ
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

