#include "stdafx.h"
#include "inGame.h"


HRESULT inGame::init()
{
	_inGameMap = new inGameMap;
	_inGameMap->init();

	_player = new player;
	_player->init();

	_player->setKeyType(false);
	cout << _player->getPlayer().isDunGreed <<"tlqkkdjfas;lfjioajfe;kasndf;saji"<< endl;
	_player->linkOpenWorldMap(_inGameMap);
	
	return S_OK;
}

void inGame::release()
{
}

void inGame::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	CAMERAMANAGER->updateCamera(_ptMouse, _mapMouse,_player->getPlayer().x,_player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	//CAMERAMANAGER->updateCameraW(_player->getRect(),_player->getPlayer().x, _player->getPlayer().y,0.1,0.9);

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (IsCollision(_player->getRect(), _inGameMap->getTile()[i].checkRect))
		{
			cout<<"�߿쵿"	<<endl;
		}
	}
	_inGameMap->update();
	_player->update();

	collisionDoor();


}

void inGame::render()
{
	_inGameMap->render();
	_player->render();
	
}

void inGame::collisionDoor()
{
	for (int i = 0; i < 4; i++)
	{
		if(IsCollision(_inGameMap->getBossDoor(i).rc, _player->getPlayer().rc)) 
		{
			switch (i)
			{
			case 0:
				SCENEMANAGER->changeScene("eggNyang");
				break;
			case 1:
				SCENEMANAGER->changeScene("niflheim");
				break;
			case 2:
				SCENEMANAGER->changeScene("bulletKing");
				break;
			case 3:
				SCENEMANAGER->changeScene("ammoconda");
				break;
			}
		}
	}
}


