#include "stdafx.h"
#include "inGameMap.h"

HRESULT inGameMap::init()
{
	IMAGEMANAGER->addFrameImage("openWorld", L"tileImg/���¿���.png", 20, 9);
	CAMERAMANAGER->setMapCamera(BACKGROUNDX * 2, BACKGROUNDY * 2);


	load();

	setDoor();

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
	cout << _tile[0].rc.left << endl;


}

void inGameMap::render()
{
	//���� �׸���
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

	//������Ʈ �׸���
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
	//���� ���Թ� ����
	for (int i = 0; i < 4; i++)
	{
		_bossDoorRect[i].img->render(_bossDoorRect[i].rc.left - CAMERAMANAGER->getX(), _bossDoorRect[i].rc.top - CAMERAMANAGER->getY());
	}
}

void inGameMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("openWorld.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	memset(_pos, 0, sizeof(int) * 2);

	////Ÿ���� �ҷ��� ���� Ÿ���� � �������� ������Ʈ���� �к�
	////�ش� Ÿ�Ͽ� �Ӽ� �ο�

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		//������Ʈ(üũ��Ʈ)�� ���� ��� ������ �Ӽ��ο�
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

void inGameMap::setDoor()
{
	IMAGEMANAGER->addImage("eggNyngDoor", L"UI/���׳ɵ���.png");
	IMAGEMANAGER->addImage("niflheimDoor", L"UI/�������ӵ���.png");
	IMAGEMANAGER->addImage("bulletKingDoor", L"UI/��źŷ����.png");
	IMAGEMANAGER->addImage("ammocondaDoor", L"UI/�Ƹ��ܴٵ���.png");

	_bossDoorRect[0].img = IMAGEMANAGER->findImage("eggNyngDoor");
	_bossDoorRect[1].img = IMAGEMANAGER->findImage("niflheimDoor");
	_bossDoorRect[2].img = IMAGEMANAGER->findImage("bulletKingDoor");
	_bossDoorRect[3].img = IMAGEMANAGER->findImage("ammocondaDoor");

	_bossDoorRect[0].x = BACKGROUNDX * 2 - 610;
	_bossDoorRect[0].y = 950;
	_bossDoorRect[1].x = 600;
	_bossDoorRect[1].y = 950;
	_bossDoorRect[2].x = 600;
	_bossDoorRect[2].y = BACKGROUNDY * 2 - 600;
	_bossDoorRect[3].x = BACKGROUNDX * 2 - 600;
	_bossDoorRect[3].y = BACKGROUNDY * 2 - 600;

	for (int i = 0; i < 4; i++)
	{
		_bossDoorRect[i].rc = RectMakeCenter(_bossDoorRect[i].x, _bossDoorRect[i].y, _bossDoorRect[i].img->getWidth(), _bossDoorRect[i].img->getHeight());
	}
}

