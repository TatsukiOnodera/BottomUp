#include "Poison.h"
#include "Dxlib.h"

Poison::Poison()
{
	posY = 768;
	collisionY = 768;
	count = 0;
	animationNumber = 0;
	animationCount = 0;
}

int Poison::getCollisionY() { return collisionY; }

void Poison::reset()
{
	posY = 768;
	collisionY = 768;
	count = 0;
	animationNumber = 0;
	animationCount = 0;
}

void Poison::move(Stage *stage)
{
	if (count >= (stage->getFloor() / 2))
	{
		if (stage->getFloor() == 8)
		{
			posY = posY - 1;
			collisionY = collisionY - 1;
			count = 0;
		}
		else
		{
			posY = posY - 2;
			collisionY = collisionY - 2;
			count = 0;
		}
	}
	count++;
	if (stage->getIsChangeStage() == 1)
	{
		collisionY = posY + 20 + 5376 + stage->getStageStart();
	}
}

void Poison::draw(Stage* stage, int GH1)
{
	if (animationCount >= 10)
	{
		animationCount = 0;
		animationNumber++;
		if (animationNumber >= 6)
		{
			animationNumber = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
	DrawRectGraph(0, posY + 5376 + stage->getStageStart(), animationNumber * 1280, 0, 1280, 768, GH1, 1, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
	animationCount++;
}
