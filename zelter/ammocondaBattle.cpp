#include "stdafx.h"
#include "ammocondaBattle.h"

ammocondaBattle::ammocondaBattle()
{
}

ammocondaBattle::~ammocondaBattle()
{
}

HRESULT ammocondaBattle::init()
{
	_ammoconda = new ammoconda;
	_ammoconda->init();

	return S_OK;
}

void ammocondaBattle::release()
{
}

void ammocondaBattle::update()
{
	_ammoconda->update();
}

void ammocondaBattle::render()
{
	_ammoconda->render();
}
