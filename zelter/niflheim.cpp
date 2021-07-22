#include "stdafx.h"
#include "niflheim.h"

#include "niflheimIdle.h"

HRESULT niflheim::init()
{
	imageAdd();

	_state = new niflheimIdle;
	_state->enter(this);

	_niflheim.x = WINSIZEX / 2;
	_niflheim.y = WINSIZEY / 2;
	_niflheim.rc = RectMake(_niflheim.x, _niflheim.y, _niflheim.img->getFrameWidth(), _niflheim.img->getFrameHeight());
	_niflheim.currentHP = 100;
	_niflheim.maxHP = 100;
	_niflheim.direction = 0;
	_niflheim.isDie = false;

	_niflheim.icePillar = new niflheimIcePillar;
	_niflheim.icePillar->seticePillar(_niflheim.x, _niflheim.y);
	_niflheim.iceSpear = new niflheimIceSpear;
	_niflheim.iceicle = new niflheimIcicle;
	_niflheim.progressBar = new progressBar;
	_niflheim.progressBar->init(650, WINSIZEY - 100, 600, 50);

	_bulletFireCount = 0;

	return S_OK;
}

void niflheim::release()
{
}

void niflheim::update()
{
	_niflheim.progressBar->update();
	_niflheim.progressBar->setGauge(_niflheim.currentHP, _niflheim.maxHP);
	//상태 확인용======
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) _niflheim.currentHP = 0;
	if (_state->getStateNamge() == "niflheimDie") _niflheim.currentHP = 50;

	//확인용===
	if (KEYMANAGER->isToggleKey(VK_SPACE))
	{
		_niflheim.icePillar->setCurrentHP(0, 0);
	}
	//=========
	//================

	inPutHandle();

	_state->update(this);

	float directAngle = GetAngle(_ptMouse.x, _ptMouse.y, _niflheim.x, _niflheim.y);
	if (directAngle > PI / 2 && directAngle < 3 * PI / 2) _niflheim.direction = 0;
	else _niflheim.direction = 1;

	bulletUpdate();

	_niflheim.rc = RectMake(_niflheim.x, _niflheim.y, _niflheim.img->getFrameWidth(), _niflheim.img->getFrameHeight());
}

void niflheim::render()
{
	_state->render(this);

	bulletRender();

	_niflheim.progressBar->render();
}

void niflheim::inPutHandle()
{
	state* newState = _state->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}

void niflheim::bulletUpdate()
{
	if (_niflheim.icePillar->getVIcePillar().size() != 0) _niflheim.icePillar->update(_niflheim.x, _niflheim.y);
	if (_niflheim.icePillar->getVbullet().size() != 0) _niflheim.icePillar->bulletMove();
	if (_niflheim.iceSpear->getVIceSpear().size() != 0) _niflheim.iceSpear->update();
	if (_niflheim.iceicle->getVIcicle().size() != 0) _niflheim.iceicle->update();
	/*if (_state->getStateNamge() == "niflheimIcePillar")
	{
		_bulletFireCount++;
		if(_bulletFireCount % 3 == 0)
		{
			_niflheim.icePillar->fireBullet1(_ptMouse.x, _ptMouse.y);
			_niflheim.icePillar->fireBullet2(_ptMouse.x, _ptMouse.y);
		}
	}*/
}

void niflheim::bulletRender()
{
	if (_niflheim.icePillar->getVIcePillar().size() != 0) _niflheim.icePillar->render();
	if (_niflheim.icePillar->getVbullet().size() != 0) _niflheim.icePillar->bulletRender();
	if (_niflheim.iceSpear->getVIceSpear().size() != 0) _niflheim.iceSpear->render();
	if (_niflheim.iceicle->getVIcicle().size() != 0) _niflheim.iceicle->render();
}

void niflheim::imageAdd()
{
	//보스::니플헤임 이미지
	IMAGEMANAGER->addFrameImage("niflheimIdle", L"niflheim/niflheimIdle.png", 6, 2);
	IMAGEMANAGER->addFrameImage("niflheimAttack", L"niflheim/niflheimAttack.png", 11, 2);
	IMAGEMANAGER->addFrameImage("niflheimEnter", L"niflheim/niflheimEnter.png", 16, 2);
	IMAGEMANAGER->addFrameImage("niflheimDie", L"niflheim/niflheimDie.png", 30, 2);
	//총알::니플헤임 이미지
	IMAGEMANAGER->addFrameImage("icePillarReady", L"niflheimBullet/icePillarReady.png", 11, 1);
	IMAGEMANAGER->addFrameImage("icePillar", L"niflheimBullet/icePillar.png", 8, 1);
	IMAGEMANAGER->addFrameImage("icicleReady", L"niflheimBullet/icicleReady.png", 9, 1);
	IMAGEMANAGER->addImage("icicle", L"niflheimBullet/icicle.png");
	IMAGEMANAGER->addFrameImage("iceSpear", L"niflheimBullet/iceSpear.png", 13, 2);
	IMAGEMANAGER->addImage("iceBullet", L"niflheimBullet/iceBullet.png");
	//효과 이미지
	IMAGEMANAGER->addFrameImage("icePillarDestroy", L"effect/icePillarDestroy.png", 3, 1);
	IMAGEMANAGER->addFrameImage("icicleDestroy", L"effect/icicleDestroy.png", 3, 1);
	IMAGEMANAGER->addFrameImage("nullImg", L"niflheimBullet/nullImg.png", 5, 1);
}
