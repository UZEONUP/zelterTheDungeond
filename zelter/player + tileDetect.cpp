#include "stdafx.h"
#include "player.h"

void player::tileDetect(string sceneName)
{
	if (sceneName == "openWorld")
	{

		RECT rcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������


		int	tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
		int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

		//������ ������Ʈ�� ���� ��Ʈ�� ����������
		rcCollision = _player.rc;

		rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

		//STEP 3
		////������Ʈ�� ���¦ �������
		/*rcCollision.left += 4;
		rcCollision.top += 4;
		rcCollision.right -= 4;
		rcCollision.bottom -= 4;*/

		tileX = rcCollision.left / 48;
		tileY = rcCollision.top / 48;


		//STEP 04
		//���� �������� ������
		//�ش� �����϶� ����Ʈ ž�� �������� ��Ÿ�ϰ� �� ��Ÿ���� ������ش�

		/*
		-----------------
		4	|	2	|	5
		-----------------
		1	| player|	0
		-----------------
		7	|	3	|	6
		*/
		switch (_player.movingDirection)
		{
		case 4:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX + (tileY*TILEY);
			break;
		case 2:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 5:
			tileIndex[0] = (tileX)+(tileY * TILEX);
			tileIndex[1] = tileX + 1 + (tileY * TILEX);
			break;
		case 1:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = tileX + (tileY + 1)*TILEX;
			break;
		case 0:
			tileIndex[0] = tileX + 1 + tileY * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
			break;
		case 7:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
			break;
		case 3:
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
			break;
		case 6:
			tileIndex[0] = tileX + 1 + (tileY * TILEX);
			tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
			break;
		}

		for (int i = 0; i < 2; ++i)
		{
			//if (_inGame->getTileAtt()[tileIndex[i]] != NONEMOVE)continue;
			RECT rc;

			if (((_inGame->getTileAtt()[tileIndex[i]] == NONEMOVE)) &&
				IntersectRect(&rc, &_inGame->getTile()[tileIndex[i]].checkRect, &rcCollision))
			{
				switch (_player.movingDirection)
				{
				case 1:
					_player.rc.left = _inGame->getTile()[tileIndex[i]].checkRect.right;
					_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;

					break;
				case 2:
					_player.rc.top = _inGame->getTile()[tileIndex[i]].checkRect.bottom;
					_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				case 0:
					_player.rc.right = _inGame->getTile()[tileIndex[i]].checkRect.left;
					_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;
					break;
				case 3:
					_player.rc.bottom = _inGame->getTile()[tileIndex[i]].checkRect.top;
					_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				}
			}
		}
		for (int i = 0; i < 2; ++i)
		{
			_tileIdx[i] = RectMake(_inGame->getTile()[tileIndex[i]].rc.left, _inGame->getTile()[tileIndex[i]].rc.top, 64, 64);
		}
		//_player.rc = rcCollision;
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "bulletKing")
	{
		RECT rcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������


		int	tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
		int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

		//������ ������Ʈ�� ���� ��Ʈ�� ����������
		rcCollision = _player.rc;

		rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

		//STEP 3
		////������Ʈ�� ���¦ �������
		/*rcCollision.left += 4;
		rcCollision.top += 4;
		rcCollision.right -= 4;
		rcCollision.bottom -= 4;*/

		tileX = rcCollision.left / 64;
		tileY = rcCollision.top / 64;


		//STEP 04
		//���� �������� ������
		//�ش� �����϶� ����Ʈ ž�� �������� ��Ÿ�ϰ� �� ��Ÿ���� ������ش�

		/*
		-----------------
		4	|	2	|	5
		-----------------
		1	| player|	0
		-----------------
		7	|	3	|	6
		*/
		switch (_player.movingDirection)
		{
		case 4:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX + (tileY*TILEY);
			break;
		case 2:
			tileIndex[0] = tileX + (tileY * TILEX);
			tileIndex[1] = (tileX + 1) + (tileY * TILEX);
			break;
		case 5:
			tileIndex[0] = (tileX)+(tileY * TILEX);
			tileIndex[1] = tileX + 1 + (tileY * TILEX);
			break;
		case 1:
			tileIndex[0] = tileX + tileY * TILEX;
			tileIndex[1] = tileX + (tileY + 1)*TILEX;
			break;
		case 0:
			tileIndex[0] = tileX + 1 + tileY * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
			break;
		case 7:
			tileIndex[0] = (tileX - 1) + (tileY*TILEY);
			tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
			break;
		case 3:
			tileIndex[0] = tileX + (tileY + 1) * TILEX;
			tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
			break;
		case 6:
			tileIndex[0] = tileX + 1 + (tileY * TILEX);
			tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
			break;
		}

		for (int i = 0; i < 2; ++i)
		{
			RECT rc;

			if (((_bulletKingMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
				IntersectRect(&rc, &_bulletKingMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
			{
				switch (_player.movingDirection)
				{
				case 1:
					_player.rc.left = _bulletKingMap->getTile()[tileIndex[i]].checkRect.right;
					_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;

					break;
				case 2:
					_player.rc.top = _bulletKingMap->getTile()[tileIndex[i]].checkRect.bottom;
					_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				case 0:
					_player.rc.right = _bulletKingMap->getTile()[tileIndex[i]].checkRect.left;
					_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

					_player.x = (_player.rc.left + _player.rc.right) / 2;
					break;
				case 3:
					_player.rc.bottom = _bulletKingMap->getTile()[tileIndex[i]].checkRect.top;
					_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

					_player.y = (_player.rc.top + _player.rc.bottom) / 2;
					break;
				}
			}
		}
		for (int i = 0; i < 2; ++i)
		{
			_tileIdx[i] = RectMake(_bulletKingMap->getTile()[tileIndex[i]].rc.left, _bulletKingMap->getTile()[tileIndex[i]].rc.top, 64, 64);
		}
		_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "ammoconda")
	{
	RECT rcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������


	int	tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
	int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

	//������ ������Ʈ�� ���� ��Ʈ�� ����������
	rcCollision = _player.rc;

	rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	//STEP 3
	////������Ʈ�� ���¦ �������
	/*rcCollision.left += 4;
	rcCollision.top += 4;
	rcCollision.right -= 4;
	rcCollision.bottom -= 4;*/

	tileX = rcCollision.left / 64;
	tileY = rcCollision.top / 64;


	//STEP 04
	//���� �������� ������
	//�ش� �����϶� ����Ʈ ž�� �������� ��Ÿ�ϰ� �� ��Ÿ���� ������ش�

	/*
	-----------------
	4	|	2	|	5
	-----------------
	1	| player|	0
	-----------------
	7	|	3	|	6
	*/
	switch (_player.movingDirection)
	{
	case 4:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX + (tileY*TILEY);
		break;
	case 2:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = (tileX + 1) + (tileY * TILEX);
		break;
	case 5:
		tileIndex[0] = (tileX)+(tileY * TILEX);
		tileIndex[1] = tileX + 1 + (tileY * TILEX);
		break;
	case 1:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)*TILEX;
		break;
	case 0:
		tileIndex[0] = tileX + 1 + tileY * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
		break;
	case 7:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
		break;
	case 3:
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
		break;
	case 6:
		tileIndex[0] = tileX + 1 + (tileY * TILEX);
		tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;

		if (((_ammocondaMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
			IntersectRect(&rc, &_ammocondaMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
		{
			switch (_player.movingDirection)
			{
			case 1:
				_player.rc.left = _ammocondaMap->getTile()[tileIndex[i]].checkRect.right;
				_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;

				break;
			case 2:
				_player.rc.top = _ammocondaMap->getTile()[tileIndex[i]].checkRect.bottom;
				_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			case 0:
				_player.rc.right = _ammocondaMap->getTile()[tileIndex[i]].checkRect.left;
				_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;
				break;
			case 3:
				_player.rc.bottom = _ammocondaMap->getTile()[tileIndex[i]].checkRect.top;
				_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			}
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		_tileIdx[i] = RectMake(_ammocondaMap->getTile()[tileIndex[i]].rc.left, _ammocondaMap->getTile()[tileIndex[i]].rc.top, 64, 64);
	}
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "eggNyang")
	{
	RECT rcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������


	int	tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
	int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

	//������ ������Ʈ�� ���� ��Ʈ�� ����������
	rcCollision = _player.rc;

	rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	//STEP 3
	////������Ʈ�� ���¦ �������
	/*rcCollision.left += 4;
	rcCollision.top += 4;
	rcCollision.right -= 4;
	rcCollision.bottom -= 4;*/

	tileX = rcCollision.left / 64;
	tileY = rcCollision.top / 64;


	//STEP 04
	//���� �������� ������
	//�ش� �����϶� ����Ʈ ž�� �������� ��Ÿ�ϰ� �� ��Ÿ���� ������ش�

	/*
	-----------------
	4	|	2	|	5
	-----------------
	1	| player|	0
	-----------------
	7	|	3	|	6
	*/
	switch (_player.movingDirection)
	{
	case 4:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX + (tileY*TILEY);
		break;
	case 2:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = (tileX + 1) + (tileY * TILEX);
		break;
	case 5:
		tileIndex[0] = (tileX)+(tileY * TILEX);
		tileIndex[1] = tileX + 1 + (tileY * TILEX);
		break;
	case 1:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)*TILEX;
		break;
	case 0:
		tileIndex[0] = tileX + 1 + tileY * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
		break;
	case 7:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
		break;
	case 3:
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
		break;
	case 6:
		tileIndex[0] = tileX + 1 + (tileY * TILEX);
		tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;

		if (((_eggNyangMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
			IntersectRect(&rc, &_eggNyangMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
		{
			switch (_player.movingDirection)
			{
			case 1:
				_player.rc.left = _eggNyangMap->getTile()[tileIndex[i]].checkRect.right;
				_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;

				break;
			case 2:
				_player.rc.top = _eggNyangMap->getTile()[tileIndex[i]].checkRect.bottom;
				_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			case 0:
				_player.rc.right = _eggNyangMap->getTile()[tileIndex[i]].checkRect.left;
				_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;
				break;
			case 3:
				_player.rc.bottom = _eggNyangMap->getTile()[tileIndex[i]].checkRect.top;
				_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			}
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		_tileIdx[i] = RectMake(_eggNyangMap->getTile()[tileIndex[i]].rc.left, _eggNyangMap->getTile()[tileIndex[i]].rc.top, 64, 64);
	}
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
	else if (sceneName == "niflheim")
	{
	RECT rcCollision;	//������ �浹���� ��Ʈ�� �ϳ� ����������


	int	tileIndex[2];	//Ÿ�� ���⿡ �ʿ��� �ε���
	int tileX, tileY;	//�÷��̾ ��� �ִ� Ÿ���� �ε���

	//������ ������Ʈ�� ���� ��Ʈ�� ����������
	rcCollision = _player.rc;

	rcCollision = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());

	//STEP 3
	////������Ʈ�� ���¦ �������
	/*rcCollision.left += 4;
	rcCollision.top += 4;
	rcCollision.right -= 4;
	rcCollision.bottom -= 4;*/

	tileX = rcCollision.left / 32;
	tileY = rcCollision.top / 32;
	 

	//STEP 04
	//���� �������� ������
	//�ش� �����϶� ����Ʈ ž�� �������� ��Ÿ�ϰ� �� ��Ÿ���� ������ش�

	/*
	-----------------
	4	|	2	|	5
	-----------------
	1	| player|	0
	-----------------
	7	|	3	|	6
	*/
	switch (_player.movingDirection)
	{
	case 4:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX + (tileY*TILEY);
		break;
	case 2:
		tileIndex[0] = tileX + (tileY * TILEX);
		tileIndex[1] = (tileX + 1) + (tileY * TILEX);
		break;
	case 5:
		tileIndex[0] = (tileX)+(tileY * TILEX);
		tileIndex[1] = tileX + 1 + (tileY * TILEX);
		break;
	case 1:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)*TILEX;
		break;
	case 0:
		tileIndex[0] = tileX + 1 + tileY * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1) * TILEX;
		break;
	case 7:
		tileIndex[0] = (tileX - 1) + (tileY*TILEY);
		tileIndex[1] = tileX - 1 + (tileY + 1 * TILEY);
		break;
	case 3:
		tileIndex[0] = tileX + (tileY + 1) * TILEX;
		tileIndex[1] = tileX + 1 + (tileY + 1)*TILEX;
		break;
	case 6:
		tileIndex[0] = tileX + 1 + (tileY * TILEX);
		tileIndex[1] = (tileX + 1 + (tileY + 1) * TILEX);
		break;
	}

	for (int i = 0; i < 2; ++i)
	{
		RECT rc;

		if (((_niflheimMap->getTileAttribute()[tileIndex[i]] == NONEMOVE)) &&
			IntersectRect(&rc, &_niflheimMap->getTile()[tileIndex[i]].checkRect, &rcCollision))
		{
			switch (_player.movingDirection)
			{
			case 1:
				_player.rc.left = _niflheimMap->getTile()[tileIndex[i]].checkRect.right;
				_player.rc.right = _player.rc.left + _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;

				break;
			case 2:
				_player.rc.top = _niflheimMap->getTile()[tileIndex[i]].checkRect.bottom;
				_player.rc.bottom = _player.rc.top + _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			case 0:
				_player.rc.right = _niflheimMap->getTile()[tileIndex[i]].checkRect.left;
				_player.rc.left = _player.rc.right - _player.img->getFrameWidth();

				_player.x = (_player.rc.left + _player.rc.right) / 2;
				break;
			case 3:
				_player.rc.bottom = _niflheimMap->getTile()[tileIndex[i]].checkRect.top;
				_player.rc.top = _player.rc.bottom - _player.img->getFrameHeight();

				_player.y = (_player.rc.top + _player.rc.bottom) / 2;
				break;
			}
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		_tileIdx[i] = RectMake(_niflheimMap->getTile()[tileIndex[i]].rc.left, _niflheimMap->getTile()[tileIndex[i]].rc.top, 64, 64);
	}
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	}
}