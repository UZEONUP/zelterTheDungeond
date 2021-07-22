#pragma once
#include "gameNode.h"
#include "niflheim.h"
#include "player.h"

class niflheimBattle : public gameNode
{
	niflheim*	_niflheim;
	player*		_player;


public :
	niflheimBattle() {};
	~niflheimBattle() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

