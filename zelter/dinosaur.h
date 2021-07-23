#pragma once
#include <vector>
#include "bulletKing.h"
#include "gameNode.h"
#include "dialogue.h"

enum DINOSAURDIRECTION
{
	DINOSAUR_RIGHT,
	DINOSAUR_LEFT
};
enum DINOSAURSTATE
{
	DINOSAUR_IDLE,
	DINOSAUR_WALK,
	DINOSAUR_RUN,
	DINOSAUR_ATTACK,
	DINOSAUR_DEATH,
};

struct tagDinosaur
{
	image* img;							//공룡 이미지
	RECT rc;							//공룡 렉트
	float speed;						//공룡 속도
	float angle;						//공룡 각도(라디안)
	float x, y;							//공룡 x, y
	int width, height;					//공룡 가로 길이, 세로 길이
	int currentFrameX;					//공룡 x축 현재 프레임
	int currentFrameY;					//공룡 y축 현재 프레임
	int maxHp, currentHp;				//공룡 최대 체력, 현재 체력
	int count;							//이미지 프레임 카운트
	int changeCount;					//상태변환용 카운트
	DINOSAURDIRECTION direction;
	DINOSAURSTATE state;
};

class dinosaur : public gameNode
{
private:
	//다이얼로그
	dialogue*	_dialogue;

	//피쉬맨 구조체
	tagDinosaur _dinosaur;

	//피쉬맨 벡터
	vector<tagDinosaur> _vDinosaur;
	vector<tagDinosaur>::iterator _viDinosaur;

	//테스트 플레이어
	bulletKing* _bulletKing;

public:
	dinosaur();
	~dinosaur();

	HRESULT init();
	void release();
	void update();
	void render();
	void setEnemy(float x, float y);
	void dinoMove(float x, float y);
	void dinoState();

	tagDinosaur getFishMan() { return _dinosaur; }
	void setFishManImage(image* img) { _dinosaur.img = img; }
	void setFishManCurrentFrameX(int currentFrameX) { _dinosaur.currentFrameX = currentFrameX; }
	void setFishManCurrentFrameY(int currentFrameY) { _dinosaur.currentFrameY = currentFrameY; }
	void setFishManAngle(float angle) { _dinosaur.angle = angle; }
};

