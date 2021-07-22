#include "stdafx.h"
#include "niflheimBattle.h"

HRESULT niflheimBattle::init()
{
	_player = new player;
	_player->init();
	_niflheim = new niflheim;
	_niflheim->init();

	_player->linkNiflHeim(_niflheim);
	_niflheim->linkPlayer(_player);

	return S_OK;
}

void niflheimBattle::release()
{
	
}

void niflheimBattle::update()
{
	_niflheim->update();
	_player->update();
}

void niflheimBattle::render()
{
	_niflheim->render();
	_player->render();
}
