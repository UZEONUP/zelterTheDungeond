#pragma once
#include "gameNode.h"
#include "ammoconda.h"

class ammocondaBattle : public gameNode
{
private:
	ammoconda* _ammoconda;

public:
	ammocondaBattle();
	~ammocondaBattle();

	HRESULT init();
	void release();
	void update();
	void render();
};

