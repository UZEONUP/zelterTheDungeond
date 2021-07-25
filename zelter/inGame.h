#pragma once
#include "gameNode.h"
#include "inGameMap.h"
#include "niflheimMap.h"
#include "player.h"

class inGame : public gameNode
{
private:
	inGameMap* _inGameMap;
	niflheimMap* _niflheimMap;
	player* _player;
	POINT _mapMouse;
public:
	inGame() {};
	~inGame() {};

	HRESULT init();
	void release();	
	void update();
	void render();

	void collisionDoor();


};

