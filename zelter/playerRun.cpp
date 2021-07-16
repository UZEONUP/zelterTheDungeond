#include "stdafx.h"
#include "playerRun.h"

#include "player.h"
#include "playerStateIdle.h"
#include "playerHit.h"
#include "playerJump.h"
#include "playerRoll.h"
#include "playerAttack.h"


playerState * playerRun::inputHandle(player * player)
{
	

	


	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')||
		KEYMANAGER->isOnceKeyUp('W')||KEYMANAGER->isOnceKeyUp('S')) return new playerStateIdle;
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) return new playerRoll;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) return new playerAttack;
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))return new playerJump;

	return nullptr;
}

void playerRun::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//player->setPlayerDirection(0); // 오른쪽
		player->setPlayerX(player->getPlayerX() + player->getPlayerSpeed());
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//player->setPlayerDirection(1); //왼쪽
		player->setPlayerX(player->getPlayerX() - player->getPlayerSpeed());
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//player->setPlayerDirection(2);//위쪽
		player->setPlayerY(player->getPlayerY() - player->getPlayerSpeed());
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//player->setPlayerDirection(3);//아래쪽	
		player->setPlayerY(player->getPlayerY() + player->getPlayerSpeed());
	}
	
	//if (KEYMANAGER->isStayKeyDown('A') && KEYMANAGER->isStayKeyDown('W'))
	//{
	//	player->setPlayerDirection(4);//좌상대각선
	//}
	//if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('W'))
	//{
	//	player->setPlayerDirection(5);//우상대각선
	//}
	//if (KEYMANAGER->isStayKeyDown('D') && KEYMANAGER->isStayKeyDown('S'))
	//{
	//	player->setPlayerDirection(6);//우하대각선
	//}
	//if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A'))
	//{
	//	player->setPlayerDirection(7);//좌하대각선
	//}

	switch (player->getPlayerDirection())
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

	_count++;

	if (_count % 7 == 0)
	{
		player->setPlayerCurrentFrameX(player->getPlayerCurrentFrameX() + 1);
		if (player->getPlayerCurrentFrameX() >= player->getPlayerImage()->getMaxFrameX()) player->setPlayerCurrentFrameX(0);
		_count = 0;
	}
	return;

}

void playerRun::enter(player * player)
{
	
	/*switch (player->getPlayerDirection())
	{
	case 0:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_right_run"));
		break;
	case 1:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_left_run"));
		break;
	case 2:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_back_run"));
		break;
	case 3:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_run"));
		break;
	case 4:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_left-up_run"));
		break;
	case 5:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_right-up_run"));
		break;
	case 6:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_right_run"));
		break;
	case 7:
		player->setPlayerImage(IMAGEMANAGER->FindImage("gunner_left_run"));
		break;
	}*/

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
