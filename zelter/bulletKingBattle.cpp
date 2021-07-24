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

	_fishMan = new fishMan;
	_fishMan->init();
	_dinosaur = new dinosaur;
	_dinosaur->init();
	
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
	CAMERAMANAGER->updateCamera(_ptMouse, _mapMouse, _player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_bulletKing->update();

	_fishMan->setEnemy(RND->getFromIntTo(0, 600), RND->getFromIntTo(0, 600));
	_fishMan->fishState();
	_fishMan->fishMove(_player->getPlayer().x, _player->getPlayer().y);

	_dinosaur->setEnemy(RND->getFromIntTo(600, 1200), RND->getFromIntTo(0, 600));
	_dinosaur->dinoState();
	_dinosaur->dinoMove(_player->getPlayer().x, _player->getPlayer().y);

	_player->update();

	_bulletKingMap->update();
}

void bulletKingBattle::render()
{
	_bulletKingMap->render();

	_fishMan->render();
	_dinosaur->render();
	_player->render();
	_bulletKing->render();

}
