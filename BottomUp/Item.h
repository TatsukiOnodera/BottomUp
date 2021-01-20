#pragma once
#include "DxLib.h"
#include "Stage.h"

class Item
{
private:
	int boxPosX;
	int boxPosY;
	int Item1;
	int Item2;
	enum status
	{
		NONE, SELECT, CARRY, PUT
	};

public:
	Item();

	void select(int& cursorX, int& cursorY, const int WIN_WIDTH, const int WIN_HEIGHT);
	void carry(int& mouse, int& oldMouse);
	void put(int& cursorX, int& cursorY, int& mouse, int& oldMouse, int map[24][20], Stage* stage);
	void draw(const int WIN_WIDTH, const int WIN_HEIGHT, int& cursorX, int& cursorY);
};