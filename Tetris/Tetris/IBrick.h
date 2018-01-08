#pragma once
#include "Bin.h"
#include "Brick.h"
class CIBrick : public CBrick {
public:
	int shiftLeft(CBin* bin);
	int shiftRight(CBin* bin);
	int shiftDown(CBin* bin);
	int rotateClockwise(CBin* bin);
	int checkCollision(CBin* bin);
	void operator>>(unsigned char** binImage);
	void putAtTop(unsigned int newOrient, unsigned int newPosX);
};