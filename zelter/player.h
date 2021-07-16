#pragma once
#include "gameNode.h"
#include "playerState.h"
#include "playerBullet.h"


struct tagPlayer
{
	image* img;
	RECT rc;
	RECT shadow;
	
	int currentHP;
	int maxHP;
	int direction;
	float x, y;
	float speed;
	float angle;
	float jumpPower; // 던그리드 보스 씬에서 사용
	
	int currentFrameX;
	int currentFrameY;

	bool isHit;
	bool isEnd;
};
struct tagPlayerGun
{
	image* img;
	RECT rc;

	float x, y;
	float angle;
};

struct tagEnemy
{
	RECT rc;
	float x, y;
};


class stageManager;

class player : public gameNode
{
private:

	tagPlayer _player;
	tagPlayerGun _playerGun;
	playerState* state;
	tagEnemy _enemy;



	int _count;
	int _index;
	int _timer;
	int _blink;
	int _gunType;
	bool _imageON;

	playerBullet* _playerBullet;
public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	//플레이어 참조자
	//tagPlayer& getPlayer() { return _player; }

	RECT getRect() { return _player.rc; }
	RECT getShadowRect() { return _player.shadow; }
	playerState* getState() { return state; }
	playerBullet* getPlayerBullet() {return _playerBullet;}
	
	float getPlayerX() { return _player.x; }
	float getPlayerY() { return _player.y; }
	void setPlayerX(float x) { _player.x = x; }
	void setPlayerY(float y) { _player.y = y; }
	
	void setHit(bool hit) { _player.isHit = hit; }
	bool getHit() { return _player.isHit; }
	
	int getPlayerDirection() { return _player.direction; }
	void setPlayerDirection(int direction) { _player.direction = direction; }
	
	float getPlayerSpeed() { return _player.speed; }
	
	float getPlayerGunX() { return _playerGun.x; }
	float getPlayerGunY() { return _playerGun.y; }
	
	int getPlayerGuntype() { return _gunType; }

	image* getPlayerImage() { return _player.img; }
	void setPlayerImage(image* img) { _player.img = img; }

	void addIMAGES();

	void inputHandle();
	
	float getEnemyX() { return _enemy.x; }
	float getEnemyY() { return _enemy.y; }
	int getGuntype() { return _gunType; }
	void setGuntype(int type) { _gunType = type; }
	void setGunRECT(RECT rc) { _playerGun.rc = rc; }

	float getGunAngle() { return _playerGun.angle; }
	void setGunAngle(float playerGunAngle) { _playerGun.angle = playerGunAngle; }

	int getPlayerCurrentFrameX() { return _player.currentFrameX; }
	void setPlayerCurrentFrameX(int frameX) { _player.currentFrameX = frameX; }

	bool getPlayerisEnd() { return _player.isEnd; }
	void setPlayerisEnd(bool end) { _player.isEnd = end; }
};
