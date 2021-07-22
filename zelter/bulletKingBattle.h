#pragma once
#include "gameNode.h"
#include "bulletKing.h"
#include "fishMan.h"
#include "dinosaur.h"
#include "player.h"
#include "bulletKingMap.h"

class bulletKingBattle : public gameNode
{
private:
	bulletKing* _bulletKing;
	player* _player;

	fishMan* _fishMan;
	dinosaur* _dinosaur;

	//¸Ê°ü·Ã
	bulletKingMap* _bulletKingMap;
	POINT _mapMouse;
public:
	bulletKingBattle();
	~bulletKingBattle();

	HRESULT init();
	void release();
	void update();
	void render();

};

