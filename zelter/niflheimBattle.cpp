#include "stdafx.h"
#include "niflheimBattle.h"

HRESULT niflheimBattle::init()
{
	_niflheimMap = new niflheimMap;
	_niflheimMap->init();

	_player = new player;
	_player->init();
	_player->setKeyType(true);

	_niflheim = new niflheim;
	_niflheim->init();

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
	_niflheimMap->render();
	_niflheim->render();
	_player->render();
}
