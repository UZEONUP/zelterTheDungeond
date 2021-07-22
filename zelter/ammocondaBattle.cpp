#include "stdafx.h"
#include "ammocondaBattle.h"
#include "player.h"

ammocondaBattle::ammocondaBattle()
{
}

ammocondaBattle::~ammocondaBattle()
{
}

HRESULT ammocondaBattle::init()
{
	_ammoconda = new ammoconda;
	_ammoconda->init();

	_player = new player;
	_player->init();

	_player->linkAmmoconda(_ammoconda);
	_ammoconda->linkPlayer(_player);
	return S_OK;
}

void ammocondaBattle::release()
{
}

void ammocondaBattle::update()
{
	_ammoconda->update();
	_player->update();
}

void ammocondaBattle::render()
{
	_ammoconda->render();
	_player->render();
}
