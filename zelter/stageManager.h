#pragma once
#include "gameNode.h"
#include "testScene.h"
//#include "mapToolManager.h"
#include "mapmap.h"

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
