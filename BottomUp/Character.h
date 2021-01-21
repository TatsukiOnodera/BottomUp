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
	int isAnimationEnd;
	int animationSpeed;
	int count;
	int next;
	enum animtion
	{
		STAND, WALK, CLIMB, DEAD
	};

public:
	Character();

	int getIsDead();
	int getNext();

	void changeStage(Stage* stage);
	void move(Stage* stage, int map[96][20]);
	void collisionPoison();
	void draw(Stage* stage, int GH1);
};