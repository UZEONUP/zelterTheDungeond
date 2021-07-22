#include "stdafx.h"
#include "playerHit.h"

playerState * playerHit::inputHandle(player * player)
{

	return nullptr;
}

void playerHit::update(player * player)
{
	_count++;
	if (player->getPlayer().isHit)
	{
		if (_count <= 30)
		{
			player->getPlayer().img->setAlpha(0);
		}
		else
		{
			player->getPlayer().img->setAlpha(1);
			_blink++;
			_count = 0;
		}

	/*	if (_blink >= 3)
		{
			player->getPlayer().isHit = false;
		}*/
	}

}

void playerHit::enter(player * player)
{

}

void playerHit::exit(player * player)
{
}

void playerHit::getCurrentState(player * player)
{
}
