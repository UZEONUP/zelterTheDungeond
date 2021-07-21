#pragma once
#include "gameNode.h"
#include "stageManager.h"
#include "player.h"
#include "playerBullet.h"



class playGround : public gameNode
{
private:
	stageManager* _stageManager;
	player* _player;
	playerBullet* _playerBullet;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};


































































