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
	_fishMan->render();
	_dinosaur->render();
	_player->render();
	_bulletKing->render();

	_bulletKingMap->render();
}
