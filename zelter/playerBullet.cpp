#include "stdafx.h"
#include "playerBullet.h"

HRESULT playerBullet::init(const char* imageName, int bulletMax, float range)
{
	addBulletImages();
	_image = imageName;
	_bulletMax = bulletMax;
	_range = range;

	

	return S_OK;
}

void playerBullet::release()
{
}

void playerBullet::update()
{

}

void playerBullet::render()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(_viBullet->x, _viBullet->y);
		if(KEYMANAGER->isToggleKey(VK_TAB))
		D2DRENDER->DrawRectangle(_viBullet->rc, D2DRenderer::DefaultBrush::White, 1.f);
	}
}

void playerBullet::fire(float x, float y, float angle, float speed, int type)
{
	switch (type)
	{
		tagPlayerBullet bullet;
		ZeroMemory(&bullet, sizeof(tagPlayerBullet));
	case NORMAL:
		if (_bulletMax < _vBullet.size()) return;
		bullet.img = IMAGEMANAGER->findImage(_image);
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
			if (_bulletMax < _vBullet.size()) return;
			bullet.img = IMAGEMANAGER->findImage(_image);
			bullet.speed = speed;
			bullet.radius = bullet.img->getWidth() / 2;
			bullet.x = bullet.fireX = cosf(angle) * 50 + x;
			bullet.y = bullet.fireY = -sinf(angle) * 50 + y;
			bullet.angle = angle + (i * 0.1f);
			bullet.damage = 10;
			bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
			_vBullet.push_back(bullet);
		}
		break;

	case HOMING:
		if (_bulletMax < _vBullet.size()) return;
		bullet.img = IMAGEMANAGER->findImage(_image);
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 50 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 70 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBullet.push_back(bullet);
		break;


	case GRENADE:
		if (_bulletMax < _vBullet.size()) return;
		bullet.img = IMAGEMANAGER->findImage(_image);
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 70 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 100 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBullet.push_back(bullet);
		break;

	case FLAMETHROWER:
		if (_bulletMax < _vBullet.size()) return;
		bullet.img = IMAGEMANAGER->findImage(_image);
		bullet.speed = speed;
		bullet.radius = bullet.img->getWidth() / 2;
		bullet.x = bullet.fireX = cosf(angle) * 50 + x;
		bullet.y = bullet.fireY = -sinf(angle) * 80 + y;
		bullet.angle = angle;
		bullet.damage = 10;
		bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getWidth(), bullet.img->getHeight());
		_vBullet.push_back(bullet);
		break;
	}
}


void playerBullet::move(int type, float x, float y)
{	
	if (type == HOMING)
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		{
			if (GetDistance(_viBullet->x, _viBullet->y, x, y) <= 100)
			{
				_disX = x - _viBullet->x;
				_disY = y - _viBullet->y;

				_viBullet->angle = -atan2f(_disY, _disX);
				_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
				_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
				_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
					_viBullet->img->getWidth(),
					_viBullet->img->getHeight());
			}
			else
			{
				_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
				_viBullet->y += -sinf(_viBullet->angle )* _viBullet->speed;
				_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
					_viBullet->img->getWidth(),
					_viBullet->img->getHeight());
			}
			if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
			{
				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}
	}

	/*else if (type == GRENADE)
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		{
			_viBullet->x += cosf(_viBullet->angle) * (_viBullet->speed + _viBullet->power);
			_viBullet->y += -sinf(_viBullet->angle) * (_viBullet->speed+_viBullet->power);
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->GetWidth(),
				_viBullet->img->GetHeight());

			if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
			{
				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}
	}*/

	else
	{
		for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		{
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
				_viBullet->img->getWidth(),
				_viBullet->img->getHeight());

			if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
			{
				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}

	}
}

void playerBullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void playerBullet::addBulletImages()
{
	IMAGEMANAGER->addImage("bullet1", L"bullets/bullet1.png");
	IMAGEMANAGER->addImage("bullet2", L"bullets/bullet2.png");
}
