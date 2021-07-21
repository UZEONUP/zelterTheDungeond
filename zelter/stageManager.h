#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "mapmap.h"
#include "player.h"
#include "characterPick.h"

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
