#pragma once
#include "playerState.h"

class player;

class playerJump : public playerState
{
	virtual playerState* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
	virtual void getCurrentState(player* player);

	virtual int getCurrentFrame() { return _count; }
	virtual int getFrameX() { return _currentFrameX; }
	virtual int getFrameY() { return _currentFrameY; }
};

