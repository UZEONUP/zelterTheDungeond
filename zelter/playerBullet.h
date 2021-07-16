#pragma once
#include "gameNode.h"
#include <vector>

#define PI 3.141592



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
	float damage;
	

};
class playerBullet : public gameNode
{	

public:
	vector<tagPlayerBullet> _vBullet;
	vector<tagPlayerBullet>::iterator _viBullet;
	//tagPlayerBullet _playerBullet;
	const char* _image;
	float _range;
	int _bulletMax;
	int _count;
	int _guntype;
	float _disX, _disY;	
	

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed, int type);
	void move(int type, float x, float y);

	
	void removeBullet(int arrNum);
	//float getDamage() { return _playerBullet.damage; }

	void addBulletImages();

	

	vector<tagPlayerBullet>& getVBullet() { return _vBullet; }
	vector<tagPlayerBullet>::iterator getViBullet() { return _viBullet; }
	
	

};

