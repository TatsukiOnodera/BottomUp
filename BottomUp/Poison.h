#pragma once
#include "Stage.h"

class Poison{
private:
	int posY;
	int count;

public:
	Poison();

	int getPosY();

	void move(Stage* stage);
	void draw(Stage *stage);
};