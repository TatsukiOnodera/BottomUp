#pragma once
#include "DxLib.h"
#include "Stage.h"
#include "Poison.h"

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
	int animationEnd;
	int direction;
	int count;
	int musicCount;
	enum animtion
	{
		STAND, WALK, CLIMB, DEAD
	};

public:
	Character();

	void reset();
	void clear(int &isGameClear, Stage* stage, int SH1, int SH2);
	void changeStage(Stage* stage);
	void move(Stage* stage, int map[96][20]);
	void collisionPoison(int &isGameover, Poison *poison);
	void draw(Stage* stage, int GH1, int GH2, int GH3, int SH1, int SH2);
};