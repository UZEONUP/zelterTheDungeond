#pragma once
#include "singletonBase.h"
#include "mapmap.h"

class saveLoadManager : public singletonBase<saveLoadManager>
{
private:
	vector<tagTile>					_vTile;
	vector<tagTile>::iterator		_viTile;

public:
	saveLoadManager() {}; 
	~saveLoadManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void save(vector<tagTile> tile);
	vector<tagTile> load();
};

