#pragma once
#include "gameNode.h"
#include "inGameMap.h"
#include "player.h"

class inGame : public gameNode
{
private:
	inGameMap* _inGameMap;
	player* _player;

public:
	inGame() {};
	~inGame() {};

	HRESULT init();
	void release();	
	void update();
	void render();
};

