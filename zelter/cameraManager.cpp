#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
	_camera.x = WINSIZEX / 2;
	_camera.y = WINSIZEY / 2;

	_camera.width = WINSIZEX;
	_camera.height = WINSIZEY;

	_camera.rc = RectMakeCenter(_camera.x, _camera.y,
		_camera.width, _camera.height);

	_x = 0;
	_y = 0;

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{

}

void cameraManager::render()
{
	D2DRENDER->DrawRectangle(_camera.rc, D2DDEFAULTBRUSH::Red, 5.f);
}

void cameraManager::setMapCamera(float x, float y)
{
	_map.width = x;
	_map.height = y;
}

void cameraManager::setCamera(float x, float y)
{
	_camera.width = x;
	_camera.height = y;
}

void cameraManager::updateCamera(POINT mouse)
{
	if (mouse.x - _camera.width / 2 < 0)
	{
		_x = 0;
	}
	else if (mouse.x + _camera.width / 2 > _map.width)
	{
		_x = _map.width;
	}
	else
	{
		_x = mouse.x - _camera.width / 2;
	}

	if (mouse.y - _camera.height / 2 < 0)
	{
		_y = 0;
	}
	else if (mouse.y + _camera.height / 2 > _map.height)
	{
		_y = _map.height;
	}
	else
	{
		_y = mouse.y - _camera.height / 2;
	}
}

void cameraManager::updateCamera(POINT mouse, POINT mouse2, int speed)
{
	//마우스(절대 좌표)
	if (mouse2.x - _camera.width / 8 < 0)
	{
		_x = 0;
	}
	else if (mouse2.x + _camera.width / 8 > _map.width)
	{
		_x = _map.width - _camera.width;
	}
	else
	{
		if (0 < mouse.x && mouse.x < WINSIZEX / 8)
		{
			_x -= speed;
		}
		if (WINSIZEX - (WINSIZEX / 8) < mouse.x && mouse.x < WINSIZEX)
		{
			_x += speed;
		}
	}
	if (mouse2.y - _camera.height / 8 < 0)
	{
		_y = 0;
	}
	else if (mouse2.y + _camera.height / 8 > _map.height)
	{
		_y = _map.height - _camera.height;
	}
	else
	{
		if (0 < mouse.y && mouse.y < WINSIZEY / 8)
		{
			_y -= speed;
		}
		if (WINSIZEY - (WINSIZEY / 8) < mouse.y && mouse.y < WINSIZEY)
		{
			_y += speed;
		}
	}
}

void cameraManager::updateCamera(POINT mouse, POINT mouse2, float x, float y)
{
	//마우스(절대 좌표)
	if (mouse2.x - _camera.width / 8 < 0)
	{
		_x = 0;
	}
	else if (mouse2.x + _camera.width / 8 > _map.width)
	{
		_x = _map.width - _camera.width;
	}
	else
	{
		if (x - _camera.width *0.5 < 0)
		{
			_x = 0;
		}
		else
		{
			if (0 < mouse.x && mouse.x < WINSIZEX / 2)
			{
				_x -= (WINSIZEX *0.5 - mouse.x);
				if (mouse.x < WINSIZEX*0.3)_x = x - (_camera.width*0.7);
				if (_x < 0)	_x = 0;
			}
			else if (WINSIZEX - (WINSIZEX / 2) < mouse.x && mouse.x < WINSIZEX)
			{
				_x += (mouse.x - WINSIZEX * 0.5);
				if (mouse.x > WINSIZEX - WINSIZEX * 0.3)_x = x - (_camera.width*0.3);
				if (_x > _map.width- _camera.width)_x = _map.width - _camera.width;
				if (_x < 0)_x = 0;
			}
		}
	}
	if (mouse2.y - _camera.height / 8 < 0)
	{
		_y = 0;
	}
	else if (mouse2.y + _camera.height / 8 > _map.height)
	{
		_y = _map.height - _camera.height;
	}
	else
	{
		if (y - _camera.height *0.5< 0)
		{
			_y = 0;
		}
		else
		{
			if (0 < mouse.y && mouse.y < WINSIZEY / 2)
			{
				_y -= (WINSIZEY *0.5 - mouse.y);
				if (mouse.y < WINSIZEY*0.3)_y = y - (_camera.height*0.7);
				if (_y < 0)	_y = 0;
			}
			else if (WINSIZEY - (WINSIZEY / 2) < mouse.y && mouse.y < WINSIZEY)
			{
				_y += (mouse.y - WINSIZEY * 0.5);
				if (mouse.y > WINSIZEY - WINSIZEY * 0.3)_y = y - (_camera.height*0.3);
				if (_y > _map.height- _camera.height)_y = _map.height - _camera.height;
				if (_y < 0)_y = 0;
			}
		}
	}
}

void cameraManager::updateCamera(RECT& player, float playerX, float playerY)
{
	//==========================================
	//           가로 영역 이다  
	if (playerX - _camera.width / 2 < 0)
	{
		_camera.rc.left = 0;
	}
	else if (playerX + _camera.width / 2 > _map.width)
	{

		_camera.rc.left = _map.width - _camera.width;
	}
	else
	{
		_camera.rc.left = (playerX - WINSIZEX * 0.5);
		_camera.rc.right = _camera.rc.left + _camera.width;
	}
	//           가로 영역 이다 
	//========================================== 

	//==========================================
	//           세로 영역 이다  
	if (playerY - _camera.height / 2 < 0)
	{
		_camera.rc.top = 0;
	}
	else if (playerY + _camera.height / 2 > _map.height)
	{
		_camera.rc.top = _map.height - _camera.height;
	}
	else
	{
		_camera.rc.top = playerY - _camera.height / 2;
	}
	//           세로 영역 이다 
	//==========================================
}

void cameraManager::updateCamera(float x, float y)
{
	if (x - _camera.width * 0.5 < 0)
	{
		x = 0;

	}
	else if (x + _camera.width * (1 - 0.5) > _map.width)
	{
		x = _map.width - _camera.width;

	}
	else
	{
		x -= _camera.width*0.5;

	}

	//Y축 (상, 하)

	if (y - _camera.height * 0.5 < 0)
	{
		y = 0;
	}
	else if (y + _camera.height * (1 - 0.5) > _map.height)
	{
		y = _map.height - _camera.height;
	}
	else
	{
		y -= _camera.height*0.5;
	}

	//갱신
	_x = x;
	_y = y;

}

void cameraManager::updateCameraH(float x, float y)
{
	if (x - _camera.width * 0.5 < 0)
	{
		x = 0;

	}
	else if (x + _camera.width * (1 - 0.5) > _map.width)
	{
		x = _map.width - _camera.width;

	}
	else
	{
		x -= _camera.width*0.5;

	}

	//Y축 (상, 하)

	if (y - _camera.height * 0.5 < 0)
	{
		y = 0;
	}
	else if (y + _camera.height * (1 - 0.5) > _map.height)
	{
		y = _map.height - _camera.height;
	}
	else
	{
		y -= _camera.height*0.5;
	}

	//갱신
	_x = x;
	_y = y;
}

void cameraManager::updateCameraW(RECT player, float x, float y, float ratio1, float ratio2)
{
	//플레이어가 맵 왼쪽 끝에 오면
	if (x - (_camera.width*ratio1) < 0)
	{
		_x = 0;
	}
	//플레이어가 맵 오른쪽 끝에 오면
	else if (x + (_camera.width* ratio1) > _map.width)
	{
		_x = _map.width - _camera.width;
	}
	else
	{
		if (x - (_camera.width * ratio2) < 0)
		{
			_x = 0;
		}
		else if (x > (_camera.width * ratio2))
		{
			_x = x - (_camera.width*ratio2);
		}
		else
		{

			_x = x - _camera.width*0.5;
		}
	}

	if (y - (_camera.height*ratio1) < 0)
	{
		_y = 0;
	}
	else if (y + (_camera.height* ratio1) > _map.height)
	{
		_y = _map.height - _camera.height;
	}
	else
	{
		if (y - (_camera.height * ratio2) < 0)
		{
			_y = 0;
		}
		else if (y > (_camera.height* ratio2))
		{
			_y = y - (_camera.height*ratio2);
		}
		else
		{
			_y = y - _camera.height*0.5;
		}
	}
}

void cameraManager::updateCameraH(RECT player, float ratioX1, float ratioY1, float ratioX2, float ratioY2)
{
	if (player.left - (_camera.width*ratioX1) < 0)
	{
		_x = 0;
	}
	else if (player.right + (_camera.width*ratioX1) > _map.width)
	{
		_x = _map.width - _camera.width;
	}
	else
	{
		if (ratioX1 > 0 && ratioX1 < 0.5f)
		{
			if (player.left < _x + ratioX1 * WINSIZEX)
			{
				_x = player.left - ratioX1 * WINSIZEX;
			}
		}

		if (ratioX2 > 0.5f && ratioX2 < 1.0f)
		{
			if (player.right > _x + ratioX2 * WINSIZEX)
			{
				_x = player.right - ratioX2 * WINSIZEX;
			}
		}
	}


	if (player.top - (_camera.height*ratioX1) < 0)
	{
		_y = 0;
	}
	else if (player.bottom + (_camera.height*ratioX1) > _map.height)
	{
		_y = _map.height - _camera.height;
	}
	else
	{
		if (ratioY1 > 0 && ratioY1 < 0.5f)
		{
			if (player.top < _y + ratioY1 * WINSIZEY)
			{
				_y = player.top - ratioY1 * WINSIZEY;
			}
		}

		if (ratioY2 > 0.5f && ratioY2 < 1.0f)
		{
			if (player.bottom > _y + ratioY2 * WINSIZEY)
			{
				_y = player.bottom - ratioY2 * WINSIZEY;
			}
		}
	}
}

void cameraManager::updateCamera(bool a)
{
	//건들지말
}

void cameraManager::mousePoint()
{
	/*if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << _ptMouse.x << "마우스 X" << endl;
		cout << _ptMouse.y << "마우스 Y" << endl;
	}*/
}
