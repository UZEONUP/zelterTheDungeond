#include "stdafx.h"
#include "bulletKingAttack2.h"


bulletKingState * bulletKingAttack2::InputHandle(bulletKing * bulletKing)
{
	if (_count >= 25) return new bulletKingIdle();
	return nullptr;
}

void bulletKingAttack2::enter(bulletKing * bulletKing)
{
	bulletKing->setBulletKingImg(IMAGEMANAGER->findImage("bulletKingAttack2"));
	bulletKing->setBulletKingIsAttack3(false);
	bulletKing->setBulletKingCurrentFrameX(0);

	//�Ѿ� �߻�1
	bulletKing->getBulletKingBullet()->bulletFire2(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y, bulletKing->getEnemyTest().x, bulletKing->getEnemyTest().y);
	_count = 0;
}

void bulletKingAttack2::update(bulletKing * bulletKing)
{
	_count++;
	if (_count % 15 == 0)
	{		
		//�Ѿ� �߻�2
		bulletKing->getBulletKingBullet()->bulletFire2(bulletKing->getBulletKing().x, bulletKing->getBulletKing().y, bulletKing->getEnemyTest().x, bulletKing->getEnemyTest().y);
		
		bulletKing->setBulletKingCurrentFrameX(bulletKing->getBulletKing().currentFrameX + 1);
		if (bulletKing->getBulletKing().currentFrameX >= bulletKing->getBulletKing().img->getMaxFrameX()) bulletKing->setBulletKingCurrentFrameX(0);
	}
}

void bulletKingAttack2::render(bulletKing * bulletKing)
{
}

void bulletKingAttack2::exit(bulletKing * bulletKing)
{
}