#include "stdafx.h"
#include "stageManager.h"

HRESULT stageManager::init()
{
	sceneSet();
	_player = new player;
	_eggNyang = new eggNyang;
	_niflheim = new niflheim;

	_niflheim->linkPlayer(_player);
	_eggNyang->linkPlayer(_player);

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
	SCENEMANAGER->addScene("eggNyang", new eggNyang);
	SCENEMANAGER->addScene("niflheim", new niflheim);
	SCENEMANAGER->addScene("bulletKing", new bulletKingBattle);
	SCENEMANAGER->addScene("ammoconda", new ammocondaBattle);


	SCENEMANAGER->changeScene("eggNyang");
}
