#include "stdafx.h"
#include "playerDonwJump.h"

playerState * playerDonwJump::inputHandle(player * player)
{
	if (player->getPlayer().y >= WINSIZEY - 100)return new playerStateIdle;

	return nullptr;
}

void playerDonwJump::update(player * player)
{
	if (player->getPlayer().y < WINSIZEY - 100) player->setPlayerY(player->getPlayer().y + _jumpPower);
	

	_count++;

	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayer().currentFrameX + 1);
		if (player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX()) player->setPlayerCurrentFrameX(0);
		_count = 0;
	}
}

void playerDonwJump::enter(player * player)
{
	if (player->getPlayer().direction == 0) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_downjump"));
	if (player->getPlayer().direction == 1) player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_downjump"));
}

void playerDonwJump::exit(player * player)
{
}

void playerDonwJump::getCurrentState(player * player)
{
}
