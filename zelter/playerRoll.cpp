#include "stdafx.h"
#include "playerRoll.h"
#include "player.h"
#include "playerStateIdle.h"
#include "playerRun.h"
#include "playerDie.h"



playerState * playerRoll::inputHandle(player * player)
{
	if ( player->getPlayer().isEnd)
	{
		return new playerStateIdle;
	}
	if ( player->getPlayer().isEnd && (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D') ||
		KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S')))
	{
		return new playerRun;
	}
	if (player->getPlayer().currentHP <= 0) return new playerDie();
	return nullptr;
}

void playerRoll::update(player * player)
{
	
	
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerDirection(0);
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed * 2);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerDirection(1);
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed * 2);
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerDirection(2);
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed * 2);
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerDirection(3);
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed * 2);
	}
	if ((KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W')))
	{
		player->setPlayerDirection(4);
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed*0.015);
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed*0.015);
	}
	if ((KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W')))
	{
		player->setPlayerDirection(5);
		player->setPlayerY(player->getPlayer().y - player->getPlayer().speed*0.015);
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed*0.015);
	}
	if ((KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S')))
	{
		player->setPlayerDirection(6);
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed*0.015);
		player->setPlayerX(player->getPlayer().x + player->getPlayer().speed*0.015);
	}
	if ((KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A')))
	{
		player->setPlayerDirection(7);
		player->setPlayerY(player->getPlayer().y + player->getPlayer().speed*0.015);
		player->setPlayerX(player->getPlayer().x - player->getPlayer().speed*0.015);
	}

	
		switch (player->getPlayer().direction)
		{
		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_roll"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_roll"));
			break;
		case 2:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_back_roll"));
			break;
		case 3:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_roll"));
			break;
		case 4:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left-up_roll"));
			break;
		case 5:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right-up_roll"));
			break;
		case 6:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_roll"));
			break;
		case 7:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_roll"));
			break;
		}

	
	_count++;

	if (_count % 3 == 0)
	{
		player->setPlayerCurrentFrameX( player->getPlayer().currentFrameX + 1);

		if ( player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
			player->setPlayerisEnd(true);
			_count = 0;
		}
	}
}

void playerRoll::enter(player * player)
{
	player->setPlayerCurrentFrameX(0);
	player->setPlayerisEnd(false);
	_count = 0;
	
	return;
}

void playerRoll::exit(player * player)
{
}

void playerRoll::getCurrentState(player * player)
{
}
