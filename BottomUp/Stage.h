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
		NONE, BLOCK, ITEM1, ITEM2
	};

public:
	Stage();

	int getStageStart();
	int getIsChangeStage();
	void setIsChangeStage(int a);

	void scroll();
	void  draw(int map[96][20], int GH1, int GH2, int GH3);
};