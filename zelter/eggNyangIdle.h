#pragma once
#include "eggNyangStateBase.h"

class eggNyang;

class eggNyangIdle : public eggNyangStateBase
{
	

public :
	virtual eggNyangStateBase* inputHandle(eggNyang* eggNyang);
	virtual void update(eggNyang* eggNyang);
	virtual void enter(eggNyang* eggNyang);
	virtual void render(eggNyang* eggNyang);
	virtual void exit(eggNyang* eggNyang);
};

