#pragma once
#include "gameNode.h"



struct tagCharacterPick
{
	RECT rc;
	image* img;
	float x, y;
	int currentFrameX;
	int currentFrameY;

	bool on;
	bool pick;
};
class characterPick :public gameNode 
{
private:
	tagCharacterPick _characterPick;
	tagCharacterPick _characterPick2;
	tagCharacterPick _character;
	tagCharacterPick _character2;

	image* _mouse;

public:

	int _count;

	HRESULT init();
	void virtual update();
	void virtual release();
	void virtual render();

	void setImages();
};

