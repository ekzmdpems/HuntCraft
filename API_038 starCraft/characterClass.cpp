#include "stdafx.h"
#include "characterClass.h"


characterClass::characterClass()
{
}


characterClass::~characterClass()
{
}



HRESULT characterClass::init(int pos)
{

	/* ----------------------------------*
	/
	/* �⺻ ���� �ʱ�ȭ. ���� 0����       */
	/* ----------------------------------*/
	_charPos.x = 0;
	_charPos.y = 0;
	//_falldownWeight = 0;
	_cameraPos = 0;


	_status = STAND;

	/* ----------------------------------------*/
	/* �浹 ������ ��Ʈ �ڽ� �ʱ�ȭ �ϴ� �Ѱ�    */
	/* ----------------------------------------*/
	_hitBox.left = 5;
	_hitBox.right = 27;
	_hitBox.top = 0;
	_hitBox.bottom = 43;


	// �� �̵��� ���� �ڽ� ����. ���� ĳ���� �߾ӿ� 16x16����...

	_warpBox.left = 9;
	_warpBox.right = 25;
	_warpBox.top = 13;
	_warpBox.bottom = 29;




	/* --------------------------------------------------------

		[�÷��̾� ���� ��ġ ����]
		init()�� �μ��� ���� ��ǥ ID(Ÿ���� _event��)�� ã��
		�ش� Ÿ�� ���� �÷��̾� ĳ���͸� �׸���.

		���� �ҽ������� ���� Ÿ���� �߳����� �ϱ� ������

		((�̺�Ʈ Ÿ�� ��ǥ + 1) * Ÿ�� ũ��) - ĳ���� ��������Ʈ�� ���� ũ��

		�� ��ǥ�� �÷��̾��� Y��ǥ�� ��´�.

		
		�÷��̾� ���� ĳ������ �ڱ� ��ġ ã�� ������

		1. Ÿ���� �Ӽ����� �̺�Ʈ�� Ÿ���� ã�´� ( _viTileData->_attID == EVENT )
		2. Ÿ���� ID������ �÷��̾� Ÿ������ NPC(����) Ÿ������ ã�´� ( _viTileData->_tileID, 0 : �÷��̾�, 1 : NPC, 2 : �� �̵���)
		3. Ÿ���� �̺�Ʈ���� ���� ĳ���͸� ��ġ�Ѵ�( _viTileData->_event, �÷��̾�� ���� ��ǥ, NPC�� ������ ID )

		* ���� 2��° �ʿ� NPC 0, 1���� ��ġ�ǵ��� �Ǿ�����.

		-------------------------------------------------------- */

	_viTileData = MapData->getMap()->begin();
	_length = MapData->mapsize();
	for (_viTileData; _viTileData != MapData->getMap()->end(); ++_viTileData)
	{
		


		if ((_viTileData->_attID -1) == EVENT) // �� Ÿ���� ��쿡�� �浹 ó��
		{
			switch (_viTileData->_tileID) 
			{
			case PLAYER: // �÷��̾�
				if (_viTileData->_event == pos)
				{
					_charPos.x = _viTileData->_pos.x * TILESIZE;
					_charPos.y = ((_viTileData->_pos.y+1) * TILESIZE)- _hitBox.bottom;
				}
				break;
			case NPC: // NPC

				break;
			case EVENT: // �� �̵�
				break;
			}
		}
	}


	return S_OK;
}

void characterClass::release(void)
{

}


int characterClass::eventCheck(POINT tile, int flag)
{
	/*	-----------------------------------------------
		�� �̵��� �浹 ó�� ��ƾ
		ptinrect�� ����
		7�� 16�� ���� ���� ���� ��ƾ �߰�
		----------------------------------------------- */

	POINT centerPos;
	RECT tileRect;

	if (!flag) // �׳� �浹 ó��(�Ϲ����� �� �̵�) 
	{
		centerPos.x = _charPos.x + 17;
		centerPos.y = _charPos.y + 21; 
	}
	else // ����Ű�� ���� �÷ȴٸ� �� üũ
	{

		centerPos.x = _charPos.x + 17;
		centerPos.y = _charPos.y + 42 + MOVESPEED;
		
	}
	tileRect.left = tile.x * TILESIZE;
	tileRect.right = (tile.x+1) * TILESIZE;
	tileRect.top = tile.y * TILESIZE;
	tileRect.bottom = (tile.y+1) * TILESIZE;
	
	return PtInRect(&tileRect, centerPos);

}

int characterClass::cameraWork()
{
	if (_charPos.x > 128) // �� ��ũ�� ����
	{
		_cameraPos = (_charPos.x - 128);

		if (_cameraPos > (_length - SIZEX))	
			_cameraPos = _length - SIZEX;
		
	}
	else
	{
		_cameraPos = 0;
	}
	_cameraPos = _cameraPos*-1;
	return _cameraPos;
}

int characterClass::mapHitcheck()
{
	/* ------------------------------------------------------------ */
	/* X�� �񱳴� ����Ű �Է½ÿ��� �ϰ� ���⼭�� �� ���� �ִ����� üũ */
	/* ------------------------------------------------------------ */

	


	_viTileData = MapData->getMap()->begin();
	for (_viTileData; _viTileData != MapData->getMap()->end(); ++_viTileData)
	{
		switch (_viTileData->_attID - 1)
		{
		case EVENT:
			switch (_viTileData->_tileID)
			{
			case PLAYER: // �÷��̾� ������
				break;
			case NPC: // NPC ������
				break;
			case ZONE: // �� �̵� ��. ���⼭�� �̰͸� üũ
				if (eventCheck(_viTileData->_pos, 0)) // �Ϲ� �̵�
				{
					_warpPoint._attID = _viTileData->_attID;
					_warpPoint._event = _viTileData->_event;
					_warpPoint._pos = _viTileData->_pos;
					_warpPoint._reverse = _viTileData->_reverse;
					_warpPoint._tileID = _viTileData->_tileID;
					return 1;
				}

				if (_status == UP && _fallJam)
				{
					if (eventCheck(_viTileData->_pos, 1)) // �� �̵�
					{
						_charPos.y += MOVESPEED; // ���� �� �̵��� FALLDWON�� ���� �ȵǴ� ���¿����� �Ǳ� ������ �ϴ� �̵����� �ٽ� �ǵ��� ���´�

						_warpPoint._attID = _viTileData->_attID;
						_warpPoint._event = _viTileData->_event;
						_warpPoint._pos = _viTileData->_pos;
						_warpPoint._reverse = _viTileData->_reverse;
						_warpPoint._tileID = _viTileData->_tileID;
						return 1;
					}
				}
				break;
			}
			break;
		}
	}

	_viTileData = MapData->getMap()->begin();
	_status = FALLDOWN;
	for (_viTileData; _viTileData != MapData->getMap()->end(); ++_viTileData)
	{
		if (_status == STAND)
			break;
		switch (_viTileData->_attID - 1)
		{
		
		case BLOCK: // �� Ÿ�ϰ� Y�� �浹 üũ
			if (_viTileData->_pos.x >= ((_charPos.x + _hitBox.left) / SPRITESIZE) && _viTileData->_pos.x <= (_charPos.x + _hitBox.right) / SPRITESIZE)
			{
				if ((_charPos.y + _hitBox.bottom + _falldownWeight) >= _viTileData->_pos.y * SPRITESIZE &&
					(_charPos.y + _hitBox.bottom + _falldownWeight) <= (_viTileData->_pos.y+1) * SPRITESIZE)
				{
					_status = STAND; //
					_falldownWeight = 0;
				}
				else
				{
					_status = FALLDOWN;
					if (_falldownWeight == 0)
						_falldownWeight = 1.f;
				}
			}
			break;
		case WALL: // �� Ÿ�ϰ� Y�� �浹 üũ
			if (_viTileData->_pos.x >= ((_charPos.x + _hitBox.left) / SPRITESIZE) && _viTileData->_pos.x <= (_charPos.x + _hitBox.right) / SPRITESIZE)
			{
				if ((_charPos.y + _hitBox.bottom + _falldownWeight) >= _viTileData->_pos.y * SPRITESIZE &&
					(_charPos.y + _hitBox.bottom + _falldownWeight) <= (_viTileData->_pos.y + 1) * SPRITESIZE)
				{
					_status = STAND; // �ε����ٴ°Ŵ� �� ����
					_falldownWeight = 0;
				}
				else
				{
					_status = FALLDOWN;
					if (_falldownWeight == 0)
						_falldownWeight = 1.f;
				}
			}
			break;


		case EVENT:
			switch (_viTileData->_tileID)
			{
			case PLAYER: // �÷��̾� ������
				break;
			case NPC: // NPC ������
				break;
			case ZONE: // �� �̵� ��. ���⼭�� �̰͸� üũ
				if (eventCheck(_viTileData->_pos, 0))
				{
					_warpPoint._attID = _viTileData->_attID;
					_warpPoint._event = _viTileData->_event;
					_warpPoint._pos = _viTileData->_pos;
					_warpPoint._reverse = _viTileData->_reverse;
					_warpPoint._tileID = _viTileData->_tileID;
					return 1;
				}
				break;
			}
			break;
		}
	}

	return 0;
}


void characterClass::charactermove()
{
	switch (_status)
	{
	case LEFT:
		_viewPoint = 1;
		if (_spriteSpeed < 8 * SPRITESPEED)
			_spriteSpeed++;
		else
			_spriteSpeed = 0;

		_charPos.x -= MOVESPEED;
		break;
	case RIGHT:
		_viewPoint = 0;
		if (_spriteSpeed < 8 * SPRITESPEED)
			_spriteSpeed++;
		else
			_spriteSpeed = 0;

		_charPos.x += MOVESPEED;		
		break;

	case UP:
		if (!_fallJam)
		{

		}

		if (_spriteSpeed < 8 * SPRITESPEED)
			_spriteSpeed++;
		else
			_spriteSpeed = 0;

		_charPos.y -= MOVESPEED;

		break;

	case DOWN:
		if (_spriteSpeed < 8 * SPRITESPEED)
			_spriteSpeed++;
		else
			_spriteSpeed = 0;

		_charPos.y += MOVESPEED;

		break;
	}

	
}


void characterClass::bulletinit(POINT pos, int xpow, int ypow)
{
	_bullet._pos = pos;
	_bullet._xmove = xpow;
	_bullet._nextmove = ypow;
}


void characterClass::bulletinit(POINT pos, int xpow, int ypow, int att)
{
	_bullet._pos = pos;
	_bullet._xmove = xpow;
	_bullet._nextmove = ypow;
	_bullet._att = att;
}


void characterClass::bulletupdate()
{
	if (_bullet._pos.y > 300)
		return;
	else
	{
		switch (_bullet._att)
		{
		case 0:
			_bullet._pos.x += _bullet._xmove;
			_bullet._nextmove += 0.5f;
			_bullet._pos.y += (int)(_bullet._nextmove / 2);
			break;
		case 1:
			_bullet._pos.x += _bullet._xmove;
			break;
		}
	}
}



int characterClass::update(int mapend)
{
	/*	-----------------------------
		�÷��̾� ������ ���ۿ� Ű �Է�

		7�� 16�� ���� �߰�
		-----------------------------	*/
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_data->addHP(_data->getHP());
		_data->addLIFE(1);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_data->addHP(-(_data->getHP()/2));
		_data->addLIFE(-1);
	}

	////////////////////////////////////




	/*	-----------------------------
		�������� ��ô�� ��ǥ üũ�� �ӽ� ��ƾ

		7�� 16�� ���� �߰�
		---------------------------------*/

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_viewPoint)
			bulletinit(_charPos, -2, -15, 0);
		else
			bulletinit(_charPos, 2, -15, 0);
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_viewPoint)
			bulletinit(_charPos, -10, 0, 1);
		else
			bulletinit(_charPos, 10, 0, 1);
	}

	bulletupdate();

	///////////////////////////////////////////////





	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _fallJam = !_fallJam;


		if (_status != FALLDOWN || _fallJam)
		{
			_status = STAND;

			if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _status = LEFT;
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))  _status = RIGHT;
			if (KEYMANAGER->isStayKeyDown(VK_UP)) _status = UP;
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))  _status = DOWN;
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) _charPos.y = 0;
			
		}
		else if (_status == FALLDOWN)
		{
			if (_fallJam)
				_falldownWeight = 0;

			_charPos.y += _falldownWeight;
			_falldownWeight += 0.5f;
		}

	charactermove();
	_cameraPos = MapData->getMapPos();

	return mapHitcheck();
}

void characterClass::render(void)
{
	IMAGEMANAGER->frameRender("WALK", getMemDC(), _charPos.x + _cameraPos, _charPos.y, _spriteSpeed / SPRITESPEED, _viewPoint);
	IMAGEMANAGER->render("WEAPON", getMemDC(), _bullet._pos.x, _bullet._pos.y);

	/*	-------------------------------------
		���̺� ������ Ȯ�ο� txtout
		
		�÷��̾� ������ ���� ��������� �ε� �� ���� �� ���̸� Ȯ��
		7�� 20�� ���� ����
		------------------------------------- */

	char temp[50];
	
	sprintf(temp, "HP: %d / SCORE: %d / LIFE: %d", _data->getHP(), _data->getSCORE(), _data->getLIFE());
	
	fontsize(33, RGB(0, 255, 0));
	TextOut(getMemDC(), 0, 0, temp, strlen(temp));

}
