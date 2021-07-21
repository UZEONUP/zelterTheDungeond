#include "stdafx.h"
#include "saveLoadManager.h"

HRESULT saveLoadManager::init()
{
	return S_OK;
}

void saveLoadManager::release()
{
}

void saveLoadManager::update()
{
}

void saveLoadManager::render()
{
}

void saveLoadManager::save(vector<tagTile> tile)
{
	for (int i = 0; i < tile.size(); i++)
	{
		_vTile.push_back(tile[i]);
	}
}

vector<tagTile> saveLoadManager::load()
{
	return _vTile;
}
