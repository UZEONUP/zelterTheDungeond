#include "stdafx.h"
#include "niflheimBattle.h"

HRESULT niflheimBattle::init()
{
	IMAGEMANAGER->addImage("niflheimBackGround", L"niflheim/niflheimBackGround.png");
	_backGround = IMAGEMANAGER->findImage("niflheimBackGround");

	_niflheimMap = new niflheimMap;
	_niflheimMap->init();
	CAMERAMANAGER->setX(0);
	CAMERAMANAGER->setY(0);

	_player = new player;
	_player->init();
	_player->setKeyType(true);

	_niflheim = new niflheim;
	_niflheim->init();

	_player->linkNiflheimMap(_niflheimMap);
	_player->linkNiflheim(_niflheim);
	_niflheim->linkPlayer(_player);

	return S_OK;
}

void niflheimBattle::release()
{
	
}

void niflheimBattle::update()
{
	_player->setKeyType(true);

	_niflheimMap->update();
	_niflheim->update();
	_player->update();
}

void niflheimBattle::render()
{
	_backGround->render(0, 0);

	_niflheimMap->render();
	_niflheim->render();
	_player->render();
}
