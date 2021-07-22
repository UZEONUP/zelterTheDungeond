#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "mapmap.h"
#include "player.h"
#include "characterPick.h"

#include"eggNyang.h"
#include"niflheim.h"

#include "ammocondaBattle.h"
#include "bulletKingBattle.h"

class stageManager : public gameNode
{
private:


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void sceneSet();

};
