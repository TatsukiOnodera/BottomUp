#pragma once
#include "DxLib.h"
#include "Stage.h"

class Character
{
private:
	int posX;
	int posY;
	int upCount;
	int point;
	int isMove;
	int isClimb;
	int isDead;
	int isAnimation;
	int animationCount;
	int animationPoint;
	int direction;
	int count;
	enum animtion
	{
		STAND, WALK, CLIMB, DEAD
	};

public:
	Character();

	void reset();
	void clear(int &isGameClear, Stage* stage);
	void changeStage(Stage* stage);
	void move(Stage* stage, int map[96][20]);
	void collisionPoison(int &isGameover);
	void draw(Stage* stage, int GH1, int GH2);
};