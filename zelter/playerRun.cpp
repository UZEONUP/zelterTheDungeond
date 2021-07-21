#include "stdafx.h"
#include "playerRun.h"

#include "player.h"
#include "playerStateIdle.h"
#include "playerHit.h"
#include "playerJump.h"
#include "playerDonwJump.h"
#include "playerRoll.h"
#include "playerAttack.h"
#include "playerDie.h"


playerState * playerRun::inputHandle(player * player)
{

	if (player->getPlayer().isDunGreed == true)
	{
		if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) return new playerStateIdle;
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))return new playerJump;
	}
	else
	{
		if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D') ||
			KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S')) return new playerStateIdle;

		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerRoll;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack;
	if (player->getPlayer().currentHP <= 0) return new playerDie();
	return nullptr;
}

void playerRun::update(player * player)
{
	if (player->getPlayer().isDunGreed)
	{
		if (KEYMANAGER->isStayKeyDown('D'))player->setPlayerX(player->getPlayer().x + player->getPlayer().speed);
		if (KEYMANAGER->isStayKeyDown('A'))player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);

		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
			break;
		}

	}
	else
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->setPlayerX(player->getPlayer().x + player->getPlayer().speed);
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->setPlayerX(player->getPlayer().x - player->getPlayer().speed);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			player->setPlayerY(player->getPlayer().y - player->getPlayer().speed);
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			player->setPlayerY(player->getPlayer().y + player->getPlayer().speed);
		}

		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
			break;
		case 2:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_back_run"));
			break;
		case 3:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_run"));
			break;
		case 4:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left-up_run"));
			break;
		case 5:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right-up_run"));
			break;
		case 6:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_run"));
			break;
		case 7:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_run"));
			break;
		}
	}
	
	_count++;
	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX( player->getPlayer().currentFrameX + 1);
		if ( player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX()) player->setPlayerCurrentFrameX(0);
		_count = 0;
	}
	return;
}

void playerRun::enter(player * player)
{
	player->setPlayerCurrentFrameX(0);
	_count = 0;
	
	return;
}

void playerRun::exit(player * player)
{
}

void playerRun::getCurrentPlayerState(player * player)
{
}
