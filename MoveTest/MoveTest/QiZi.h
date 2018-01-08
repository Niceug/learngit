#pragma once
#define WidthAndHigh 20
class CQiZi
{
public:
	int g_Brick[WidthAndHigh][WidthAndHigh];
	bool AIPlay(int Location_x, int Location_y);
	int Robot4Qizi();
	int Robot3QiZi();
	void RobotPlayer(int Location_x, int Location_y);

};

