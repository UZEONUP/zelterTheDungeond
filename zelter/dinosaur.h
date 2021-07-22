#pragma once
#include <vector>
#include "bulletKing.h"
#include "gameNode.h"

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
	image* img;							//���� �̹���
	RECT rc;							//���� ��Ʈ
	float speed;						//���� �ӵ�
	float angle;						//���� ����(����)
	float x, y;							//���� x, y
	int width, height;					//���� ���� ����, ���� ����
	int currentFrameX;					//���� x�� ���� ������
	int currentFrameY;					//���� y�� ���� ������
	int maxHp, currentHp;				//���� �ִ� ü��, ���� ü��
	int count;							//�̹��� ������ ī��Ʈ
	int changeCount;					//���º�ȯ�� ī��Ʈ
	DINOSAURDIRECTION direction;
	DINOSAURSTATE state;
};

class dinosaur : public gameNode
{
private:
	//�ǽ��� ����ü
	tagDinosaur _dinosaur;

	//�ǽ��� ����
	vector<tagDinosaur> _vDinosaur;
	vector<tagDinosaur>::iterator _viDinosaur;

	//�׽�Ʈ �÷��̾�
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
