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
	FLAMETHROWER,
	GRENADEBULLET
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
	vector<tagPlayerBullet> _vBulletN;
	vector<tagPlayerBullet>::iterator _viBulletN;


	vector<tagPlayerBullet> _vBulletS;
	vector<tagPlayerBullet>::iterator _viBulletS;

	vector<tagPlayerBullet> _vBulletH;
	vector<tagPlayerBullet>::iterator _viBulletH;

	vector<tagPlayerBullet> _vBulletBomb;
	vector<tagPlayerBullet>::iterator _viBulletBomb;

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
	void releaseBullet(int index);
	void releaseS(int index);
	void releaseH(int index);
	void releaseBomb(int index);
	void releaseG(int index);
	void releaseF(int index);

	void update();
	void render();

	void fire(float x, float y, float angle, float speed, int type, float power);
	void move(int type, float x, float y);

	
	//float getDamage() { return _playerBullet.damage; }

	

	float getPower() { return _viBulletN->power; }
	void setPower(float power) { _viBulletN->power = power; }
	void setplayerBulletCount(int count) { _viBulletBomb->count = count; }
	

	vector<tagPlayerBullet> getVBulletN() { return _vBulletN; }
	vector<tagPlayerBullet>::iterator getViBulletN() { return _viBulletN; }


	vector<tagPlayerBullet> getVBulletS() { return _vBulletS; }
	vector<tagPlayerBullet>::iterator getViBulletS() { return _viBulletS; }

	vector<tagPlayerBullet> getVBulletH() { return _vBulletH; }
	vector<tagPlayerBullet>::iterator getViBulletH() { return _viBulletH; }

	vector<tagPlayerBullet> getVBulletBomb() { return _vBulletBomb; }
	vector<tagPlayerBullet>::iterator getViBulletBomb() { return _viBulletBomb; }

	vector<tagPlayerBullet> getVBulletG() { return _vBulletG; }
	vector<tagPlayerBullet>::iterator getViBulletG() { return _viBulletG; }

	vector<tagPlayerBullet> getVBulletF() { return _vBulletF; }
	vector<tagPlayerBullet>::iterator getViBulletF() { return _viBulletF; }

	
	void setPlayerLink(player* player) { _player = player; }

};

