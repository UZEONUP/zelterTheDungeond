#include "stdafx.h"
#include "inGame.h"
//
//HRESULT inGame::init()
//{
//	IMAGEMANAGER->addFrameImage("openWorld", L"tileImg/오픈월드.png", 20, 9);
//	CAMERAMANAGER->setMapCamera(BACKGROUNDX * 2, BACKGROUNDY * 2);
//
//	load();
//	for (int i = 0; i < TILEX*TILEY; i++)
//	{
//		_tile[i].sizeX = TILESIZEX;
//		_tile[i].sizeY = TILESIZEY;
//		_tile[i].rc.left *= 2;
//		_tile[i].rc.top *= 2;
//		_tile[i].rc.right *= 2;
//		_tile[i].rc.bottom *= 2;
//	}
//	return S_OK;
//}
//
//void inGame::release()
//{
//
//}
//
//void inGame::update()
//{
//	CAMERAMANAGER->updateCamera(_ptMouse, _mapMouse, 10);
//	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
//	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();
//	/*cout << _mapMouse.x << endl;
//	cout << _mapMouse.y << endl;*/
//
//}
//
//void inGame::render()
//{
//	//지형 그리기
//	for (int i = 0; i < TILEX * TILEY; ++i)
//	{
//		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
//			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
//			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
//			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
//		{
//
//			IMAGEMANAGER->findImage("openWorld")->cutRender(
//				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
//				_tile[i].terrainX, _tile[i].terrainY,
//				_tile[i].sizeX, _tile[i].sizeY
//			);
//		}
//
//	}
//
//	//오브젝트 그리기
//	for (int i = 0; i < TILEX * TILEY; ++i)
//	{
//		if (_tile[i].object == OBJ_NONE)continue;
//
//		if (0 <= _tile[i].rc.right - CAMERAMANAGER->getX() &&
//			_tile[i].rc.left - CAMERAMANAGER->getX() <= WINSIZEX &&
//			0 <= _tile[i].rc.bottom - CAMERAMANAGER->getY() &&
//			_tile[i].rc.top - CAMERAMANAGER->getY() <= WINSIZEY)
//		{
//
//			IMAGEMANAGER->findImage("openWorld")->cutRender(
//				_tile[i].rc.left - CAMERAMANAGER->getX(), _tile[i].rc.top - CAMERAMANAGER->getY(),
//				_tile[i].objX, _tile[i].objY,
//				_tile[i].sizeX, _tile[i].sizeY
//			);
//		}
//	}
//}
//
//void inGame::load()
//{
//	HANDLE file;
//	DWORD read;
//
//	file = CreateFile("openWorld", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//
//	ReadFile(file, _tile, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
//	//ReadFile(file, _pos, sizeof(int)*2, &read, NULL);
//
//	////타일을 불러온 다음 타일이 어떤 지형인지 오브젝트인지 분별
//	////해당 타일에 속성 부여
//
//	//for (int i = 0; i < TILEX*TILEY; ++i)
//	//{
//	//	if (_tile[i].colChk == true)_attribute[i] |= ATTR_UNMOVE;
//	//}
//
//	CloseHandle(file);
//
//}
