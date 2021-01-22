#include "Character.h"

Character::Character()
{
	posX = 1184;
	posY = 608;
	upCount = 0;
	point = 0;
	isMove = 0;
	isClimb = 0;
	isDead = 0;
	isAnimation = 0;
	animationCount = 0;
	animationPoint = 0;
	direction = 1;
	count = 0;
}

void Character::reset()
{
	posX = 1184;
	posY = 608;
	upCount = 0;
	point = 0;
	isMove = 0;
	isClimb = 0;
	isDead = 0;
	isAnimation = 0;
	animationCount = 0;
	animationPoint = 0;
	direction = 1;
	count = 0;
}

void Character::clear(int& isGameClear, Stage* stage)
{
	if (stage->getStageStart() == 0 && posY <= -96)
	{
		isGameClear = 1;
	}
}

void Character::changeStage(Stage* stage)
{
	if (stage->getIsChangeStage() == 1)
	{
		posY += 37;
		if (posY > 608)
		{
			posY = 608;
			isAnimation = STAND;
		}
	}
}

void Character::move(Stage* stage, int map[96][20])
{
	if (isDead == 0 && stage->getIsChangeStage() == 0)
	{
		if (isClimb == 0)
		{
			if (isMove == 0)
			{
				for (int j = 0; j < 20; j++)
				{
					if (map[((posY - stage->getStageStart()) / 64 + 2)][j] == 3)
					{
						point = (j + 1) - (posX / 64);
						isMove = 2;
						isAnimation = WALK;
						break;
					}
				}
				for (int i = 0; i < 20; i++)
				{
					if (map[(posY - stage->getStageStart()) / 64][i] == 2)
					{
						point = i - (posX / 64);
						point = posX + point * 64;
						isMove = 1;
						isAnimation = WALK;
						break;
					}
				}
			}
			if (isMove == 1)
			{
				if (point < posX)
				{
					posX -= 6;
					direction = 1;
					if (point > posX)
					{
						posX = point;
					}
					if (posX == point)
					{
						isMove = 0;
						isClimb = 1;
					}
				}
				if (point > posX)
				{
					direction = 0;
					posX += 6;
					if (point < posX)
					{
						posX = point;
					}
					if (posX == point)
					{
						isMove = 0;
						isClimb = 1;
					}
				}
			}
			if (isMove == 2)
			{
				if (point > 0)
				{
					direction = 0;
					posX = posX + 6;
					if (map[((posY - stage->getStageStart()) / 64) + 2][((posX - 32) / 64) + 1] == 0)
					{
						posX = (posX / 64) * 64 + 32;
						isAnimation = STAND;
						isMove = 0;
					}
					if (map[((posY - stage->getStageStart()) / 64) + 2][(posX / 64) - 1] == 3)
					{
						map[((posY - stage->getStageStart()) / 64) + 2][(posX / 64) - 1] = 0;
					}
					if (posX > 1184)
					{
						posX = 1184;
						isMove = 0;
						isAnimation = STAND;
					}
				}
				if (point < 0)
				{
					direction = 1;
					posX = posX - 6;
					if (map[((posY - stage->getStageStart()) / 64) + 2][((posX + 32) / 64) - 1] == 0)
					{
						posX = ((posX / 64) - 1 * 64 + 32);
						isAnimation = STAND;
						isMove = 0;
					}
					if (map[((posY - stage->getStageStart()) / 64) + 2][(posX / 64) + 1] == 3)
					{
						map[((posY - stage->getStageStart()) / 64) + 2][(posX / 64) + 1] = 0;
					}
					if (posX < 96)
					{
						posX = 96;
						isMove = 0;
						isAnimation = STAND;
					}
				}
			}
		}

		if (isClimb == 1)
		{
			isAnimation = CLIMB;
			upCount++;
			if (upCount > 48)
			{
				isClimb = 0;
				upCount = 0;
				isAnimation = STAND;
				if (posY <= -160)
				{
					stage->setIsChangeStage(1);
				}
			}
		}
		if (isClimb == 1)
		{
			posY -= 4;
		}
	}
}

void Character::collisionPoison(int& gameOver)
{
	if (isDead == 1)
	{
		isAnimation = 4;
	}
}

void Character::draw(Stage* stage, int GH1, int GH2)
{
	if (isAnimation == STAND)
	{
		if (direction == 0)
		{
			DrawGraph(posX - 32, posY - 32, GH1, 1);
		}
		if (direction == 1)
		{
			DrawTurnGraph(posX - 32, posY - 32, GH1, 1);
		}
	}
	if (isAnimation == WALK)
	{
		if (direction == 0)
		{
			if (animationCount >= 1)
			{
				animationCount = 0;
				animationPoint++;
				if (animationPoint >= 7)
				{
					animationPoint = 0;
				}
			}
			DrawRectGraph(posX - 32, posY - 32, animationPoint * 64, 0, 64, 128, GH2, 1, 0);
			animationCount++;
		}
		if (direction == 1)
		{
			if (animationCount >= 1)
			{
				animationCount = 0;
				animationPoint++;
				if (animationPoint >= 7)
				{
					animationPoint = 0;
				}
			}
			DrawRectGraph(posX - 32, posY - 32, animationPoint * 64, 0, 64, 128, GH2, 1, 1);
			animationCount++;
		}
	}
	if (isAnimation == CLIMB)
	{
		DrawBox(posX - 32, posY - 32, posX + 32, posY + 96, GetColor(0, 180, 100), 1);
		DrawBox(posX - 32, posY - 32, posX + 32, posY + 96, GetColor(255, 255, 255), 0);
	}
	if (isAnimation == DEAD)
	{
		DrawBox(posX - 32, posY - 32, posX + 32, posY + 96, GetColor(0, 180, 100), 1);
		DrawBox(posX - 32, posY - 32, posX + 32, posY + 96, GetColor(255, 255, 255), 0);
	}
}