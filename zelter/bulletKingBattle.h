#pragma once
#include "gameNode.h"
#include "bulletKing.h"
#include "fishMan.h"
#include "dinosaur.h"

class bulletKingBattle : public gameNode
{
private:
	bulletKing* _bulletKing;
	fishMan* _fishMan;
	dinosaur* _dinosaur;


public:
	bulletKingBattle();
	~bulletKingBattle();

	HRESULT init();
	void release();
	void update();
	void render();

};

