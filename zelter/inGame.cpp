#include "stdafx.h"
#include "inGame.h"


HRESULT inGame::init()
{
	_inGameMap = new inGameMap;
	_inGameMap->init();

	_player = new player;
	_player->init();

	_player->setKeyType(false);
	cout << _player->getPlayer().isDunGreed << endl;
	_player->linkOpenWorldMap(_inGameMap);

	return S_OK;
}

void inGame::release()
{
}

void inGame::update()
{
	CAMERAMANAGER->updateCameraH(_player->getRect(),0.2,0.8);

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (IsCollision(_player->getRect(), _inGameMap->getTile()[i].checkRect))
		{
			cout<<"�߿쵿"	<<endl;
		}
	}
	_inGameMap->update();
	_player->update();
	cout << _player->getPlayer().x << endl;
	cout << _player->getPlayer().y << endl;
}

void inGame::render()
{
	_inGameMap->render();
	_player->render();
}
