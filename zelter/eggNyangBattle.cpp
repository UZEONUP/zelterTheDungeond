#include "stdafx.h"
#include "eggNyangBattle.h"

HRESULT eggNyangBattle::init()
{
	IMAGEMANAGER->addImage("eggNyangBackGround", L"eggNyang/eggNyangBackGround.png");
	_backGround = IMAGEMANAGER->findImage("eggNyangBackGround");
	
	_eggNyangMap = new eggNyangMap;
	_eggNyangMap->init();
	_eggNyang = new eggNyang;
	_eggNyang->init();
	_player = new player;
	_player->init();

	_eggNyang->linkPlayer(_player);
	_player->linkEggNyang(_eggNyang);

	return S_OK;
}

void eggNyangBattle::release()
{
}

void eggNyangBattle::update()
{
	_eggNyangMap->update();
	_eggNyang->update();
	_player->update();
}

void eggNyangBattle::render()
{
	_backGround->render(0, 0);

	_eggNyangMap->render();
	_eggNyang->render();
	_player->render();
}
