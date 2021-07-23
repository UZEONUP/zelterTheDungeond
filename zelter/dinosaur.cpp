#include "stdafx.h"
#include "dinosaur.h"

dinosaur::dinosaur()
{
}

dinosaur::~dinosaur()
{
}

HRESULT dinosaur::init()
{
	_dialogue = new dialogue;

	return S_OK;
}

void dinosaur::release()
{
}

void dinosaur::update()
{
}

void dinosaur::render()
{
	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			D2DRENDER->DrawRectangle(_viDinosaur->rc, D2DRenderer::DefaultBrush::White);
		}
		_viDinosaur->img->frameRender2(_viDinosaur->rc.left, _viDinosaur->rc.top, _viDinosaur->currentFrameX, _viDinosaur->currentFrameY);
	}

	_dialogue->render();
}

void dinosaur::setEnemy(float x, float y)
{
	IMAGEMANAGER->addFrameImage("dinosaurIdle", L"dinosaur/dinosaurIdle_1_1.png", 1, 2);
	IMAGEMANAGER->addFrameImage("dinosaurWalk", L"dinosaur/dinosaurWalk_2_2.png", 2, 2);
	IMAGEMANAGER->addFrameImage("dinosaurAttack", L"dinosaur/dinosaurAttack_2_2.png", 2, 2);
	IMAGEMANAGER->addFrameImage("dinosaurDeath", L"dinosaur/dinosaurDeath_2_2.png", 2, 2);

	for (int i = 0; i < 1; i++)
	{
		if (10 <= _vDinosaur.size()) return;

		tagDinosaur dinosaur;
		ZeroMemory(&dinosaur, sizeof(tagDinosaur));
		dinosaur.img = IMAGEMANAGER->findImage("fishManIdle");
		dinosaur.speed = 2.0f;
		dinosaur.angle = RND->getFromFloatTo(0, PI2);
		dinosaur.x = x;
		dinosaur.y = y;
		dinosaur.currentHp = dinosaur.maxHp = 100;
		dinosaur.currentFrameX = dinosaur.currentFrameY = 0;
		dinosaur.count = dinosaur.changeCount = 0;
		dinosaur.state = DINOSAUR_IDLE;
		//angle에 따라 방향지정
		if (dinosaur.angle > 0 && dinosaur.angle <= PI / 2 || dinosaur.angle >= PI + PI / 2 && dinosaur.angle <= PI2)
			dinosaur.direction = DINOSAUR_RIGHT;
		else if (dinosaur.angle > PI / 2 && dinosaur.angle <= PI + PI / 2)
			dinosaur.direction = DINOSAUR_LEFT;
		dinosaur.rc = RectMakeCenter(dinosaur.x, dinosaur.y, dinosaur.img->getWidth() / dinosaur.img->getMaxFrameX(), dinosaur.img->getHeight() / dinosaur.img->getMaxFrameY());

		_vDinosaur.push_back(dinosaur);
	}
}

void dinosaur::dinoMove(float x, float y)
{
	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		//랜덤값에 따라 IDLE 혹은 WALK 상태로 변경
		_viDinosaur->changeCount++;
		if (_viDinosaur->changeCount >= RND->getFromIntTo(100, 200))
		{
			_viDinosaur->angle = RND->getFromFloatTo(0, PI2);

			int changeRand = RND->getFromIntTo(0, 2);

			switch (changeRand)
			{
			case 0:
				_viDinosaur->state = DINOSAUR_IDLE;
				break;
			case 1:
				_viDinosaur->state = DINOSAUR_WALK;
				break;
			}
			_viDinosaur->changeCount = 0;
		}
		//WALK 상태인 경우 speed 값에 따라 이동
		if (_viDinosaur->state == DINOSAUR_WALK)
		{
			_viDinosaur->x += cosf(_viDinosaur->angle) * _viDinosaur->speed;
			_viDinosaur->y += -sinf(_viDinosaur->angle) * _viDinosaur->speed;

		}
		if (GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) < 300 && GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) > 30)
		{
			_viDinosaur->angle = GetAngle(_viDinosaur->x, _viDinosaur->y, x, y);
			_viDinosaur->speed = 3.0f;
		}
		if (GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) <= 30)
		{
			_viDinosaur->state = DINOSAUR_ATTACK;
			_viDinosaur->angle = GetAngle(_viDinosaur->x, _viDinosaur->y, x, y);
		}
		if (GetDistance(_viDinosaur->x, _viDinosaur->y, x, y) > 300)
		{
			_viDinosaur->state = DINOSAUR_WALK;
			_viDinosaur->speed = 2.0f;
		}
		if (_viDinosaur->currentHp <= 0)
		{
			_viDinosaur->state = DINOSAUR_DEATH;

		}
		//angle에 따라 방향지정
		if (_viDinosaur->angle > 0 && _viDinosaur->angle <= PI / 2 || _viDinosaur->angle >= PI + PI / 2 && _viDinosaur->angle <= PI2)_viDinosaur->direction = DINOSAUR_RIGHT;
		else if (_viDinosaur->angle > PI / 2 && _viDinosaur->angle <= PI + PI / 2)_viDinosaur->direction = DINOSAUR_LEFT;
		//angle 예외처리
		if (_viDinosaur->angle >= PI2)_viDinosaur->angle -= PI2;
		if (_viDinosaur->angle <= 0) _viDinosaur->angle += PI2;
		//화면 밖 예외처리
		if (_viDinosaur->rc.left < 0) _viDinosaur->x = (_viDinosaur->img->getWidth() / _viDinosaur->img->getMaxFrameX()) / 2;
		if (_viDinosaur->rc.right > WINSIZEX) _viDinosaur->x = WINSIZEX - (_viDinosaur->img->getWidth() / _viDinosaur->img->getMaxFrameX()) / 2;
		if (_viDinosaur->rc.top < 0) _viDinosaur->y = (_viDinosaur->img->getHeight() / _viDinosaur->img->getMaxFrameY()) / 2;
		if (_viDinosaur->rc.bottom > WINSIZEY) _viDinosaur->y = WINSIZEY - (_viDinosaur->img->getHeight() / _viDinosaur->img->getMaxFrameY()) / 2;
		//렉트 
		_viDinosaur->rc = RectMakeCenter(_viDinosaur->x, _viDinosaur->y, _viDinosaur->img->getWidth() / _viDinosaur->img->getMaxFrameX(), _viDinosaur->img->getHeight() / _viDinosaur->img->getMaxFrameY());
	}

	_dialogue->update();
}

void dinosaur::dinoState()
{
	for (_viDinosaur = _vDinosaur.begin(); _viDinosaur != _vDinosaur.end(); ++_viDinosaur)
	{
		//이미지 프레임 전환
		_viDinosaur->count++;
		if (_viDinosaur->count % 15 == 0)
		{
			_viDinosaur->currentFrameX++;
			switch (_viDinosaur->direction)
			{
			case DINOSAUR_RIGHT:
				_viDinosaur->currentFrameY = 0;
				break;
			case DINOSAUR_LEFT:
				_viDinosaur->currentFrameY = 1;
				break;
			}
		}
		//상태별 예외처리
		switch (_viDinosaur->state)
		{
			//IDLE 상태일 경우
		case DINOSAUR_IDLE:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurIdle");
			if (_viDinosaur->currentFrameX > 0)_viDinosaur->currentFrameX = 0;
			break;
			//WALK 상태일 경우
		case DINOSAUR_WALK:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurWalk");
			if (_viDinosaur->currentFrameX > 1)_viDinosaur->currentFrameX = 0;
			break;
			//ATTACK 상태일 경우
		case DINOSAUR_ATTACK:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurAttack");
			if (_viDinosaur->currentFrameX > 1)
			{
				//공격할 때 대사 출력신호 보내줍니다
				_dialogue->speechCreate(DINOSAUR, _viDinosaur->x - 60, _viDinosaur->y - 60);

				_viDinosaur->currentFrameX = 0;
			}
			break;
			//DEATH 상태일 경우
		case DINOSAUR_DEATH:
			_viDinosaur->img = IMAGEMANAGER->findImage("dinosaurDeath");
			if (_viDinosaur->currentFrameX > 1)_viDinosaur->currentFrameX = 0;
			break;
		}
	}
}
