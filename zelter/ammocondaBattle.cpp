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
	SOUNDMANAGER->addSound("ammocondaBGM", "sound/아모콘다 보스 배경음악.wav", true, true);

	_ammocondaMap = new ammocondaMap;
	_ammocondaMap->init();

	_ammoconda = new ammoconda;
	_ammoconda->init();

	_player = new player;
	_player->init();
	
	_player->linkAmmoconda(_ammoconda);
	_ammoconda->linkPlayer(_player);

	_player->setKeyType(false);

	SOUNDMANAGER->play("ammocondaBGM");

	return S_OK;
}

void ammocondaBattle::release()
{
}

void ammocondaBattle::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_ammocondaMap->update();

	_ammoconda->update();
	_player->update();

}

void ammocondaBattle::render()
{
	_ammocondaMap->render();

	_ammoconda->render();
	_player->render();
}
