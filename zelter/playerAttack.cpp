#include "stdafx.h"
#include "playerAttack.h"
#include "playerStateIdle.h"
#include "playerRun.h"
#include "playerRoll.h"
#include "playerDie.h"


playerState * playerAttack::inputHandle(player * player)
{

	
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (player->getPlayerGuntype() == GRENADE)
			{
				player->getPlayerBullet()->fire(player->getPlayerGunX(), player->getPlayerGunY(),
					GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y), 20.0f, player->getPlayerGuntype(), _pressPower);
			}

			return new playerStateIdle();
		}
	
		if (player->getPlayer().isDunGreed)
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('A')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('D')) return new playerRun();
		}
		else
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('A')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('D')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('W')) return new playerRun();
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('S')) return new playerRun();
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerRoll();
		}

		if (player->getPlayer().currentHP <= 0) return new playerDie();
	
	return nullptr;
}

void playerAttack::update(player * player)
{
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();

	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
	if (player->getPlayer().isDunGreed)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->setPlayerX(player->getPlayer().x + 3);
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->setPlayerX(player->getPlayer().x - 3);
		}
		switch (player->getPlayer().direction)
		{

		case 0:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_right_idle"));
			break;
		case 1:
			player->setPlayerImage(IMAGEMANAGER->findImage("gunner_left_idle"));
			break;
		}
	}
	
	else
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->setPlayerX(player->getPlayer().x + 3);
		}

		if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->setPlayerX(player->getPlayer().x - 3);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			player->setPlayerY(player->getPlayer().y - 3);
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			player->setPlayerY(player->getPlayer().y + 3);
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
	
	if (player->getPlayerGuntype() == FLAMETHROWER)
	{
		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			RND->getFromFloatTo(GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) + 0.15,
				GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) - 0.15), 10, player->getPlayerGuntype(), 0);
	}

	

	_count++;
	if (_count % 5 == 0)
	{
		if(player->getPlayerGuntype() == GRENADE)_pressPower += 0.5;
		cout << _pressPower << endl;
		
		player->setPlayerCurrentFrameX( player->getPlayer().currentFrameX + 1);
	
		if ( player->getPlayer().currentFrameX >= player->getPlayer().img->getMaxFrameX())
		{
			player->setPlayerCurrentFrameX(0);
			player->setPlayerisEnd(true);
			_count = 0;
		}
	}
}

void playerAttack::enter(player * player)
{
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
	_pressPower = 0;

	switch (player->getPlayerGuntype())
	{
	case NORMAL:
		
		player->getPlayerBullet()->fire(player->getPlayerGunX(), player->getPlayerGunY(),
			GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y), 10, player->getPlayerGuntype(),0);
		break;
	case SHOTGUN:
		
		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			RND->getFromFloatTo(GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) + 0.15,
				GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) - 0.15), 10, player->getPlayerGuntype(),0);
		break;
	case HOMING:
		
		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y), 10, player->getPlayerGuntype(),0);
		break;
	case GRENADE:
		
		break;
	case FLAMETHROWER:
		player->getPlayerBullet()->fire(player->getPlayer().x, player->getPlayer().y,
			RND->getFromFloatTo(GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) + 0.15,
				GetAngle(player->getPlayer().x, player->getPlayer().y, _mapMouse.x, _mapMouse.y) - 0.15), 10, player->getPlayerGuntype(),0);
		break;
	}
}

void playerAttack::exit(player * player)
{
}

void playerAttack::getCurrentState(player * player)
{
}
