#include "stdafx.h"
#include "eggNyangBattle.h"

HRESULT eggNyangBattle::init()
{
	SOUNDMANAGER->addSound("eggNyangBGM", "sound/에그냥 보스 배경음악.wav", true, true);

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

	SOUNDMANAGER->play("eggNyangBGM");

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
