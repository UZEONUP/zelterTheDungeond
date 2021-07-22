#pragma once
#include "gameNode.h"
#include "ammoconda.h"

class ammocondaBattle : public gameNode
{
private:
	ammoconda* _ammoconda;
	player* _player;
public:
	ammocondaBattle();
	~ammocondaBattle();

	HRESULT init();
	void release();
	void update();
	void render();
};

