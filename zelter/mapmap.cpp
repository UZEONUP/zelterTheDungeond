#include "stdafx.h"
#include "mapmap.h"

HRESULT mapmap::init()
{
	IMAGEMANAGER->addFrameImage("sample", L"maptiles.png", SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addImage("유정", L"유정.png");
	_player.img = IMAGEMANAGER->findImage("유정");
	_player.x = WINSIZEX / 2 - 100;
	_player.y = WINSIZEY / 2;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getWidth(), _player.img->getHeight());
	cout << _player.img->getWidth() << endl;
	IMAGEMANAGER->addImage("world", L"현진.png");
	CAMERAMANAGER->setMapCamera(BACKGROUNDX, BACKGROUNDY);
	CAMERAMANAGER->setCamera(WINSIZEX, WINSIZEY);
	setup();

	return S_OK;
}

void mapmap::release()
{
}

void mapmap::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))_player.x -= 5.f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))_player.x += 5.f;
	if (KEYMANAGER->isStayKeyDown(VK_UP))_player.y -= 5.f;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))_player.y += 5.f;

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getWidth(), _player.img->getHeight());
	CAMERAMANAGER->updateCamera(_player.x, _player.y);

	tapTool();
	setMap();
	if (_tool.isOn)	dragField();
}

void mapmap::render()
{
	/*IMAGEMANAGER->findImage("world")->mapRender2(0, 0,_player.x,_player.y,WINSIZEX,WINSIZEY);
	_player.img->render(_player.x,_player.y);*/

	//맵 타일 그리기
	if (_vTile.size() != 0)
	{
		for (int i = 0; i < _vTile.size(); i++)
		{
			IMAGEMANAGER->findImage("sample")->
				cutRender(
					_vTile[i].rc.left, _vTile[i].rc.top,
					_vTile[i].terrainX, _vTile[i].terrainY,
					_vTile[i].sizeX, _vTile[i].sizeY
				);
		}
	}

	//오브젝트 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tile[i].object == NONE)continue;

		IMAGEMANAGER->findImage("sample")->
			cutRender(
				_tile[i].rc.left, _tile[i].rc.top,
				_tile[i].objX, _tile[i].objY,
				TILESIZEX, TILESIZEY
			);

	}

	//샘플 타일 그리기
	if (_tool.isOn)
	{
		D2DRENDER->FillRectangle
		(
			_tool.rc,
			D2D1COLOR::Black,
			0.7f
		);
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
		{
			IMAGEMANAGER->findImage("sample")->
				cutRender(
					_sample[i].rc.left,
					_sample[i].rc.top,
					_sample[i].frameX,
					_sample[i].frameY,
					TILESIZEX, TILESIZEY
				);
			D2DRENDER->DrawRectangle
			(
				_sample[i].rc,
				D2DDEFAULTBRUSH::White
			);
		}
		if (_dragMouse.isDrag)
		{
			D2DRENDER->DrawRectangle
			(
				_dragMouse.rc,
				D2DDEFAULTBRUSH::Red,
				1.f
			);
		}
	}

	buttonRender();

	if (_dragStart)
	{
		IMAGEMANAGER->findImage("sample")->
			cutRender(
				_ptMouse.x, _ptMouse.y,													//이미지가 찍힐 left,top
				_dragMouse.currentStartX, _dragMouse.currentStartY,						//이미지를 짜를 left,top
				(_dragMouse.currentEndX + 1 - _dragMouse.currentStartX) * TILESIZEX,	//짜른 이미지의 width
				(_dragMouse.currentEndY + 1 - _dragMouse.currentStartY) * TILESIZEY,	//짜른 이미지의 hegiht
				0.5f
			);
	}
}

void mapmap::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("saveMap.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tile, sizeof(tagTileFake)* TILEX* TILEY, &write, NULL);
	CloseHandle(file);
}

void mapmap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("saveMap.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tile, sizeof(tagTileFake)*TILEX*TILEY, &read, NULL);
	CloseHandle(file);
}

void mapmap::setup()
{
	_startX = TILEX / 2;
	_startY = TILEY / 2;
	_endX = TILEX * 3 / 2;
	_endY = TILEY * 3 / 2;

	_dragStart = false;

	_dragMouse.currentStartX = 5;
	_dragMouse.currentStartY = 0;
	_dragMouse.currentEndY = 0;
	_dragMouse.currentEndY = 0;
	_dragMouse.start.x = 0;
	_dragMouse.start.y = 0;
	_dragMouse.end.x = 0;
	_dragMouse.end.y = 0;

	_tool.rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 1000, 600);
	_tool.isOn = false;

	_message = RectMake(_tool.rc.right - 250, _tool.rc.top + 50, 200, 30);

	_btnSave.rc = RectMake(50, 50, 100, 30);
	_btnLoad.rc = RectMake(160, 50, 100, 30);
	_btnTerrain.rc = RectMake(_tool.rc.left + 50, 500, 100, 30);
	_btnObject.rc = RectMake(_tool.rc.left + 150, 500, 100, 30);
	_btnEraser.rc = RectMake(_tool.rc.left + 250, 500, 100, 30);
	_btnEnter.rc = RectMake(_tool.rc.right - 150, _tool.rc.bottom - 80, 100, 30);

	//처음 상태는 지형을 선택 한 것으로
	_ctrlSelect = CTRL_TERRAINDRAW;

	//샘플 타일셋 먼저 셋팅
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sample[i*SAMPLETILEX + j].frameX = j;
			_sample[i*SAMPLETILEX + j].frameY = i;

			SetRect(&_sample[i*SAMPLETILEX + j].rc,
				(_tool.rc.left + 50) + j * TILESIZEX,
				(_tool.rc.top + 50) + i * TILESIZEY,
				(_tool.rc.left + 50) + j * TILESIZEX + TILESIZEX,
				(_tool.rc.top + 50) + i * TILESIZEY + TILESIZEY);
		}
	}

	//맵 타일 영역
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tile[i*TILEX + j].rc,
				j*TILESIZEX,
				i*TILESIZEY,
				j*TILESIZEX + TILESIZEX,
				i*TILESIZEY + TILESIZEY);
		}
	}

	for (int i = 0; i < TILEX *TILEY; i++)
	{
		_tile[i].terrainX = 3;
		_tile[i].terrainY = 0;
		_tile[i].objX = 0;
		_tile[i].objY = 0;
		_tile[i].terrain = CEMENT;
		_tile[i].object = NONE;
		_tile[i].sizeX = TILESIZEX;
		_tile[i].sizeY = TILESIZEY;
	}

	_currentTile.x = 3;
	_currentTile.y = 0;
}

void mapmap::setMap()
{

	//맵 타일 그리기
	if (_leftButtonDown && !_tool.isOn)
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (PtInRect(&_tile[i].rc, _ptMouse))
			{
				switch (_ctrlSelect)
				{
				case CTRL_TERRAINDRAW:
					_tile[i].terrainX = _dragMouse.currentStartX;
					_tile[i].terrainY = _dragMouse.currentStartY;
					_tile[i].sizeX = (_dragMouse.currentEndX + 1 - _dragMouse.currentStartX)*TILESIZEX;
					_tile[i].sizeY = (_dragMouse.currentEndY + 1 - _dragMouse.currentStartY)*TILESIZEY;
					_tile[i].terrain = CEMENT;
					break;
				case CTRL_OBJDRAW:
					_tile[i].objX = _currentTile.x;
					_tile[i].objY = _currentTile.y;
					_tile[i].object = BLOCK;
					break;
				case CTRL_ERASER:
					_tile[i].objX = NULL;
					_tile[i].objY = NULL;
					_tile[i].object = NONE;
					break;
				}
				_vTile.push_back(_tile[i]);
				cout << _vTile.size() << "사이즈" << endl;
			}
		}
	}

	//샘플 타일 선택하기
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		if (_leftButtonDown && _tool.isOn && PtInRect(&_sample[i].rc, _ptMouse))
		{
			_currentTile.x = _sample[i].frameX;
			_currentTile.y = _sample[i].frameY;
			break;
		}
	}

	if (_leftButtonDown)
	{
		if (PtInRect(&_btnSave.rc, _ptMouse))save();
		if (PtInRect(&_btnLoad.rc, _ptMouse))load();
	}
}


void mapmap::buttonRender()
{

	D2DRENDER->FillRectangle
	(
		_btnSave.rc,
		D2DDEFAULTBRUSH::Red
	);

	D2DRENDER->RenderTextField
	(
		_btnSave.rc.left, _btnSave.rc.top,
		L"세이브",
		20,
		100, 30,
		D2DDEFAULTBRUSH::White,
		DWRITE_TEXT_ALIGNMENT_CENTER
	);


	D2DRENDER->FillRectangle
	(
		_btnLoad.rc,
		D2DDEFAULTBRUSH::Red
	);
	D2DRENDER->RenderTextField
	(
		_btnLoad.rc.left, _btnLoad.rc.top,
		L"로드",
		20,
		100, 30,
		D2DDEFAULTBRUSH::White,
		DWRITE_TEXT_ALIGNMENT_CENTER
	);
	if (_tool.isOn)
	{
		D2DRENDER->DrawRectangle
		(
			_message,
			D2DDEFAULTBRUSH::Red
		);

		switch (_ctrlSelect)
		{
		case CTRL_TERRAINDRAW:
			D2DRENDER->RenderTextField
			(
				_message.left, _message.top,
				L"지형 선택",
				20,
				200, 30,
				D2DDEFAULTBRUSH::Red,
				DWRITE_TEXT_ALIGNMENT_CENTER
			);
			break;
		case CTRL_OBJDRAW:
			D2DRENDER->RenderTextField
			(
				_message.left, _message.top,
				L"오브젝트 선택",
				20,
				200, 30,
				D2DDEFAULTBRUSH::Red,
				DWRITE_TEXT_ALIGNMENT_CENTER
			);
			break;
		case CTRL_ERASER:
			D2DRENDER->RenderTextField
			(
				_message.left, _message.top,
				L"지우개 선택",
				20,
				200, 30,
				D2DDEFAULTBRUSH::Red,
				DWRITE_TEXT_ALIGNMENT_CENTER
			);
			break;
		}

		D2DRENDER->DrawRectangle
		(
			_btnTerrain.rc,
			D2DDEFAULTBRUSH::Red
		);
		D2DRENDER->RenderTextField
		(
			_btnTerrain.rc.left, _btnTerrain.rc.top,
			L"지형",
			20,
			100, 30,
			D2DDEFAULTBRUSH::Red,
			DWRITE_TEXT_ALIGNMENT_CENTER
		);

		D2DRENDER->DrawRectangle
		(
			_btnObject.rc,
			D2DDEFAULTBRUSH::Red
		);
		D2DRENDER->RenderTextField
		(
			_btnObject.rc.left, _btnObject.rc.top,
			L"오브젝트",
			20,
			100, 30,
			D2DDEFAULTBRUSH::Red,
			DWRITE_TEXT_ALIGNMENT_CENTER
		);

		D2DRENDER->DrawRectangle
		(
			_btnEraser.rc,
			D2DDEFAULTBRUSH::Red
		);
		D2DRENDER->RenderTextField
		(
			_btnEraser.rc.left, _btnEraser.rc.top,
			L"지우개",
			20,
			100, 30,
			D2DDEFAULTBRUSH::Red,
			DWRITE_TEXT_ALIGNMENT_CENTER
		);
		D2DRENDER->DrawRectangle
		(
			_btnEnter.rc,
			D2DDEFAULTBRUSH::Red
		);
		D2DRENDER->RenderTextField
		(
			_btnEnter.rc.left, _btnEnter.rc.top,
			L"확인",
			20,
			100, 30,
			D2DDEFAULTBRUSH::Red,
			DWRITE_TEXT_ALIGNMENT_CENTER
		);
	}

}

void mapmap::tapTool()
{

	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{

		_dragMouse.currentStartX = 0;
		_dragMouse.currentStartY = 0;
		_dragMouse.currentEndY = 0;
		_dragMouse.currentEndY = 0;
		_dragMouse.start.x = 0;
		_dragMouse.start.y = 0;
		_dragMouse.end.x = 0;
		_dragMouse.end.y = 0;

		_tool.isOn = true;
		_dragStart = true;
	}

}

void mapmap::dragField()
{
	if (_leftButtonDown)
	{
		if (PtInRect(&_btnTerrain.rc, _ptMouse))_ctrlSelect = CTRL_TERRAINDRAW;
		if (PtInRect(&_btnObject.rc, _ptMouse))_ctrlSelect = CTRL_OBJDRAW;
		if (PtInRect(&_btnEraser.rc, _ptMouse))_ctrlSelect = CTRL_ERASER;
		if (PtInRect(&_btnEnter.rc, _ptMouse))
		{
			_tool.isOn = false;
		}
	}
	for (int i = 0; i < SAMPLETILEX*SAMPLETILEY; i++)
	{
		if (PtInRect(&_sample[i].rc, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_dragMouse.start.x = _sample[i].rc.left;
				_dragMouse.start.y = _sample[i].rc.top;
				_dragMouse.currentStartX = _sample[i].frameX;
				_dragMouse.currentStartY = _sample[i].frameY;
			}
			if (_leftButtonDown)
			{
				_dragMouse.end.x = _sample[i].rc.right;
				_dragMouse.end.y = _sample[i].rc.bottom;
				_dragMouse.currentEndX = _sample[i].frameX;
				_dragMouse.currentEndY = _sample[i].frameY;
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				_dragMouse.end.x = _sample[i].rc.right;
				_dragMouse.end.y = _sample[i].rc.bottom;
				_dragMouse.currentEndX = _sample[i].frameX;
				_dragMouse.currentEndY = _sample[i].frameY;
			}
			_dragMouse.rc = RectMakeDrag(_dragMouse.start.x, _dragMouse.start.y, _dragMouse.end.x, _dragMouse.end.y);
		}
	}
}
