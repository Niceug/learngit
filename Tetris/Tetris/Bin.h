#pragma once
#ifndef BIN_H
#define BIN_H

/*����2�������Ϸ�������λ��*/
#define LocateOfPlayer1Game 6
#define LocateOfPlayer2Game 20
class CBin {
private:
	unsigned char** image;
	unsigned int width;
	unsigned int height;
public:
	CBin(unsigned int w, unsigned int h);
	~CBin();
	unsigned int getWidth() { return width; };
	unsigned int getHeight() { return height; };
	void getImage(unsigned char** destImage);
	void setImage(unsigned char** srcImage);
	unsigned int removeFullLines();
};
#endif