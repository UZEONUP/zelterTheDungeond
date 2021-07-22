#include "stdafx.h"
#include "inGameMap.h"

HRESULT inGameMap::init()
{
	IMAGEMANAGER->addFrameImage("openWorld", L"tileImg/오픈월드.png", 20, 9);
	CAMERAMANAGER->setMapCamera(BACKGROUNDX * 2, BACKGROUNDY * 2);

	load();

	return S_OK;
}

void inGameMap::release()
{

}

void inGameMap::update()
{
	//_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	//_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
	/*cout << _mapMouse.x << endl;
	cout << _mapMouse.y << endl;*/

}

void inGameMap::render()
{
	//지형 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{

			IMAGEMANAGER->findImage("openWorld")->cutRender(
				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
				_tile[i].terrainX, _tile[i].terrainY,
				_tile[i].sizeX, _tile[i].sizeY
			);
		}

	}

	//오브젝트 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tile[i].object == OBJ_NONE)continue;

		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
		{

			IMAGEMANAGER->findImage("openWorld")->cutRender(
				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
				_tile[i].objX, _tile[i].objY,
				_tile[i].sizeX, _tile[i].sizeY
			);
		}
		D2DRENDER->DrawRectangle(_tile[i].checkRect, D2DDEFAULTBRUSH::Red);
	}
}

void inGameMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("openWorld.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	//ReadFile(file, _pos, sizeof(int)*2, &read, NULL);

	////타일을 불러온 다음 타일이 어떤 지형인지 오브젝트인지 분별
	////해당 타일에 속성 부여

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		//오브젝트(체크렉트)가 있을 경우 못가게 속성부여
		if (_tile[i].object == (BLOCK || BLOCK_LHALF ||
			BLOCK_RHALF || BLOCK_LTRIPLE || BLOCK_RTRIPLE))
			_attribute[i] = ATTR_UNMOVE;
	}

	CloseHandle(file);

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		_tile[i].sizeX = TILESIZEX * 2;
		_tile[i].sizeY = TILESIZEY * 2;
		_tile[i].rc.left *= 2;
		_tile[i].rc.top *= 2;
		_tile[i].rc.right *= 2;
		_tile[i].rc.bottom *= 2;
		_tile[i].checkRect.left *= 2;
		_tile[i].checkRect.top *= 2;
		_tile[i].checkRect.right *= 2;
		_tile[i].checkRect.bottom *= 2;
	}
}
