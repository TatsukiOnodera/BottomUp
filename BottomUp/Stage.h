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
	void  draw(int map[24][20], int& GH4, int& GH5, int& GH6);
};