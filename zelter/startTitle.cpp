#include "stdafx.h"
#include "startTitle.h"

startTitle::startTitle()
{
}

startTitle::~startTitle()
{
}

HRESULT startTitle::init()
{
	IMAGEMANAGER->addFrameImage("startTitle", L"UI/���ʹ�_Ÿ��Ʋ_100.png", 10, 10);
	IMAGEMANAGER->addImage("logo", L"UI/�ΰ�.png");
	_backGroundImg = IMAGEMANAGER->findImage("startTitle");
	_titleImg = IMAGEMANAGER->findImage("logo");
	_count = _currentFrameX = 0;

	return S_OK;
}

void startTitle::release()
{
}

void startTitle::update()
{
	_count++;

	if (_count % 7 == 0) 
	{
		_currentFrameX++;
		if (_currentFrameX >= 10)
		{
			_currentFrameY++;
			_currentFrameX = 0;
		}
		if (_currentFrameY >= 10) 
		{
			_currentFrameY = 0;
			_currentFrameX = 0;
		}
		_count = 0;
	}
}

void startTitle::render()
{
	_backGroundImg->frameRender2(0, 0, _currentFrameX, _currentFrameY);
	_titleImg->render(WINSIZEX / 2-370, WINSIZEY / 2-200);
}
