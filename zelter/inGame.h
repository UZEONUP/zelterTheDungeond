#pragma once
#include "gameNode.h"

class inGame : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

