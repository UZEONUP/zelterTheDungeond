#include "stdafx.h"
#include "playGround.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")


playGround::playGround()
{

}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);;

	_stageManager = new stageManager;
	_stageManager->init();

	_player = new player;
	_playerBullet = new playerBullet;
	

	_player->init();
	_playerBullet->init();
	
	_player->setplayerBulletLink(_playerBullet);
	_playerBullet->setPlayerLink(_player);

	return S_OK;
}

//�޸� ����
void playGround::release()
{

}

//����
void playGround::update()
{
	gameNode::update();

	
	_stageManager->update();

}

//�׸��� ����
void playGround::render()
{
	//����� �ʱ�ȭ
	D2DRENDER->BeginRender(D2D1::ColorF::White);


	_stageManager->render();

	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2DRENDER->EndRender();
}
