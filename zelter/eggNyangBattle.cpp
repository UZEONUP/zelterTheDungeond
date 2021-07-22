#include "stdafx.h"
#include "eggNyangBattle.h"

HRESULT eggNyangBattle::init()
{
	_eggNyang = new eggNyang;
	_eggNyang->init();
	_player = new player;
	_eggNyang->init();

	_player->linkEggNyang(_eggNyang);
	_eggNyang->linkPlayer(_player);

	return S_OK;
}

void eggNyangBattle::release()
{
}

void eggNyangBattle::update()
{
	_eggNyang->update();
	_player->update();
}

void eggNyangBattle::render()
{
	_eggNyang->render();
	_player->render();
}
