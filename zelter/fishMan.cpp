#include "stdafx.h"
#include "fishMan.h"

fishMan::fishMan()
{
}

fishMan::~fishMan()
{
}

HRESULT fishMan::init()
{
	_dialogue = new dialogue;

	return S_OK;
}

void fishMan::release()
{
}

void fishMan::update()
{

}

void fishMan::render()
{

	for (_viFishMan = _vFishMan.begin(); _viFishMan != _vFishMan.end(); ++_viFishMan)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			D2DRENDER->DrawRectangle(_viFishMan->rc, D2DRenderer::DefaultBrush::White);
		}
		_viFishMan->img->frameRender2(_viFishMan->rc.left, _viFishMan->rc.top, _viFishMan->currentFrameX, _viFishMan->currentFrameY);
	}

	_dialogue->render();
}


void fishMan::setEnemy(float x, float y)
{
	IMAGEMANAGER->addFrameImage("fishManIdle", L"fishMan/fishManIdle.png", 3, 2);
	IMAGEMANAGER->addFrameImage("fishManWalk", L"fishMan/fishManWalk.png", 4, 2);
	IMAGEMANAGER->addFrameImage("fishManRun", L"fishMan/fishManRun.png", 2, 2);
	IMAGEMANAGER->addFrameImage("fishManAttack", L"fishMan/fishManAttack.png", 3, 2);
	IMAGEMANAGER->addFrameImage("fishManDie", L"fishMan/fishManDie.png", 4, 2);

	for (int i = 0; i < 1; i++)
	{
		if (10 <= _vFishMan.size()) return;

		tagFishMan fishMan;
		ZeroMemory(&fishMan, sizeof(tagFishMan));
		fishMan.img = IMAGEMANAGER->findImage("fishManIdle");
		fishMan.speed = 2.0f;
		fishMan.angle = RND->getFromFloatTo(0, PI2);
		fishMan.x = x;
		fishMan.y = y;
		fishMan.currentHp = fishMan.maxHp = 100;
		fishMan.currentFrameX = fishMan.currentFrameY = 0;
		fishMan.count = fishMan.changeCount = 0;
		fishMan.state = FISHMAN_IDLE;
		//angle에 따라 방향지정
		if (fishMan.angle > 0 && fishMan.angle <= PI / 2 || fishMan.angle >= PI + PI / 2 && fishMan.angle <= PI2)
			fishMan.direction = FISHMAN_RIGHT;
		else if (fishMan.angle > PI / 2 && fishMan.angle <= PI + PI / 2)
			fishMan.direction = FISHMAN_LEFT;
		fishMan.rc = RectMakeCenter(fishMan.x, fishMan.y, fishMan.img->getWidth() / fishMan.img->getMaxFrameX(), fishMan.img->getHeight() / fishMan.img->getMaxFrameY());

		_vFishMan.push_back(fishMan);
	}
}
//피쉬맨 움직임
void fishMan::fishMove(float x, float y)
{
	for (_viFishMan = _vFishMan.begin(); _viFishMan != _vFishMan.end(); ++_viFishMan)
	{
		//랜덤값에 따라 IDLE 혹은 WALK 상태로 변경
		_viFishMan->changeCount++;
		if (_viFishMan->changeCount >= RND->getFromIntTo(100, 200))
		{
			_viFishMan->angle = RND->getFromFloatTo(0, PI2);

			int changeRand = RND->getFromIntTo(0, 2);

			switch (changeRand)
			{
			case 0:
				_viFishMan->state = FISHMAN_IDLE;
				break;
			case 1:
				_viFishMan->state = FISHMAN_WALK;
				break;
			}
			_viFishMan->changeCount = 0;
		}
		//WALK 상태인 경우 speed 값에 따라 이동
		if (_viFishMan->state == FISHMAN_WALK)
		{
			_viFishMan->x += cosf(_viFishMan->angle) * _viFishMan->speed;
			_viFishMan->y += -sinf(_viFishMan->angle) * _viFishMan->speed;

		}
		if (GetDistance(_viFishMan->x, _viFishMan->y, x, y) < 300 && GetDistance(_viFishMan->x, _viFishMan->y, x, y) > 30)
		{
			_viFishMan->state = FISHMAN_RUN;
			_viFishMan->angle = GetAngle(_viFishMan->x, _viFishMan->y, x, y);

			_viFishMan->x += cosf(_viFishMan->angle) * _viFishMan->speed;
			_viFishMan->y += -sinf(_viFishMan->angle) * _viFishMan->speed;
		}
		if (GetDistance(_viFishMan->x, _viFishMan->y, x, y) <= 30)
		{
			_viFishMan->state = FISHMAN_ATTACK;
			_viFishMan->angle = GetAngle(_viFishMan->x, _viFishMan->y, x, y);
		}
		if(GetDistance(_viFishMan->x, _viFishMan->y, x, y) > 300)
		{
			_viFishMan->state = FISHMAN_WALK;
		}
		if (_viFishMan->currentHp <= 0) 
		{
			_viFishMan->state = FISHMAN_DEATH;
			
		}
		//angle에 따라 방향지정
		if (_viFishMan->angle > 0 && _viFishMan->angle <= PI / 2 || _viFishMan->angle >= PI + PI / 2 && _viFishMan->angle <= PI2)_viFishMan->direction = FISHMAN_RIGHT;
		else if (_viFishMan->angle > PI / 2 && _viFishMan->angle <= PI + PI / 2)_viFishMan->direction = FISHMAN_LEFT;
		//angle 예외처리
		if (_viFishMan->angle >= PI2)_viFishMan->angle -= PI2;
		if (_viFishMan->angle <= 0) _viFishMan->angle += PI2;
		//화면 밖 예외처리
		if (_viFishMan->rc.left < 0) _viFishMan->x = (_viFishMan->img->getWidth() / _viFishMan->img->getMaxFrameX()) / 2;
		if (_viFishMan->rc.right > WINSIZEX) _viFishMan->x = WINSIZEX - (_viFishMan->img->getWidth() / _viFishMan->img->getMaxFrameX()) / 2;
		if (_viFishMan->rc.top < 0) _viFishMan->y = (_viFishMan->img->getHeight() / _viFishMan->img->getMaxFrameY()) / 2;
		if (_viFishMan->rc.bottom > WINSIZEY) _viFishMan->y = WINSIZEY - (_viFishMan->img->getHeight() / _viFishMan->img->getMaxFrameY()) / 2;
		//렉트 
		_viFishMan->rc = RectMakeCenter(_viFishMan->x, _viFishMan->y, _viFishMan->img->getWidth() / _viFishMan->img->getMaxFrameX(), _viFishMan->img->getHeight() / _viFishMan->img->getMaxFrameY());
	}

	_dialogue->update();
}
//피쉬맨 상태
void fishMan::fishState()
{
	for (_viFishMan = _vFishMan.begin(); _viFishMan != _vFishMan.end(); ++_viFishMan)
	{
		//이미지 프레임 전환
		_viFishMan->count++;
		if (_viFishMan->count % 15 == 0)
		{
			switch (_viFishMan->direction)
			{
			case FISHMAN_RIGHT:
				_viFishMan->currentFrameY = 0;
				_viFishMan->currentFrameX++;

				break;
			case FISHMAN_LEFT:
				_viFishMan->currentFrameY = 1;
				_viFishMan->currentFrameX--;

				break;
			}
		}
		//상태별 예외처리
		switch (_viFishMan->state)
		{
			//IDLE 상태일 경우
		case FISHMAN_IDLE:
			_viFishMan->img = IMAGEMANAGER->findImage("fishManIdle");
			switch (_viFishMan->direction)
			{
			case FISHMAN_RIGHT:
				if (_viFishMan->currentFrameX > 2)_viFishMan->currentFrameX = 0;
				break;
			case FISHMAN_LEFT:
				if (_viFishMan->currentFrameX < 0) _viFishMan->currentFrameX = 2;
				break;
			}
			break;
			//WALK 상태일 경우
		case FISHMAN_WALK:
			_viFishMan->img = IMAGEMANAGER->findImage("fishManWalk");
			switch (_viFishMan->direction)
			{
			case FISHMAN_RIGHT:
				if (_viFishMan->currentFrameX > 3)_viFishMan->currentFrameX = 0;
				break;
			case FISHMAN_LEFT:
				if (_viFishMan->currentFrameX < 0) _viFishMan->currentFrameX = 3;
				break;
			}
			break;
			//RUN 상태일 경우
		case FISHMAN_RUN:
			_viFishMan->img = IMAGEMANAGER->findImage("fishManRun");
			switch (_viFishMan->direction)
			{
			case FISHMAN_RIGHT:
				if (_viFishMan->currentFrameX > 1)_viFishMan->currentFrameX = 0;
				break;
			case FISHMAN_LEFT:
				if (_viFishMan->currentFrameX < 0) _viFishMan->currentFrameX = 1;
				break;
			}
			break;
			//ATTACK 상태일 경우
		case FISHMAN_ATTACK:
			_viFishMan->img = IMAGEMANAGER->findImage("fishManAttack");
			switch (_viFishMan->direction)
			{
			case FISHMAN_RIGHT:
				if (_viFishMan->currentFrameX > 2)
				{
					_dialogue->speechCreate(FISHMAN, _viFishMan->x - 60, _viFishMan->y - 60);

					_viFishMan->currentFrameX = 0;
				}
				break;
			case FISHMAN_LEFT:
				if (_viFishMan->currentFrameX < 0)
				{
					_dialogue->speechCreate(FISHMAN, _viFishMan->x - 60, _viFishMan->y - 60);

					_viFishMan->currentFrameX = 2;
				}
				break;
			}
			break;
			//DEATH 상태일 경우
		case FISHMAN_DEATH:
			_viFishMan->img = IMAGEMANAGER->findImage("fishManDie");
			switch (_viFishMan->direction)
			{
			case FISHMAN_RIGHT:
				if (_viFishMan->currentFrameX > 3)
				{
					_viFishMan->currentFrameX = 3;
					_viFishMan = _vFishMan.erase(_viFishMan);
				}
				break;
			case FISHMAN_LEFT:
				if (_viFishMan->currentFrameX < 0)
				{
					_viFishMan->currentFrameX = 0;
					_viFishMan = _vFishMan.erase(_viFishMan);
				}
				break;
			}
			break;
		}
	}
}
