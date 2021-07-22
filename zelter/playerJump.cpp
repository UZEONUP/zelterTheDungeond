#include "stdafx.h"
#include "playerJump.h"
#include "playerStateIdle.h"
#include "playerDie.h"
#include "playerHit.h"
#include "playerAttack.h"

playerState * playerJump::inputHandle(player * player)
{
	if(player->getPlayer().y >= WINSIZEY-100)return new playerStateIdle();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack();
	if (player->getPlayer().isHit == true) return new playerHit();
	if (player->getPlayer().currentHP <= 0) return new playerDie();
	return nullptr;
}

void playerJump::update(player * player)
{
	if (player->getPlayer().y < WINSIZEY - 100)
	{
		_gravity += 0.3;
		player->setPlayerY(player->getPlayer().y - _jumpPower);
		_jumpPower -= _gravity;
	}

	_count++;
	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX()) player->setPlayerCurrentFrameX(0);
		_count = 0;
	}
}

void playerJump::enter(player * player)
{
	if (player->getPlayer().direction == 0) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_jump"));
	if (player->getPlayer().direction == 1) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_jump"));
}

void playerJump::exit(player * player)
{
}

void playerJump::getCurrentState(player * player)
{
}
