#pragma once
#include "singletonBase.h"

struct tagCamera
{
	RECT rc;
	float width, height;
	float x, y;
};

struct tagMap
{
	RECT rc;
	float width, height;
	float x, y;
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	tagCamera _camera;
	tagMap _map;

	float _x, _y;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setMapCamera(float x, float y);
	void setCamera(float x, float y);

	//���ͼ��� ���� ��
	void updateCamera(POINT mouse);		
	//�׳� �� �Լ� ��ü�� ���� ��
	void updateCamera(POINT mouse,POINT mouse2, int speed =1.f);	

	//�� �߾� ����
	void updateCamera(RECT& player, float playerX, float playerY);
	void updateCamera(float x, float y);
	void updateCameraH(float x, float y);
	void updateCameraH(RECT player , float ratio1, float ratio2);

	//�� ???? ��� ����
	void updateCamera(bool a);

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	tagCamera getCameraInfo() { return _camera; }
	void setLeft(float left) { _camera.rc.left = left; }
	void setTop(float top) { _camera.rc.left = top; }

	
	void mousePoint();
};

