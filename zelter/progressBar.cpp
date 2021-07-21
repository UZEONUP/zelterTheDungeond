#include "stdafx.h"
#include "progressBar.h"

progressBar::progressBar()
{
}

progressBar::~progressBar()
{
}

HRESULT progressBar::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;

	_rc = RectMake(x, y, width, height);

	barTop = IMAGEMANAGER->addImage("hpfront", L"UI/hpfront.png");
	barBottom = IMAGEMANAGER->addImage("hpback", L"UI/hpback.png");
	

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rc = RectMakeCenter(_x, _y, barTop->getWidth(), barTop->getHeight());
}

void progressBar::render()
{
	barBottom->render(_rc.left,_rc.top);
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * barBottom->getWidth();
}
