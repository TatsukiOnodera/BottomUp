#pragma once
#include "DxLib.h"
#include "Stage.h"

class Item
{
private:
	int boxPosX;
	int boxPosY;
	int is

public:
	Item();

	void reset();
	void select(int& cursorX, int& cursorY, const int WIN_WIDTH, const int WIN_HEIGHT);
	void carry(int& mouse, int& oldMouse);
	void put(int& cursorX, int& cursorY, int& mouse, int& oldMouse, int map[96][20], Stage* stage, int SH1);
	void draw(const int WIN_WIDTH, const int WIN_HEIGHT, int& cursorX, int& cursorY);
};