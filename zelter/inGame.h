#pragma once
#include "tileNode.h"
#include "gameNode.h"

struct tagPlayerr
{
	image* img;
	RECT rc;
	float x, y;
};

class inGame : public gameNode
{
private:
	tagTile _tile[TILEX*TILEY];
	DWORD _attribute[TILEX*TILEY];
	POINT _mapMouse;
	int _pos[2];

	tagPlayerr _player;

public:
	inGame() {};
	~inGame() {};

	HRESULT init();
	void release();
	void update();
	void render();
	void load();

	tagTile* getTile() { return _tile; }
	//Ÿ�� �Ӽ��� ���� �����ڵ� �������� �÷��̾� ��ü�� ���ʹ� ��ü�� ���� ����
	DWORD*  getTileAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

