#pragma once
#include "DxLib.h"

class Stage
{
private:
	int stageStart;
	int mapChipSize;
	int isChangeStage;
	int floor;
	enum resource
	{
		NONE, BLOCK, ITEM1, ITEM2, WALL
	};

public:
	Stage();

	int getStageStart();
	int getIsChangeStage();
	int getFloor();
	void setIsChangeStage(int a);

	void reset();
	void scroll();
	void  draw(int map[96][20], int GH1, int GH2, int GH3, int GH4, int GH5, int GH7);
};