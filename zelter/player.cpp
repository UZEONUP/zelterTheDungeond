#include "stdafx.h"
#include "player.h"
#include "playerStateIdle.h"
#include "playerBullet.h"
#include "ammoconda.h"
#include "eggNyang.h"
#include "bulletKing.h"
#include "niflheim.h"



HRESULT player::init()
{
	addIMAGES(); //이미지추가

	//ShowCursor(false);

	_player.img = IMAGEMANAGER->findImage("gunner_idle");
	_playerGun.img = IMAGEMANAGER->findImage("GUN1");
	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.shadow = RectMakeCenter(_player.x, _player.y, 100, 10);
	_playerGun.rc = RectMakeCenter(_player.x + 30, _player.y, _playerGun.img->getWidth(), _playerGun.img->getHeight());
	_player.currentFrameX = _player.currentFrameY = 0;
	_player.isDeath = false;
	_player.isDunGreed = false;
	_player.isHit = false;
	_player.isEnd = true;

	_player.maxHP = _player.currentHP = 100;
	_playerGun.x = _player.x;
	_playerGun.y = _player.y;
	_player.speed = 3.0f;
	_gunType = 0;
	_playerBullet = new playerBullet;
	_playerBullet->init();

	_enemy.x = WINSIZEX / 2;
	_enemy.y = WINSIZEY / 2;
	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, 100, 100);

	_mouse = IMAGEMANAGER->findImage("mouse");

	state = new playerStateIdle();

	_quickSlot = new quickSlot;
	_quickSlot->init();

	_progressBar = new progressBar();
	_progressBar->init(170, 25, 100, 30);
	_progressBar->setGauge(_player.currentHP, _player.maxHP);


	return S_OK;
}

void player::release()
{
}

void player::update()
{
	cout << _player.direction << "방향" << endl;
	tileDetect();
	_cameraX = CAMERAMANAGER->getX();
	_cameraY = CAMERAMANAGER->getY();
	_mapMouse.x = _ptMouse.x + CAMERAMANAGER->getX();
	_mapMouse.y = _ptMouse.y + CAMERAMANAGER->getY();

	//=================================================================

	RECT temp;
	_count++;

	inputHandle();
	state->update(this);
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.shadow = RectMakeCenter(_player.x, _player.rc.bottom, 50, 10);

	

	//플레이어 마우스 방향으로 바라보기
	_playerGun.angle = GetAngle(_playerGun.x, _playerGun.y, _mapMouse.x, _mapMouse.y) * (180 / PI);

	
	if (!_player.isDeath)
	{
		if (_playerGun.angle < 340 && 0 < _playerGun.angle) _player.direction = 0;
		if (_playerGun.angle < 110 && 70 < _playerGun.angle) _player.direction = 2;
		if (_playerGun.angle < 200 && 160 < _playerGun.angle) _player.direction = 1;
		if (_playerGun.angle < 290 && 250 < _playerGun.angle) _player.direction = 3;
		if (_playerGun.angle < 70 && 20 < _playerGun.angle) _player.direction = 5;
		if (_playerGun.angle < 160 && 110 < _playerGun.angle) _player.direction = 4;
		if (_playerGun.angle < 250 && 200 < _playerGun.angle) _player.direction = 7;
		if (_playerGun.angle < 310 && 290 < _playerGun.angle) _player.direction = 6;

		if (_player.isDunGreed)
		{
			if (_mapMouse.x < _player.x)_player.direction = 1;
			else _player.direction = 0;
		}
	}

	_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y, 100, 100);
	_playerGun.x = _player.x;
	_playerGun.y = _player.y;
	_playerBullet->move(_gunType, _enemy.x, _enemy.y);
	_playerBullet->update();
	_playerBullet->moveGrenadeBullet();

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

	if (KEYMANAGER->isOnceKeyDown(VK_F9))_player.currentHP -= 10;
	if (KEYMANAGER->isOnceKeyDown(VK_DELETE)) _player.isDunGreed = true;

	if (SCENEMANAGER->isCurrentScene("openWorld"))
	{
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth()*_openWorldSize, _player.img->getFrameHeight()*_openWorldSize);
	}

	//불렛 킹 총알 충돌
	if (SCENEMANAGER->isCurrentScene("bulletKing"))
	{
	
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth()*_bulletKingSize, _player.img->getFrameHeight()*_bulletKingSize);
		if (!_player.isHit && _player.isEnd)
		{
			for (int i = 0; i < _bulletKing->getBulletKingBullet()->getvBulletKingBullet1().size(); ++i)
			{
				if (IntersectRect(&temp, &_player.rc, &_bulletKing->getBulletKingBullet()->getvBulletKingBullet1()[i].rc))
				{
					_player.isHit = true;
					hitDamage(10.f);
				}
			}
			for (int i = 0; i < _bulletKing->getBulletKingBullet()->getvBulletKingBullet2().size(); ++i)
			{
				if (IntersectRect(&temp, &_player.rc, &_bulletKing->getBulletKingBullet()->getvBulletKingBullet2()[i].rc))
				{
					_player.isHit = true;
					hitDamage(50.f);
				}
			}
			for (int i = 0; i < _bulletKing->getBulletKingBullet()->getvBulletKingBullet3().size(); ++i)
			{
				if (IntersectRect(&temp, &_player.rc, &_bulletKing->getBulletKingBullet()->getvBulletKingBullet3()[i].rc))
				{
					_player.isHit = true;
					hitDamage(90.f);
				}
			}
		}
	}
	
	//아모콘다 총알 충돌
	if (SCENEMANAGER->isCurrentScene("ammoconda"))
	{
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth()*_ammoCondaSize, _player.img->getFrameHeight()*_ammoCondaSize);
		
		for (int i = 0; i < _ammoconda->getBAmmocondaBullet()->getVammoCondaBullet1().size(); i++)
		{
			if (IntersectRect(&temp, &_player.rc, &_ammoconda->getBAmmocondaBullet()->getVammoCondaBullet1()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
			if (IntersectRect(&temp, &_player.rc, &_ammoconda->getBAmmocondaBullet()->getVammoCondaBullet2()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
			if (IntersectRect(&temp, &_player.rc, &_ammoconda->getBAmmocondaBullet()->getVipotBullet()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
		}
	}

	//니플헤임 총알 충돌
	if (SCENEMANAGER->isCurrentScene("niflheim"))
	{
		for (int i = 0; i < _niflheim->getNiflheim().icePillar->getVbullet().size(); i++)
		{
			if (IntersectRect(&temp, &_player.rc, &_niflheim->getNiflheim().icePillar->getVbullet()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
		}
		for (int i = 0; i < _niflheim->getNiflheim().iceSpear->getVIceSpear().size(); i++)
		{
			if (IntersectRect(&temp, &_player.rc, &_niflheim->getNiflheim().iceSpear->getVIceSpear()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
		}
		for (int i = 0; i < _niflheim->getNiflheim().iceicle->getVIcicle().size(); i++)
		{
			if (IntersectRect(&temp, &_player.rc, &_niflheim->getNiflheim().iceicle->getVIcicle()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
		}
	}


	//에그냥 총알 충돌
	if (SCENEMANAGER->isCurrentScene("eggNyang"))
	{
		for (int i = 0; i < _eggNyang->getEggNyang().bullet->getEggNyangVBullet().size(); i++)
		{
			if (IntersectRect(&temp, &_player.rc, &_eggNyang->getEggNyang().bullet->getEggNyangVBullet()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
			if (IntersectRect(&temp, &_player.rc, &_eggNyang->getEggNyang().lazer->getEggNyangVLazer()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
			if (IntersectRect(&temp, &_player.rc, &_eggNyang->getEggNyang().sword->getEggNyangVSword()[i].rc))
			{
				_player.isHit = true;
				hitDamage(10.f);
			}
			
		}
	}


	_quickSlot->update();

	if (_quickSlot->getQuickslotisOn(0))
	{
		_gunType = NORMAL;
	}
	if (_quickSlot->getQuickslotisOn(1))
	{
		_gunType = SHOTGUN;
	}
	if (_quickSlot->getQuickslotisOn(2))
	{
		_gunType = HOMING;
	}
	if (_quickSlot->getQuickslotisOn(3))
	{
		_gunType = GRENADE;
	}
	if (_quickSlot->getQuickslotisOn(4))
	{
		_gunType = FLAMETHROWER;
	}


	_progressBar->setGauge(_player.currentHP, _player.maxHP);
	_progressBar->update();

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

	if (_player.direction == 2 || _player.direction == 4 || _player.direction == 5)
	{
		if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
		{
			if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 1.f, -1.f, _playerGun.angle);
			_player.img->frameRender2(_player.rc.left, _player.rc.top, _player.currentFrameX, 0);
			
		}
		else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
		{
			if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 1.f, 1.f, _playerGun.angle);
			_player.img->frameRender2(_player.rc.left, _player.rc.top, _player.currentFrameX, 0);
		}
	}
	else
	{
		if (_player.direction == 1 || _player.direction == 3 || _player.direction == 4 || _player.direction == 7)
		{
			_player.img->frameRender2(_player.rc.left, _player.rc.top, _player.currentFrameX, 0);
			if (!_player.isDeath)_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 1.f, -1.f, _playerGun.angle);
		}
		else if (_player.direction == 0 || _player.direction == 2 || _player.direction == 5 || _player.direction == 6)
		{
			_player.img->frameRender2(_player.rc.left, _player.rc.top, _player.currentFrameX, 0);
			if (!_player.isDeath)
				_playerGun.img->render(_playerGun.rc.left - _cameraX, _playerGun.rc.top - _cameraY, 1.f, 1.f, _playerGun.angle);
		}
	}
	_progressBar->render();
	_quickSlot->render();
	_mouse->render(_ptMouse.x - 7, _ptMouse.y - 5);

	for (int i = 0; i < 8; ++i)
	{
		D2DRENDER->DrawRectangle(_tileIdx[i], D2DDEFAULTBRUSH::Red);
	}

}

void player::addIMAGES()
{
	IMAGEMANAGER->addImage("GUN1", L"무기/기본.png");
	IMAGEMANAGER->addImage("GUN2", L"무기/산탄.png");
	IMAGEMANAGER->addImage("GUN3", L"무기/유도총.png");
	IMAGEMANAGER->addImage("GUN4", L"무기/수류탄.png");
	IMAGEMANAGER->addImage("GUN5", L"무기/화염방사.png");
	IMAGEMANAGER->addImage("mouse", L"무기/마우스.png");

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

	IMAGEMANAGER->addFrameImage("gunner_left_jump", L"STATE/JUMP/gunner_left_jump.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_jump", L"STATE/JUMP/gunner_right_jump.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_left_downjump", L"STATE/JUMP/gunner_left_downjump.png", 6, 1);
	IMAGEMANAGER->addFrameImage("gunner_right_downjump", L"STATE/JUMP/gunner_right_downjump.png", 6, 1);


	IMAGEMANAGER->addFrameImage("gunner_death", L"STATE/DEATH/gunner_death.png", 15, 1);

	IMAGEMANAGER->addImage("bullet1", L"bullets/bullet1.png");
	IMAGEMANAGER->addImage("bullet2", L"bullets/bullet2.png");
	IMAGEMANAGER->addImage("flame", L"bullets/flame.png");
	IMAGEMANAGER->addImage("backpack", L"UI/backpack.png");
	IMAGEMANAGER->addImage("quickslotback", L"UI/quickslotback.png");
	IMAGEMANAGER->addImage("quickslotfront", L"UI/quickslotfront.png");
	IMAGEMANAGER->addImage("quickslotbase", L"UI/quickslotbase.png");

	IMAGEMANAGER->addImage("hpback", L"UI/hpback.png");
	IMAGEMANAGER->addImage("hpfront", L"UI/hpfront.png");


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

void player::tileDetect()
{
	if (SCENEMANAGER->getSceneName() == "openWorld")
	{

		RECT rcCollision;	//가상의 충돌판정 렉트를 하나 생성해주자


		int	tileIndex[2];	//타일 검출에 필요한 인덱스
		int tileX, tileY;	//플레이어가 밟고 있는 타일의 인덱스

		//가상의 판정렉트에 현재 렉트를 대입해주자
		rcCollision = _player.rc;

		rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

		//STEP 3
		////판정렉트를 사알짝 깍아주자
		/*rcCollision.left += 4;
		rcCollision.top += 4;
		rcCollision.right -= 4;
		rcCollision.bottom -= 4;*/

		tileX = rcCollision.left / 64;
		tileY = rcCollision.top / 64;


		//STEP 04
		//가장 메인이지 싶으요
		//해당 방향일때 레프트 탑을 기준으로 앞타일과 그 옆타일을 계산해준다

		/*
		-----------------
		4	|	2	|	5
		-----------------
		1	| player|	0
		-----------------
		7	|	3	|	6
		*/
		switch (_player.movingDirection)
		{
		case 4:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX + (tileY*TILEY);
			break;
		case 2:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 5:
			tileIndex[0] = (tileX)+(tileY * TILEX);
			tileIndex[1] = tileX + 1 + (tileY * TILEX);
			break;
		case 1:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = tileX + (tileY + 1)*TILEX;
			break;
		case 0:
			tileIndex[0] = tileX + 1 + tileY * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
			break;
		case 7:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
			break;
		case 3:
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
			break;
		case 6:
			tileIndex[0] = tileX + 1 + (tileY * TILEX);
			tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
			break;
		}

		for (int i = 0; i < 2; ++i)
		{
			//if (_inGame->getTileAtt()[tileIndex[i]] != NONEMOVE)continue;
			RECT rc;

			if (((_inGame->getTileAtt()[tileIndex[i]] == NONEMOVE)) &&
				IntersectRect(&rc, &_inGame->getTile()[tileIndex[i]].checkRect, &rcCollision))
			{
				switch (_player.movingDirection)
				{
				case 1:
					_player.rc.left = _inGame->getTile()[tileIndex[i]].checkRect.right;
					_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;

					break;
				case 2:
					_player.rc.top = _inGame->getTile()[tileIndex[i]].checkRect.bottom;
					_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				case 0:
					_player.rc.right = _inGame->getTile()[tileIndex[i]].checkRect.left;
					_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;
					break;
				case 3:
					_player.rc.bottom = _inGame->getTile()[tileIndex[i]].checkRect.top;
					_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				}
			}
		}
		for (int i = 0; i < 2; ++i)
		{
			_tileIdx[i] = RectMake(_inGame->getTile()[tileIndex[i]].rc.left, _inGame->getTile()[tileIndex[i]].rc.top, 64, 64);
		}
		//_player.rc = rcCollision;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}

	//여기가 제일 중요한 부분이 아닌가 싶습니다
}

float player::hitDamage(float damage)
{
	return _player.currentHP -= damage;
}




