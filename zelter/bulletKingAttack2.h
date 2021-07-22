#pragma once
#include "bulletKingState.h"
#include "bulletKing.h"
#include "bulletKingIdle.h"

class bulletKingAttack2 : public bulletKingState
{
private:
	int _count;
	int rand;
public:
	virtual bulletKingState* InputHandle(bulletKing* bulletKing);
	virtual void enter(bulletKing* bulletKing);
	virtual void update(bulletKing* bulletKing);
	virtual void render(bulletKing* bulletKing);
	virtual void exit(bulletKing* bulletKing);
};

