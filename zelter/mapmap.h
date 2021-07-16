#pragma once
#include "gameNode.h"
#include <vector>

#define TILESIZEX 32
#define TILESIZEY 32

#define SAMPLETILEX 20
#define SAMPLETILEY 9

#define TILEX WINSIZEX / TILESIZEX
#define TILEY WINSIZEY / TILESIZEY

			  


enum TERRAINFAKE
{
	CEMENT,
	DESERT,
	WATER
};

enum OBJECTFAKE
{
	BLOCK, NONE
};

struct tagTileFake
{
	TERRAINFAKE terrain;
	OBJECTFAKE object;
	image* img;
	RECT rc;
	int terrainX;
	int terrainY;
	int objX;
	int objY;
	int sizeX;
	int sizeY;
};

struct tagSampleTileFake
{
	RECT rc;
	int frameX;
	int frameY;
};

struct tagButtonFake
{
	RECT rc;
	image* img;
};

struct sampleMapTool
{
	RECT rc;
	bool isOn;
};

struct tagMouseDrag
{ 
	RECT rc;
	POINT start;
	POINT end;
	int currentStartX;
	int currentStartY;
	int currentEndX;
	int currentEndY;
	bool isDrag;
};

struct tagPlayer
{
	image* img;
	RECT rc;
	float x, y;
};

class mapmap : public gameNode
{
private:
	vector<tagTileFake> _vTile;

	tagTileFake _tile[TILEX * TILEY];
	tagTileFake _realIile[TILEX * TILEY];

	tagSampleTileFake _sample[SAMPLETILEX * SAMPLETILEY];

	POINT _currentTile;
	
	tagPlayer _player;

	sampleMapTool _tool;

	tagButtonFake _btnSave;
	tagButtonFake _btnLoad;
	tagButtonFake _btnEraser;
	tagButtonFake _btnObject;
	tagButtonFake _btnTerrain;
	tagButtonFake _btnEnter;

	tagMouseDrag _dragMouse;

	RECT _message;
	
	bool _dragStart;

	int _startX, _startY;
	int _endX, _endY;

public:
	mapmap() {};
	~mapmap() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setup();
	void setMap();

	void cameraMove();

	void save();
	void load();



	void buttonRender();

	void tapTool();

	void dragField();
};

