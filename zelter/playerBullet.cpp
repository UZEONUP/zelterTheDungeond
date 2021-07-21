#include "stdafx.h"
#include "playerBullet.h"

#include "player.h"

HRESULT playerBullet::init()
{
	_player = new player;

	
	return S_OK;
}

void playerBullet::release()
{
}

void playerBullet::update()
{
	for (_viBulletG = _vBulletG.begin(); _viBulletG != _vBulletG.end(); ++_viBulletG)
	{

		_viBulletG->gravity += 0.03;
		break;
	}

	
}

void playerBullet::render()
{
	

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(_viBullet->x, _viBullet->y, 1.f, 1.f, _viBullet->angle * 180 / PI, _viBullet->img->getWidth() / 2, _viBullet->img->getHeight() / 2);
		if(KEYMANAGER->isToggleKey(VK_TAB))
		D2DRENDER->DrawRectangle(_viBullet->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}

	

	for (_viBulletS = _vBulletS.begin(); _viBulletS != _vBulletS.end(); ++_viBulletS)
	{
		_viBulletS->img->render(_viBulletS->x, _viBulletS->y,1.f,1.f,_viBulletS->angle *180/PI,_viBulletS->img->getWidth()/2, _viBulletS->img->getHeight()/2);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletS->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}



	for (_viBulletH = _vBulletH.begin(); _viBulletH != _vBulletH.end(); ++_viBulletH)
	{
		_viBulletH->img->render(_viBulletH->x, _viBulletH->y,1.f, 1.f, _viBulletH->angle * 180 / PI, _viBulletH->img->getWidth() / 2, _viBulletH->img->getHeight() / 2);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletH->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}


	for (_viBulletG = _vBulletG.begin(); _viBulletG != _vBulletG.end(); ++_viBulletG)
	{
		_viBulletG->img->render(_viBulletG->x, _viBulletG->y);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletG->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}


	for (_viBulletF = _vBulletF.begin(); _viBulletF != _vBulletF.end(); ++_viBulletF)
	{
		_viBulletF->img->render(_viBulletF->x, _viBulletF->y);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			D2DRENDER->DrawRectangle(_viBulletF->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}


}

void playerBullet::fire(float x, float y, float angle, float speed, int type, float power)
{
	switch (type)
	{
		tagPlayerBullet bullet;
		ZeroMemory(&bullet, sizeof(tagPlayerBullet));
	case NORMAL:
		bullet.img = IMAGEMANAGER->findImage("bullet2");
		bullet.range = WINSIZEX;
		bullet.bulletMax = 50;
		if (bullet.bulletMax < _vBullet.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle)* 30 + x;
		bullet.y = bullet.fireY = -sinf(angle)* 30 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBullet.push_back(bullet);
		break;

	case SHOTGUN:
		for (int i = 0; i < 4; i++)
		{
			bullet.img = IMAGEMANAGER->findImage("bullet1");
			bullet.range = WINSIZEX;
			bullet.bulletMax = 50;
			if (bullet.bulletMax < _vBulletS.size()) return;
			bullet.speed = speed;
			bullet.radius = bullet.img->getWidth() / 2;
			bullet.x = bullet.fireX = cosf(angle) * 50 + x;
			bullet.y = bullet.fireY = -sinf(angle) * 50 + y;
			bullet.angle = angle + (i * 0.1f);
			bullet.damage = 10;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
			_vBulletS.push_back(bullet);
		}
		break;

	case HOMING:
		bullet.img = IMAGEMANAGER->findImage("bullet2");
		bullet.range = WINSIZEX;
		bullet.bulletMax = 50;
		if (bullet.bulletMax < _vBulletH.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 50 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 70 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletH.push_back(bullet);
		break;


	case GRENADE:
		bullet.img = IMAGEMANAGER->findImage("GUN4");
		bullet.range = 250;
		bullet.bulletMax = 50;
		if (bullet.bulletMax < _vBulletG.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 20 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 100 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.power = power;
		bullet.gravity = 0;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletG.push_back(bullet);
		break;

	case FLAMETHROWER:
		bullet.img = IMAGEMANAGER->findImage("flame");
		bullet.range = 300;
		bullet.bulletMax = 100;
		if (bullet.bulletMax < _vBulletF.size()) return;
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 50 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 80 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBulletF.push_back(bullet);
		break;
	}
}


void playerBullet::move(int type, float x, float y)
{	
	if (_vBulletH.size() != 0)
	{
		for (_viBulletH = _vBulletH.begin(); _viBulletH != _vBulletH.end();)
		{
			if (GetDistance(_viBulletH->x, _viBulletH->y, x, y) <= 100)
			{
				_disX = x - _viBulletH->x;
				_disY = y - _viBulletH->y;

				_viBulletH->angle = -atan2f(_disY, _disX);
				_viBulletH->x += cosf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->y += -sinf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->rc = RectMakeCenter(_viBulletH->x, _viBulletH->y,
					_viBulletH->img->getWidth(),
					_viBulletH->img->getHeight());
			}
			else
			{
				_viBulletH->x += cosf(_viBulletH->angle) * _viBulletH->speed;
				_viBulletH->y += -sinf(_viBulletH->angle )* _viBulletH->speed;
				_viBulletH->rc = RectMakeCenter(_viBulletH->x, _viBulletH->y,
					_viBulletH->img->getWidth(),
					_viBulletH->img->getHeight());
			}
			if (_viBulletH->range < GetDistance(_viBulletH->fireX, _viBulletH->fireY, _viBulletH->x, _viBulletH->y))
			{
				_viBulletH = _vBulletH.erase(_viBulletH);
			}
			else ++_viBulletH;
		}
	}

	if (_vBulletG.size() != 0)
	{
		for (_viBulletG = _vBulletG.begin(); _viBulletG != _vBulletG.end(); ++_viBulletG)
		{

			/*if (_ptMouse.y > _player->getPlayer().y)
			{
				_viBulletG->x += cosf(_viBulletG->angle) * _viBulletG->speed;
				_viBulletG->y += -sinf(_viBulletG->angle) * (_viBulletG->speed + _viBulletG->power);
				_viBulletG->power -= _viBulletG->gravity;
				_viBulletG->gravity += 0.5;
				_viBulletG->rc = RectMakeCenter(_viBulletG->x, _viBulletG->y,
					_viBulletG->img->getWidth(),
					_viBulletG->img->getHeight());
			}
			else*/
			{ _viBulletG->x += cosf(_viBulletG->angle) * _viBulletG->speed;
			_viBulletG->y -= -sinf(_viBulletG->angle) * (_viBulletG->speed + _viBulletG->power);
			_viBulletG->power -= _viBulletG->gravity;
			_viBulletG->gravity += 0.5;
			_viBulletG->rc = RectMakeCenter(_viBulletG->x, _viBulletG->y,
				_viBulletG->img->getWidth(),
				_viBulletG->img->getHeight());
			}
			
		
			if (_viBulletG->range < GetDistance(_viBulletG->fireX, _viBulletG->fireY, _viBulletG->x, _viBulletG->y))
			{
				_viBulletG->gravity = 0;
				_viBulletG->speed = 0;
				_viBulletG->power = 0;
			}
		}
	}

	if (_vBulletF.size() != 0)
	{
		for (_viBulletF = _vBulletF.begin(); _viBulletF != _vBulletF.end();)
		{
			_viBulletF->x += cosf(_viBulletF->angle) * (_viBulletF->speed/2);
			_viBulletF->y += -sinf(_viBulletF->angle) * (_viBulletF->speed/2);
			_viBulletF->rc = RectMakeCenter(_viBulletF->x, _viBulletF->y,
				_viBulletF->img->getWidth(),
				_viBulletF->img->getHeight());

			if (_viBulletF->range < GetDistance(_viBulletF->fireX, _viBulletF->fireY, _viBulletF->x, _viBulletF->y))
			{
				_viBulletF = _vBulletF.erase(_viBulletF);
			}
			else ++_viBulletF;
		}

	}
	if (_vBullet.size() != 0)
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		{
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->getWidth(),
				_viBullet->img->getHeight());

			//_range += _viBullet->power;

			if (_viBullet->range < GetDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
			{
				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}

	}
	if (_vBulletS.size() != 0)
	{
	for (_viBulletS = _vBulletS.begin(); _viBulletS != _vBulletS.end();)
	{
		_viBulletS->x += cosf(_viBulletS->angle) * _viBulletS->speed;
		_viBulletS->y += -sinf(_viBulletS->angle) * _viBulletS->speed;
		_viBulletS->rc = RectMakeCenter(_viBulletS->x, _viBulletS->y,
			_viBulletS->img->getWidth(),
			_viBulletS->img->getHeight());

		//_range += _viBullet->power;

		if (_viBulletS->range < GetDistance(_viBulletS->fireX, _viBulletS->fireY, _viBulletS->x, _viBulletS->y))
		{
			_viBulletS = _vBulletS.erase(_viBulletS);
		}
		else ++_viBulletS;
	}

	}
}



