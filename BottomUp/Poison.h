#pragma once
#include "Stage.h"

class Poison{
private:
	int posY;
	int collisionY;
	int count;
	int animationNumber;
	int animationCount;

public:
	Poison();

	int getCollisionY();

	void reset();
	void move(Stage* stage);
	void draw(Stage *stage, int GH1);
};