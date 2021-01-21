#include "Stage.h"

Stage::Stage()
{
	stageStart = -768;
	mapChipSize = 64;
	isChangeStage = 0;
	floor = 2;
}

int Stage::getStageStart() { return stageStart; }

int Stage::getIsChangeStage() { return isChangeStage; }

void Stage::setIsChangeStage(int a) { isChangeStage = a; }

void Stage::scroll()
{
	if (isChangeStage == 1)
	{
		stageStart += 37;
		if (stageStart > (floor - 2) * -768)
		{
			stageStart = 0;
			isChangeStage = 0;
			floor -= 1;
			if (floor < 2)
			{
				floor = 2;
			}
		}
	}
}

void Stage::draw(int map[24][20], int& GH4, int& GH5, int& GH6)
{
	for (int j = 0; j < 2; j++)
	{
		if (j % 1 == 1)
		{
			DrawGraph(0, (j + stageStart) + j * 768, GH4, 1);
		} else if (j % 1 == 0)
		{
			DrawGraph(0, (j + stageStart) + j * 768, GH5, 1);
		} else if (j % 2 == 0)
		{
			DrawGraph(0, (j + stageStart) + j * 768, GH6, 1);
		}
	}
	for (int y = 0; y < 24; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (map[y][x] == BLOCK)
			{
				DrawBox(x * 64, (y + stageStart) + y * (mapChipSize - 1), x * 64 + 64, (y + stageStart) + y * (mapChipSize - 1) + 64, GetColor(50, 50, 50), 1);
				DrawBox(x * 64, (y + stageStart) + y * (mapChipSize - 1), x * 64 + 64, (y + stageStart) + y * (mapChipSize - 1) + 64, GetColor(255, 255, 255), 0);
			}
			if (map[y][x] == ITEM1)
			{
				DrawBox(x * 64, (y + stageStart) + y * (mapChipSize - 1), x * 64 + 64, (y + stageStart) + y * (mapChipSize - 1) + 64, GetColor(255, 0, 0), 1);
				DrawBox(x * 64, (y + stageStart) + y * (mapChipSize - 1), x * 64 + 64, (y + stageStart) + y * (mapChipSize - 1) + 64, GetColor(255, 255, 255), 0);
			}
			if (map[y][x] == ITEM2)
			{
				DrawBox(x * 64, (y + stageStart) + y * (mapChipSize - 1), x * 64 + 64, (y + stageStart) + y * (mapChipSize - 1) + 64, GetColor(0, 0, 255), 1);
				DrawBox(x * 64, (y + stageStart) + y * (mapChipSize - 1), x * 64 + 64, (y + stageStart) + y * (mapChipSize - 1) + 64, GetColor(255, 255, 255), 0);
			}
		}
	}
}