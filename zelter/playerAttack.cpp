#include "stdafx.h"
#include "playerAttack.h"
#include "playerStateIdle.h"
#include "playerRun.h"
#include "playerRoll.h"
#include "player.h"



playerState * playerAttack::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))return new playerStateIdle();
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('A')) return new playerRun();
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('W')) return new playerRun();
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('S')) return new playerRun();
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('D')) return new playerRun();

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerRoll();
	return nullptr;
}

void playerAttack::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setPlayerX(player->getPlayerX() + 3);
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setPlayerX(player->getPlayerX() - 3);
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->setPlayerY(player->getPlayerY() - 3);
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setPlayerY(player->getPlayerY() + 3);
	}
	

	if (player->getGuntype() == GRENADE)
	{
		player->getPlayerBullet()->getViBullet()->power +=0.01;
	}
	
	_count++;

	if (_count % 3 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayerCurrentFrameX() + 1);

		if (player->getPlayerCurrentFrameX() >= player->getPlayerImage()->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
			player->setPlayerisEnd(true);
			_count = 0;
		}
	}
}

void playerAttack::enter(player * player)
{
	switch (player->getPlayerGuntype())
	{
	case NORMAL:
		player->getPlayerBullet()->init("bullet1", 50, WINSIZEX);
		player->getPlayerBullet()->fire(player->getPlayerGunX(), player->getPlayerGunY(),
			GetAngle(player->getPlayerX(), player->getPlayerY(), _ptMouse.x, _ptMouse.y), 10, player->getPlayerGuntype());
		break;
	case SHOTGUN:
		player->getPlayerBullet()->init("bullet1", 200, WINSIZEX);
		player->getPlayerBullet()->fire(player->getPlayerX(), player->getPlayerY(),
			RND->getFromFloatTo(GetAngle(player->getPlayerX(), player->getPlayerY(), _ptMouse.x, _ptMouse.y) + 0.15,
				GetAngle(player->getPlayerX(), player->getPlayerY(), _ptMouse.x, _ptMouse.y) - 0.15), 10, player->getPlayerGuntype());
		break;
	case HOMING:
		player->getPlayerBullet()->init("bullet1", 50, WINSIZEX);
		player->getPlayerBullet()->fire(player->getPlayerX(), player->getPlayerY(),
			GetAngle(player->getPlayerX(), player->getPlayerY(), _ptMouse.x, _ptMouse.y), 10, player->getPlayerGuntype());
		break;
	case GRENADE:
		player->getPlayerBullet()->init("bullet1", 50, WINSIZEX);
		player->getPlayerBullet()->fire(player->getPlayerX(), player->getPlayerY(),
			GetAngle(player->getPlayerX(), player->getPlayerY(), _ptMouse.x, _ptMouse.y), 10, player->getPlayerGuntype());
		break;
	case FLAMETHROWER:
		player->getPlayerBullet()->init("bullet1", 50, WINSIZEX);
		player->getPlayerBullet()->fire(player->getPlayerX(), player->getPlayerY(),
			GetAngle(player->getPlayerX(), player->getPlayerY(), _ptMouse.x, _ptMouse.y), 10, player->getPlayerGuntype());
		break;
	}
}

void playerAttack::exit(player * player)
{
}

void playerAttack::getCurrentState(player * player)
{
}
