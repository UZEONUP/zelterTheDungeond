#include "stdafx.h"
#include "characterPick.h"

HRESULT characterPick::init()
{
	setImages();
	_mouse = IMAGEMANAGER->findImage("mouse");

	_characterPick.rc = RectMakeCenter(WINSIZEX / 2 -325, WINSIZEY / 2, WINSIZEX / 2, WINSIZEY);
	_characterPick2.rc = RectMakeCenter(WINSIZEX / 2 + 325, WINSIZEY / 2, WINSIZEX / 2, WINSIZEY);

	_characterPick.img = IMAGEMANAGER->findImage("gunner_illust_off");
	_characterPick.currentFrameX = 0;
	_characterPick2.img = IMAGEMANAGER->findImage("wizard_illust_off");

	_characterPick.on = false;
	_characterPick2.on = false;
	_character.pick = false;

	_character.rc = RectMakeCenter(WINSIZEX / 2 - 300, WINSIZEY - 100, 100, 100);
	_character.currentFrameX = 0;
	_character2.rc = RectMakeCenter(WINSIZEX / 2 + 300, WINSIZEY - 100, 100, 100);

	_character.img = IMAGEMANAGER->findImage("gunner_pick_frame_off");
	//_character2.img = IMAGEMANAGER->findImage("wizard_pick_off");
	return S_OK;
}

void characterPick::update()
{
	_count++;

	if (PtInRect(&_characterPick.rc, _ptMouse))_characterPick.on = true;
	else _characterPick.on = false;

	if (PtInRect(&_characterPick2.rc, _ptMouse))_characterPick2.on = true;
	else _characterPick2.on = false;

	if (_characterPick.on)
	{
		_characterPick.img = IMAGEMANAGER->findImage("gunner_illust_on");
		_character.img = IMAGEMANAGER->findImage("gunner_pick_frame_on");
		if (_count % 7 == 0)
		{
			
			_characterPick.currentFrameX++;
			if (_characterPick.currentFrameX >= _characterPick.img->getMaxFrameX())_characterPick.currentFrameX = 0;
			_count = 0;
		}
		
	}
	
	else if (!_characterPick.on)
	{
		_characterPick.img = IMAGEMANAGER->findImage("gunner_illust_off");
		_character.img = IMAGEMANAGER->findImage("gunner_pick_frame_off");
		_characterPick.currentFrameX = 0;
		if(!_character.pick)_character.currentFrameX = 0;
	}
	if (_characterPick2.on)
	{
		_characterPick2.img = IMAGEMANAGER->findImage("wizard_illust_on");
	}
	else if (!_characterPick2.on)
	{
		_characterPick2.img = IMAGEMANAGER->findImage("wizard_illust_off");
	}


	if (PtInRect(&_characterPick.rc, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_character.pick = true;
	}
	if (_character.pick)
	{
		_character.img = IMAGEMANAGER->findImage("gunner_pick_frame_on");
		_characterPick.img = IMAGEMANAGER->findImage("gunner_illust_on");
		_characterPick2.img = IMAGEMANAGER->findImage("wizard_illust_off");

		if (_count % 7 == 0)_character.currentFrameX+=1;
		if (_character.currentFrameX >= _character.img->getMaxFrameX())
			SCENEMANAGER->changeScene("niflheim");
		cout << _character.currentFrameX << endl;
	}
}

void characterPick::release()
{
}

void characterPick::render()
{
	D2DRENDER->DrawRectangle(_characterPick.rc, D2DRenderer::DefaultBrush::Black, 1.f);
	D2DRENDER->DrawRectangle(_characterPick2.rc, D2DRenderer::DefaultBrush::Black, 1.f);
	if(KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDER->DrawRectangle(_character.rc, D2DRenderer::DefaultBrush::Black, 1.f);
		D2DRENDER->DrawRectangle(_character2.rc, D2DRenderer::DefaultBrush::Black, 1.f);
	}

	_characterPick.img->frameRender2(_characterPick.rc.left, _characterPick.rc.top,_characterPick.currentFrameX,0);
	_character.img->frameRender2(_character.rc.left, _character.rc.top, _character.currentFrameX, 0);
	_characterPick2.img->render(_characterPick2.rc.left+150, _characterPick2.rc.top);

	_mouse->render(_ptMouse.x - 7, _ptMouse.y - 5);
}

void characterPick::setImages()
{
	IMAGEMANAGER->addFrameImage("gunner_illust_off", L"STATE/PICK/gunner_illust_off.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_illust_on", L"STATE/PICK/gunner_illust_on.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_pick_frame_off", L"STATE/PICK/gunner_pick_off.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_pick_frame_on", L"STATE/PICK/gunner_pick_on.png", 9, 1);
	IMAGEMANAGER->addImage("wizard_illust_off", L"STATE/PICK/wizard_illust_off.png");
	IMAGEMANAGER->addImage("wizard_illust_on", L"STATE/PICK/wizard_illust_on.png");
	IMAGEMANAGER->addImage("mouse", L"무기/마우스.png");
}
