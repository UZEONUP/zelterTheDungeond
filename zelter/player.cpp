#include "stdafx.h"
#include "player.h"
#include "playerStateIdle.h"
#include "playerBullet.h"




HRESULT player::init()
{
	addIMAGES(); //이미지추가

	_player.img = IMAGEMANAGER->findImage("gunner_idle");
	_playerGun.img = IMAGEMANAGER->findImage("GUN1");
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.rc = RectMakeCenter(_player.x,_player.y, _player.img->getFrameWidth(),_player.img->getFrameHeight());
	_player.shadow = RectMakeCenter(_player.x, _player.y, 100, 10);
	_playerGun.rc = RectMakeCenter(_player.x + 30, _player.y, _playerGun.img->getWidth(), _playerGun.img->getHeight());
	_player.currentFrameX = _player.currentFrameY = 0;

	_playerGun.x = _player.x;
	_playerGun.y = _player.y;
	_player.speed = 3.0f;
	_gunType = 0;


	_playerBullet = new playerBullet;

	_enemy.x = WINSIZEX / 2;
	_enemy.y = WINSIZEY / 2;
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, 100, 100);

	state = new playerStateIdle();
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	inputHandle();
	state->update(this);
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.shadow = RectMakeCenter(_player.x, _player.rc.bottom, 50, 10);
	

	//플레이어 마우스 방향으로 바라보기
	_playerGun.angle = GetAngle(_playerGun.x, _playerGun.y, _ptMouse.x, _ptMouse.y) * (180 / PI);

		if (_playerGun.angle < 340 && 0 < _playerGun.angle) _player.direction = 0;
		if (_playerGun.angle < 110 && 70 < _playerGun.angle) _player.direction = 2;
		if (_playerGun.angle < 200 && 160 < _playerGun.angle) _player.direction = 1;
		if (_playerGun.angle < 290 && 250 < _playerGun.angle) _player.direction = 3;
		if (_playerGun.angle < 70 && 20 < _playerGun.angle) _player.direction = 5;
		if (_playerGun.angle < 160 && 110 < _playerGun.angle) _player.direction = 4;
		if (_playerGun.angle < 250 && 200 < _playerGun.angle) _player.direction = 7;
		if (_playerGun.angle < 310 && 290 < _playerGun.angle) _player.direction = 6;
	
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, 100, 100);
	_playerGun.x = _player.x;
	_playerGun.y = _player.y;
	_playerBullet->move(_gunType,_enemy.x,_enemy.y);


	//마우스 위치가 플레이어 중점보다 크면 오른쪽에
	if (_ptMouse.x > _player.x)
	{
		_playerGun.rc = RectMakeCenter(_player.x + 27, _player.y + 15, _playerGun.img->getWidth(), _playerGun.img->getHeight());
		switch (_gunType)
		{

		case 0:
			_playerGun.img = IMAGEMANAGER->findImage("GUN1");
			break;
		case 1:
			_playerGun.img = IMAGEMANAGER->findImage("GUN2");
			break;
		case 2:
			_playerGun.img = IMAGEMANAGER->findImage("GUN3");
			break;
		case 3:
			_playerGun.img = IMAGEMANAGER->findImage("GUN4");
			break;
		case 4:
			_playerGun.img = IMAGEMANAGER->findImage("GUN5");
			break;
		}
	}

	//작으면 왼쪽에 그려줌
	else
	{
		_playerGun.rc = RectMakeCenter(_player.x - 10, _player.y + 15, _playerGun.img->getWidth(), _playerGun.img->getHeight());
		
		switch (_gunType)
		{

		case 0:
			_playerGun.img = IMAGEMANAGER->findImage("GUN1R");
			break;
		case 1:
			_playerGun.img = IMAGEMANAGER->findImage("GUN2R");
			break;
		case 2:
			_playerGun.img = IMAGEMANAGER->findImage("GUN3R");
			break;
		case 3:
			_playerGun.img = IMAGEMANAGER->findImage("GUN4R");
			break;
		case 4:
			_playerGun.img = IMAGEMANAGER->findImage("GUN5R");
			break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{

		_gunType++;
		if (_gunType >= 5)_gunType = 0;
	}

}

void player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		D2DRENDER->DrawRectangle(_player.rc, D2DRenderer::DefaultBrush::White, 1.f);
		D2DRENDER->DrawRectangle(_player.shadow, D2DRenderer::DefaultBrush::White, 1.f);
		D2DRENDER->DrawRectangle(_playerGun.rc, D2DRenderer::DefaultBrush::White, 1.f, _playerGun.angle);
	}
		D2DRENDER->DrawRectangle(_enemy.rc, D2DRenderer::DefaultBrush::Red, 1.f);
	_playerBullet->render();

	_player.img->cutRender(_player.rc.left, _player.rc.top,
		_player.img->getFrameX(),_player.img->getFrameY(),
		_player.img->getFrameWidth(),_player.img->getFrameHeight());
	_playerGun.img->render(_playerGun.rc.left, _playerGun.rc.top,1.f,1.f,_playerGun.angle);

	if (_player.direction ==2|| _player.direction == 4|| _player.direction == 5)
	{
		_playerGun.img->render(_playerGun.rc.left, _playerGun.rc.top, 1.f, 1.f, _playerGun.angle);
		_player.img->cutRender(_player.rc.left, _player.rc.top,
			_player.img->getFrameX(), _player.img->getFrameY(),
			_player.img->getFrameWidth(), _player.img->getFrameHeight());
		_playerGun.img->render(_playerGun.rc.left, _playerGun.rc.top, 1.f, 1.f, _playerGun.angle);
	}
}

void player::addIMAGES()
{
	IMAGEMANAGER->addImage("GUN1", L"무기/기본.png");
	IMAGEMANAGER->addImage("GUN2", L"무기/산탄.png");
	IMAGEMANAGER->addImage("GUN3", L"무기/유도총.png");
	IMAGEMANAGER->addImage("GUN4", L"무기/수류탄.png");
	IMAGEMANAGER->addImage("GUN5", L"무기/화염방사.png");

	IMAGEMANAGER->addImage("GUN1R", L"무기/기본반대.png");
	IMAGEMANAGER->addImage("GUN2R", L"무기/산탄반대.png");
	IMAGEMANAGER->addImage("GUN3R", L"무기/유도총반대.png");
	IMAGEMANAGER->addImage("GUN4R", L"무기/수류탄반대.png");
	IMAGEMANAGER->addImage("GUN5R", L"무기/화염방사반대.png");


	IMAGEMANAGER->addFrameImage("gunner_idle", L"STATE/IDLE/gunner_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_back_idle", L"STATE/IDLE/gunner_back_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_idle", L"STATE/IDLE/gunner_left_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_idle", L"STATE/IDLE/gunner_right_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_left-up_idle", L"STATE/IDLE/gunner_left-up_idle2.png", 4, 1);
	IMAGEMANAGER->addFrameImage("gunner_right-up_idle", L"STATE/IDLE/gunner_right-up_idle2.png", 4, 1);

	IMAGEMANAGER->addFrameImage("gunner_run", L"STATE/RUN/gunner_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_back_run", L"STATE/RUN/gunner_back_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_run", L"STATE/RUN/gunner_left_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_run", L"STATE/RUN/gunner_right_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_left-up_run", L"STATE/RUN/gunner_up_left_run.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right-up_run", L"STATE/RUN/gunner_up_right_run.png", 6, 1);

	IMAGEMANAGER->addFrameImage("gunner_roll", L"STATE/ROLL/gunner_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_back_roll", L"STATE/ROLL/gunner_back_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_roll", L"STATE/ROLL/gunner_left_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_roll", L"STATE/ROLL/gunner_right_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_left-up_roll", L"STATE/ROLL/gunner_left_up_roll.png", 9, 1);
	IMAGEMANAGER->addFrameImage("gunner_right-up_roll", L"STATE/ROLL/gunner_right_up_roll.png", 9, 1);
}

void player::inputHandle() //스테이트 호출
{
	playerState* newState = state->inputHandle(this);

	if (newState != nullptr)
	{
		SAFE_DELETE(state);
		state = newState;
		state->enter(this);
	}
}




