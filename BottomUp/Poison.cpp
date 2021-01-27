#include "Poison.h"
#include "Dxlib.h"

Poison::Poison()
{
	posY = 768;
	collisionY = 768;
	count = 0;
}

int Poison::getCollisionY() { return collisionY; }

void Poison::reset()
{
	posY = 768;
	collisionY = 768;
	count = 0;
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

void Poison::draw(Stage* stage)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, posY + 5376 + stage->getStageStart(), 1280, posY + 6144 + stage->getStageStart(), GetColor(255, 0, 255), 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
}
