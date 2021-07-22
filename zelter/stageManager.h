#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "mapmap.h"
#include "player.h"
#include "characterPick.h"
#include "inGame.h"

#include"eggNyang.h"
#include"niflheim.h"

#include "ammocondaBattle.h"
#include "bulletKingBattle.h"

class stageManager : public gameNode
{
private:
	player*			_player;
	eggNyang*		_eggNyang;
	niflheim*		_niflheim;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void sceneSet();

};
