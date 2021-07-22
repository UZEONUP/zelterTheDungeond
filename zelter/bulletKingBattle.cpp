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
	_bulletKing = new bulletKing;
	_bulletKing->init();
	_fishMan = new fishMan;
	_dinosaur = new dinosaur;
	
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
	_fishMan->fishMove(_bulletKing->getEnemyTest().x, _bulletKing->getEnemyTest().y);

	_dinosaur->setEnemy(RND->getFromIntTo(600, 1200), RND->getFromIntTo(0, 600));
	_dinosaur->dinoState();
	_dinosaur->dinoMove(_bulletKing->getEnemyTest().x, _bulletKing->getEnemyTest().y);

}

void bulletKingBattle::render()
{
	_bulletKing->render();
	_fishMan->render();
	_dinosaur->render();
}
