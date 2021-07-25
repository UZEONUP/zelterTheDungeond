#include "stdafx.h"
#include "pickDialogue.h"

//pickDialogue::pickDialogue()
//{
//}
//
//pickDialogue::~pickDialogue()
//{
//}
//
//HRESULT pickDialogue::init()
//{
//	_count = 0;
//	_pickTextCount = 0;
//	_pickText = "위자드  캐릭터를  사용하시려면  구매하셔야  합니다.   구매하시겠습니까?";
//	_img = IMAGEMANAGER->findImage("확인창");
//
//	return S_OK;
//}
//
//void pickDialogue::release()
//{
//}
//
//void pickDialogue::update()
//{
//	_count++;
//	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 600, 400);
//	if (_count % 5 == 0)_pickTextCount++;
//
//	strncpy_s(_pickTextCut, sizeof(_pickTextCut), _pickText, _pickTextCount * 2);
//
//	if (_pickTextCount >= strlen(_pickText)) _pickTextCount = strlen(_pickText);
//}
//
//void pickDialogue::render()
//{
//	_img->render(_rc.left, _rc.top);
//	D2DRENDER->RenderTextField(_rc.left+20,_rc.top-100, ConvertCtoWC(_pickTextCut), D2D1::ColorF::White,20,500,400);
//}
