#pragma once
#include "gameNode.h"
#include <vector>

#define PI 3.141592


class player;

//typedef struct SHAPE
//{
//	double left, top, width, height, degreeAngle;
//};


enum GUNTYPE
{
	NORMAL,
	SHOTGUN,
	HOMING,
	GRENADE,
	FLAMETHROWER
};

struct tagPlayerBullet
{
	RECT rc;
	image* img;
	
	float x, y;
	float fire;
	float angle;
	float speed;
	float power;
	float radius;
	float fireX, fireY;
	bool isFire;
	int count;
	int currentFrameX;
	int currentFrameY;
	int index;
	int bulletMax;
	float range;
	float damage;
	float gravity;
};


class playerBullet : public gameNode
{	

public:
	vector<tagPlayerBullet> _vBullet;
	vector<tagPlayerBullet>::iterator _viBullet;


	vector<tagPlayerBullet> _vBulletS;
	vector<tagPlayerBullet>::iterator _viBulletS;

	vector<tagPlayerBullet> _vBulletH;
	vector<tagPlayerBullet>::iterator _viBulletH;

	vector<tagPlayerBullet> _vBulletG;
	vector<tagPlayerBullet>::iterator _viBulletG;

	vector<tagPlayerBullet> _vBulletF;
	vector<tagPlayerBullet>::iterator _viBulletF;

	//tagPlayerBullet _playerBullet;
	const char* _image;
	float _range;
	int _bulletMax;
	int _count;
	int _guntype;
	float _disX, _disY;	
	
	player* _player;

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed, int type, float power);
	void move(int type, float x, float y);

	
	//float getDamage() { return _playerBullet.damage; }

	

	float getPower() { return _viBullet->power; }
	void setPower(float power) { _viBullet->power = power; }

	

	vector<tagPlayerBullet>& getVBullet() { return _vBullet; }
	vector<tagPlayerBullet>::iterator getViBullet() { return _viBullet; }


	vector<tagPlayerBullet>& getVBulletS() { return _vBulletS; }
	vector<tagPlayerBullet>::iterator getViBulletS() { return _viBulletS; }

	vector<tagPlayerBullet>& getVBulletH() { return _vBulletH; }
	vector<tagPlayerBullet>::iterator getViBulletH() { return _viBulletH; }

	vector<tagPlayerBullet>& getVBulletG() { return _vBulletG; }
	vector<tagPlayerBullet>::iterator getViBulletG() { return _viBulletG; }

	vector<tagPlayerBullet>& getVBulletF() { return _vBulletF; }
	vector<tagPlayerBullet>::iterator getViBulletF() { return _viBulletF; }

	
	void setPlayerLink(player* player) { _player = player; }

};

