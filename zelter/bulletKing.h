#pragma once
#include "gameNode.h"
#include "bulletKingState.h"
#include "bulletKingIdle.h"
#include "bulletKingBullet.h"
#include "progressBar.h"
#include "player.h"

struct tagBulletKing
{
	image* img;							//총탄킹 이미지

	RECT rc;							//총탄킹 렉트
	float speed;						//총탄킹 속도
	float angle;						//총탄킹 각도(라디안)
	float x, y;							//총탄킹 x, y
	int width, height;					//총탄킬 가로 길이, 세로 길이
	int currentFrameX;					//총탄킹 x축 현재 프레임
	int maxHp, currentHp;				//총탄킹 최대 체력, 현재 체력
	bool isAttack3;						//3번쨰 패턴 발생 여부
};

class bulletKing : public gameNode
{
private:
	//총탄킹 본체 및 의자 구조체
	tagBulletKing _bulletKing;
	tagBulletKing _bulletKingChair;

	//체력
	progressBar* _hp;
	image* _bulletKing_hp;

	//총알 클래스
	bulletKingBullet* _bullet;

	//총탄킹 상태패턴
	bulletKingState* _state;
	
	//적 테스트용
	tagBulletKing _enemyTest;
	bool _isMove;


	player* _player;
public:
	bulletKing();
	~bulletKing();

	HRESULT init();
	void release();
	void update();
	void render();
	void InputHandle();
	void setBoss();

	tagBulletKing& getBulletKing() { return _bulletKing; }
	void setBulletKingX(int x) { _bulletKing.x = x; }
	void setBulletKingY(int y) { _bulletKing.y = y; }
	void setBulletKingCurrentFrameX(int currentX) { _bulletKing.currentFrameX = currentX; }
	void setBulletKingImg(image* bulletKingImg) { _bulletKing.img = bulletKingImg; }
	void setBulletKingIsAttack3(bool bulletKingIsAttack3) { _bulletKing.isAttack3 = bulletKingIsAttack3; }

	tagBulletKing& getBulletKingChair() { return _bulletKingChair; }
	void setBulletKingChairX(int x) { _bulletKingChair.x = x; }
	void setBulletKingChairY(int y) { _bulletKingChair.y = y; }
	void setBulletKingChairCurrentFrameX(int currentX) { _bulletKingChair.currentFrameX = currentX; }
	void setBulletKingAttack3(bool bulletKingChairAttack3) { _bulletKingChair.isAttack3 = bulletKingChairAttack3; }

	//총알 get
	bulletKingBullet* getBulletKingBullet() { return _bullet; }

	//적 테스트 get
	tagBulletKing getEnemyTest() {return _enemyTest;}
};

