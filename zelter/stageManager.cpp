#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	sceneSet();


	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
	SCENEMANAGER->update();
}

void stageManager::render()
{
	SCENEMANAGER->render();

	
}

void stageManager::sceneSet()
{
	SCENEMANAGER->addScene("title", new testScene);
	SCENEMANAGER->addScene("mapmap", new mapmap);
	SCENEMANAGER->addScene("player", new player);
	SCENEMANAGER->addScene("pick", new characterPick);


	SCENEMANAGER->changeScene("player");
}
