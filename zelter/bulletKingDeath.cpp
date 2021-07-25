#include "stdafx.h"
#include "bulletKingDeath.h"

bulletKingState * bulletKingDeath::InputHandle(bulletKing * bulletKing)
{
	return nullptr;
}

void bulletKingDeath::enter(bulletKing * bulletKing)
{
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingDeath"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);

	_count = 0;

	SOUNDMANAGER->stop("bulletKingBGM");
}

void bulletKingDeath::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 10 == 0)
	{
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		bulletKing->setBulletKingChairCurrentFrameX(1);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
		_count = 0;
	}
}

void bulletKingDeath::render(bulletKing * bulletKing)
{
}

void bulletKingDeath::exit(bulletKing * bulletKing)
{
}
