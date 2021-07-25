#include "stdafx.h"
#include "inGame.h"


HRESULT inGame::init()
{
	
	_inGameMap->init();

	_player = new player;
	_player->init();

	_player->setKeyType(false);
	_player->linkOpenWorldMap(_inGameMap);
	_player->linkNiflheimMap(_niflheimMap);


	return S_OK;
}

void inGame::release()
{
}

void inGame::update()
{
	_player->setKeyType(false);
	CAMERAMANAGER->updateCamera(_player->getPlayer().x, _player->getPlayer().y);
	CAMERAMANAGER->updateCamera(_ptMouse, _mapMouse, _player->getPlayer().x, _player->getPlayer().y);
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	_inGameMap->update();
	_player->update();

	collisionDoor();


	
	
}

void inGame::render()
{

	_inGameMap->render();
	_player->render();

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_inGameMap->getTile()[i].object == OBJ_NONE)continue;

		if (0 <= _inGameMap->getTile()[i].rc.right - CAMERAMANAGER->getX() &&
			_inGameMap->getTile()[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _inGameMap->getTile()[i].rc.bottom - CAMERAMANAGER->getY() &&
			_inGameMap->getTile()[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{
			/*if (_player->getPlayer().rc.bottom > _inGameMap->getTile()[i].checkRect.bottom)
			{*/
			IMAGEMANAGER->findImage("openWorld")->cutRender(
				_inGameMap->getTile()[i].rc.left - CAMERAMANAGER->getX(), _inGameMap->getTile()[i].rc.top - CAMERAMANAGER->getY(),
				_inGameMap->getTile()[i].objX, _inGameMap->getTile()[i].objY,
				_inGameMap->getTile()[i].sizeX, _inGameMap->getTile()[i].sizeY
			);
			//}
		}
		D2DRENDER->DrawRectangle(_inGameMap->getTile()[i].checkRect, D2DDEFAULTBRUSH::Red);
	}

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


