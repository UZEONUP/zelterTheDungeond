#pragma once
#include "gameNode.h"
#include "inGameMap.h"
#include "niflheimMap.h"
#include "player.h"

struct tagNPC
{
	image* img;
	RECT rc;
	float x, y;
};


class inGame : public gameNode
{
private:
	inGameMap* _inGameMap;
	niflheimMap* _niflheimMap;
	player* _player;
	POINT _mapMouse;

	//==================
	tagNPC _npc;
	int count;
public:
	inGame() {};
	~inGame() {};

	HRESULT init();
	void release();	
	void update();
	void render();

	void collisionDoor();


};

