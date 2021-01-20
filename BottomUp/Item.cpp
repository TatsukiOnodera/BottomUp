#include "Item.h"

Item::Item()
{
	boxPosX = 0;
	boxPosY = 0;
	isSelect = 0;
	isCarry = 0;
	isPut = 0;
}

void Item::select(int& cursorX, int& cursorY, const int WIN_WIDTH, const int WIN_HEIGHT)
{
	if (cursorX >= WIN_WIDTH - 220)
	{
		if (cursorY <= WIN_HEIGHT / 2)
		{
			isSelect = 1;
		}
		if (cursorY > WIN_HEIGHT / 2 && cursorY <= WIN_HEIGHT)
		{
			isSelect = 2;
		}
	} else
	{
		isSelect = 0;
	}
}

void Item::carry(int& mouse, int& oldMouse)
{
	if (isSelect == 1)
	{
		if (isCarry == 0 || isCarry == 2)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isCarry = 1;
			}
		} else if (isCarry <= 2)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isCarry = 0;
			}
		}
	}
	if (isSelect == 2)
	{
		if (isCarry == 0 || isCarry == 1)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isCarry = 2;
			}
		} else if (isCarry <= 2)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isCarry = 0;
			}
		}
	}
}

void Item::put(int& cursorX, int& cursorY, int& mouse, int& oldMouse, int map[24][20], Stage* stage)
{
	boxPosX = cursorX / 64;
	boxPosY = (cursorY - stage->getStageStart()) / 64;

	if (cursorX <= 1280 && cursorY <= 768 && cursorX >= 0 && cursorY >= 0 && stage->getIsChangeStage() == 0)
	{
		if (isCarry == 1)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isPut = 1;
				isCarry = 0;
			}
		}
		if (isCarry == 2)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				isPut = 2;
				isCarry = 0;
			}
		}

		for (int i = -1; i < 2; i++)
		{
			if (isPut == 1)
			{
				if (map[boxPosY + i][boxPosX] >= 2 || map[boxPosY][boxPosX] == 1 || map[boxPosY + 1][boxPosX] == 1
					|| map[boxPosY + 2][boxPosX] == 0 || map[boxPosY + 2][boxPosX] >= 2 || map[boxPosY - 1][boxPosX] != 1)
				{
					isPut = 0;
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (isPut == 2)
			{
				if (map[boxPosY][boxPosX + i] >= 2 || map[boxPosY][boxPosX - 1] != 1 || map[boxPosY][boxPosX + 3] != 1)
				{
					isPut = 0;
				}
			}
		}


		if (map[boxPosY][boxPosX] <= 1)
		{
			if (isPut == 1)
			{
				for (int i = -1; i < 2; i++)
				{
					map[boxPosY + i][boxPosX] = 2;
				}
			}
			if (map[boxPosY][boxPosX] <= 1)
			{
				if (isPut == 2)
				{
					for (int i = 0; i < 3; i++)
					{
						map[boxPosY][boxPosX + i] = 3;
					}
				}
				isPut = 0;
			}
		}
	}
}

void Item::draw(const int WIN_WIDTH, const int WIN_HEIGHT, int& cursorX, int& cursorY)
{
	DrawBox(WIN_WIDTH - 220, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(255, 255, 255), 1);
	DrawBox(WIN_WIDTH - 220, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(0, 0, 0), 0);
	DrawBox(WIN_WIDTH - 220, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 255, 255), 1);
	DrawBox(WIN_WIDTH - 220, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), 0);
	if (isSelect == 1)
	{
		DrawBox(WIN_WIDTH - 220, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(255, 255, 0), 1);
		DrawBox(WIN_WIDTH - 220, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(0, 0, 0), 0);
	} else if (isSelect == 2)
	{
		DrawBox(WIN_WIDTH - 220, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 255, 0), 1);
		DrawBox(WIN_WIDTH - 220, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), 0);
	}
	DrawBox(0, 768, WIN_WIDTH - 220, WIN_HEIGHT, GetColor(255, 255, 255), 1);
	DrawBox(0, 768, WIN_WIDTH - 220, WIN_HEIGHT, GetColor(0, 0, 0), 0);
	if (isCarry == 1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(cursorX - 32, cursorY - 96, cursorX + 31, cursorY + 96, GetColor(255, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	} else if (isCarry == 2)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(cursorX - 32, cursorY - 32, cursorX + 159, cursorY + 31, GetColor(0, 0, 255), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	}
}