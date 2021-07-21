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
	if (mouse2.x - _camera.width/8 < 0)
	{
		_x = 0;
	}
	else if (mouse2.x + _camera.width/8 > _map.width)
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
	else if (mouse2.y + _camera.height/8 > _map.height)
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

void cameraManager::updateCamera(bool a)
{
	//건들지말
}

void cameraManager::mousePoint()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << _ptMouse.x << "마우스 X" << endl;
		cout << _ptMouse.y << "마우스 Y" << endl;
	}
}
