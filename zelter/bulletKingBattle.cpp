#include "stdafx.h"
#include "bulletKingBattle.h"

bulletKingBattle::bulletKingBattle()
{
}

bulletKingBattle::~bulletKingBattle()
{
}

HRESULT bulletKingBattle::init()
{
	_bulletKingMap = new bulletKingMap;
	_bulletKingMap->init();

	_bulletKing = new bulletKing;
	_bulletKing->init();
	_player = new player;
	_player->init();
	_player->setKeyType(false);

	
	_player->linkBulletKing(_bulletKing);
	_bulletKing->linkPlayer(_player);

	return S_OK;
}

void bulletKingBattle::release()
{
}

void bulletKingBattle::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_bulletKing->update();

	_player->update();

	_bulletKingMap->update();
}

void bulletKingBattle::render()
{
	_bulletKingMap->render();
	_player->render();
	_bulletKing->render();

}
