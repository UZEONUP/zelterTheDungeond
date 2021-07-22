#pragma once
#include "gameNode.h"
#include "playerState.h"
#include "quickSlot.h"
#include "progressBar.h"
#include "inGameMap.h"
#include "niflheimBullet.h"
#include "bulletKingBullet.h"

class bulletKing;
class ammoconda;
class niflheim;
class playerBullet;

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
	bool isDeath;
	bool isDunGreed; // 던그리드 보스씬 구분용
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
	quickSlot* _quickSlot;
	progressBar* _progressBar;


	int _count;
	int _index;
	int _timer;
	int _blink;
	int _gunType;
	bool _imageON;

	image* _mouse;
	playerBullet* _playerBullet;

	//======================다른 곳에서 불러온 변수=================
	inGameMap* _inGame;
	//아모콘다맵* 맵;
	bulletKing* _bulletKing;
	ammoconda* _ammoconda;
	niflheim* _niflheim;

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

	tagPlayer getPlayer() { return _player; }
	
	float getPlayerGunAngle() { return _playerGun.angle; }

	int getPlayerGuntype() { return _gunType; }

	void setPlayerX(float x) { _player.x = x; }
	void setPlayerY(float y) { _player.y = y; }

	void setHit(bool hit) { _player.isHit = hit; }
	float hitDamage(float damage);
	void setPlayerDirection(int direction) { _player.direction = direction; }

	void setPlayerImage(image* img) { _player.img = img; }

	void addIMAGES();

	void inputHandle();
	
	float getEnemyX() { return _enemy.x; }
	float getEnemyY() { return _enemy.y; }

	void setGuntype(int type) { _gunType = type; }
	void setGunRECT(RECT rc) { _playerGun.rc = rc; }

	float getPlayerGunX() { return _playerGun.x; }
	float getPlayerGunY() { return _playerGun.y; }

	float getGunAngle() { return _playerGun.angle; }
	void setGunAngle(float playerGunAngle) { _playerGun.angle = playerGunAngle; }

	void setPlayerCurrentFrameX(int frameX) { _player.currentFrameX = frameX; }

	void setPlayerisEnd(bool end) { _player.isEnd = end; }

	void setPlayerisDeath(bool death) { _player.isDeath = death; }

	void setplayerBulletLink(playerBullet* playerBullet) { _playerBullet = playerBullet; }


	//==================맵 링크 관련====================================
	void linkOpenWorldMap(inGameMap* map) {  _inGame = map; }
	void setKeyType(bool type) { _player.isDunGreed = type; }
	void linkBulletKing(bulletKing* bulletKing) { _bulletKing = bulletKing; }
	void linkAmmoconda(ammoconda* ammoconda) { _ammoconda = ammoconda; }
	void linkNiflHeim(niflheim* niflheim) { _niflheim = niflheim; }
};
