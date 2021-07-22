#pragma once
#include "gameNode.h"
#include "eggNyang.h"
#include "player.h"

class eggNyangBattle : public gameNode
{
	eggNyang*	_eggNyang;
	player*		_player;

public :
	eggNyangBattle() {};
	~eggNyangBattle() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

