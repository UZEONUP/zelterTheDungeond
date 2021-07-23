#pragma once
#include "gameNode.h"
#include <vector>
#include "bulletKing.h"
#include "dialogue.h"

enum FISHMANDIRECTION
{
	FISHMAN_RIGHT,
	FISHMAN_LEFT
};
enum FISHMANSTATE 
{
	FISHMAN_IDLE,
	FISHMAN_WALK,
	FISHMAN_RUN,
	FISHMAN_ATTACK,
	FISHMAN_DEATH,
};

struct tagFishMan
{
	image* img;							//�ǽ��� �̹���
	RECT rc;							//�ǽ��� ��Ʈ
	float speed;						//�ǽ��� �ӵ�
	float angle;						//�ǽ��� ����(����)
	float x, y;							//�ǽ��� x, y
	int width, height;					//�ǽ��� ���� ����, ���� ����
	int currentFrameX;					//�ǽ��� x�� ���� ������
	int currentFrameY;					//�ǽ��� y�� ���� ������
	int maxHp, currentHp;				//�ǽ��� �ִ� ü��, ���� ü��
	int count;							//�̹��� ������ ī��Ʈ
	int changeCount;					//���º�ȯ�� ī��Ʈ
	FISHMANDIRECTION direction;
	FISHMANSTATE state;
};


class fishMan : public gameNode
{
private:
	//���̾�α�
	dialogue* _dialogue;

	//�ǽ��� ����ü
	tagFishMan _fishMan;

	//�ǽ��� ����
	vector<tagFishMan> _vFishMan;
	vector<tagFishMan>::iterator _viFishMan;

	//�׽�Ʈ �÷��̾�
	bulletKing* _bulletKing;

public:
	fishMan();
	~fishMan();

	HRESULT init();
	void release();
	void update();
	void render();
	void setEnemy(float x, float y);
	void fishMove(float x, float y);
	void fishState();

	tagFishMan getFishMan() { return _fishMan; }
	void setFishManImage(image* img) { _fishMan.img = img; }
	void setFishManCurrentFrameX(int currentFrameX) { _fishMan.currentFrameX = currentFrameX; }
	void setFishManCurrentFrameY(int currentFrameY) { _fishMan.currentFrameY = currentFrameY; }
	void setFishManAngle(float angle) { _fishMan.angle = angle; }


};

