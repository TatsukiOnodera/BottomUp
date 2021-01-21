#include "Item.h"

Item::Item()
{
	boxPosX = 0;
	boxPosY = 0;

	enum status Item1;
}

void Item::select(int& cursorX, int& cursorY, const int WIN_WIDTH, const int WIN_HEIGHT)
{
	if (cursorX >= WIN_WIDTH - 220)
	{
		if (cursorY <= WIN_HEIGHT / 2 && Item1 == NONE)
		{
			Item1 = SELECT;
		}
		if (cursorY > WIN_HEIGHT / 2 && cursorY <= WIN_HEIGHT && Item2 == NONE)
		{
			Item2 = SELECT;
		}
	} 
}

void Item::carry(int& mouse, int& oldMouse)
{
	if (Item1 == SELECT)
	{
		if (Item1 == SELECT)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				Item1 = CARRY;
			}
		}
	}
}

void Item::put(int& cursorX, int& cursorY, int& mouse, int& oldMouse, int map[24][20], Stage* stage)
{
	boxPosX = cursorX / 64;
	boxPosY = (cursorY - stage->getStageStart()) / 64;

	if (cursorX <= 1500 && cursorY <= 844 && cursorX >= 0 && cursorY >= 0 && stage->getIsChangeStage() == 0)
	{
		if (Item1 == CARRY)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				Item1 = PUT;
			}
		}
		if (Item2 == CARRY)
		{
			if (mouse == 1 && oldMouse == 0)
			{
				Item2 = PUT;
			}
		}

		for (int i = -1; i < 2; i++)
		{
			if (Item1 == PUT)
			{
				if (map[boxPosY + i][boxPosX] >= 2 || map[boxPosY][boxPosX] == 1 || map[boxPosY + 1][boxPosX] == 1
					|| map[boxPosY + 2][boxPosX] == 0 || map[boxPosY + 2][boxPosX] >= 2 || map[boxPosY - 1][boxPosX] != 1)
				{
					Item1 = NONE;
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (Item2 == PUT)
			{
				if (map[boxPosY][boxPosX + i] >= 2 || map[boxPosY][boxPosX - 1] != 1 || map[boxPosY][boxPosX + 3] != 1)
				{
					Item2 = NONE;
				}
			}
		}


		if (map[boxPosY][boxPosX] <= 1)
		{
			if (Item1 == PUT)
			{
				for (int i = -1; i < 2; i++)
				{
					map[boxPosY + i][boxPosX] = 2;
				}
				Item1 = NONE;
			}
			if (map[boxPosY][boxPosX] <= 1)
			{
				if (Item2 == PUT)
				{
					for (int i = 0; i < 3; i++)
					{
						map[boxPosY][boxPosX + i] = 3;
					}
					Item2 = NONE;
				}
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
	if (Item1 <= CARRY)
	{
		DrawBox(WIN_WIDTH - 220, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(255, 255, 0), 1);
		DrawBox(WIN_WIDTH - 220, 0, WIN_WIDTH, WIN_HEIGHT / 2, GetColor(0, 0, 0), 0);
	} 
	else if (Item2 <= CARRY)
	{
		DrawBox(WIN_WIDTH - 220, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(255, 255, 0), 1);
		DrawBox(WIN_WIDTH - 220, WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), 0);
	}
	DrawBox(0, 768, WIN_WIDTH - 220, WIN_HEIGHT, GetColor(255, 255, 255), 1);
	DrawBox(0, 768, WIN_WIDTH - 220, WIN_HEIGHT, GetColor(0, 0, 0), 0);
	if (Item1 == CARRY)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(cursorX - 32, cursorY - 96, cursorX + 31, cursorY + 96, GetColor(255, 0, 0), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	} 
	else if (Item2 == CARRY)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
		DrawBox(cursorX - 32, cursorY - 32, cursorX + 159, cursorY + 31, GetColor(0, 0, 255), 1);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	}
}