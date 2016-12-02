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
	/* 기본 변수 초기화. 전부 0으로       */
	/* ----------------------------------*/
	_charPos.x = 0;
	_charPos.y = 0;
	//_falldownWeight = 0;
	_cameraPos = 0;


	_status = STAND;

	/* ----------------------------------------*/
	/* 충돌 판정용 히트 박스 초기화 일단 한개    */
	/* ----------------------------------------*/
	_hitBox.left = 5;
	_hitBox.right = 27;
	_hitBox.top = 0;
	_hitBox.bottom = 43;


	// 존 이동용 워프 박스 설정. 대충 캐릭터 중앙에 16x16으로...

	_warpBox.left = 9;
	_warpBox.right = 25;
	_warpBox.top = 13;
	_warpBox.bottom = 29;




	/* --------------------------------------------------------

		[플레이어 시작 위치 설정]
		init()의 인수로 들어온 좌표 ID(타일의 _event값)를 찾아
		해당 타일 위에 플레이어 캐릭터를 그린다.

		현재 소스에서는 시작 타일을 발끝으로 하기 때문에

		((이벤트 타일 좌표 + 1) * 타일 크기) - 캐릭터 스프라이트의 세로 크기

		한 좌표를 플레이어의 Y좌표로 삼는다.

		
		플레이어 몬스터 캐릭터의 자기 위치 찾는 절차는

		1. 타일의 속성값이 이벤트인 타일을 찾는다 ( _viTileData->_attID == EVENT )
		2. 타일의 ID값으로 플레이어 타일인지 NPC(몬스터) 타일인지 찾는다 ( _viTileData->_tileID, 0 : 플레이어, 1 : NPC, 2 : 맵 이동용)
		3. 타일의 이벤트값에 맞춰 캐릭터를 베치한다( _viTileData->_event, 플레이어는 시작 좌표, NPC는 각각의 ID )

		* 현재 2번째 맵에 NPC 0, 1번이 배치되도록 되어있음.

		-------------------------------------------------------- */

	_viTileData = MapData->getMap()->begin();
	_length = MapData->mapsize();
	for (_viTileData; _viTileData != MapData->getMap()->end(); ++_viTileData)
	{
		


		if ((_viTileData->_attID -1) == EVENT) // 블럭 타일인 경우에만 충돌 처리
		{
			switch (_viTileData->_tileID) 
			{
			case PLAYER: // 플레이어
				if (_viTileData->_event == pos)
				{
					_charPos.x = _viTileData->_pos.x * TILESIZE;
					_charPos.y = ((_viTileData->_pos.y+1) * TILESIZE)- _hitBox.bottom;
				}
				break;
			case NPC: // NPC

				break;
			case EVENT: // 존 이동
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
		맵 이동용 충돌 처리 루틴
		ptinrect를 쓴다
		7월 16일 이후 문에 들어가는 루틴 추가
		----------------------------------------------- */

	POINT centerPos;
	RECT tileRect;

	if (!flag) // 그냥 충돌 처리(일반적인 맵 이동) 
	{
		centerPos.x = _charPos.x + 17;
		centerPos.y = _charPos.y + 21; 
	}
	else // 방향키를 위로 올렸다면 문 체크
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
	if (_charPos.x > 128) // 맵 스크롤 시작
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
	/* X축 비교는 방향키 입력시에만 하고 여기서는 땅 위에 있는지만 체크 */
	/* ------------------------------------------------------------ */

	


	_viTileData = MapData->getMap()->begin();
	for (_viTileData; _viTileData != MapData->getMap()->end(); ++_viTileData)
	{
		switch (_viTileData->_attID - 1)
		{
		case EVENT:
			switch (_viTileData->_tileID)
			{
			case PLAYER: // 플레이어 생성용
				break;
			case NPC: // NPC 생성용
				break;
			case ZONE: // 존 이동 용. 여기서는 이것만 체크
				if (eventCheck(_viTileData->_pos, 0)) // 일반 이동
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
					if (eventCheck(_viTileData->_pos, 1)) // 문 이동
					{
						_charPos.y += MOVESPEED; // 현재 문 이동은 FALLDWON이 적용 안되는 상태에서만 되기 때문에 일단 이동값을 다시 되돌려 놓는다

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
		
		case BLOCK: // 블럭 타일과 Y축 충돌 체크
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
		case WALL: // 블럭 타일과 Y축 충돌 체크
			if (_viTileData->_pos.x >= ((_charPos.x + _hitBox.left) / SPRITESIZE) && _viTileData->_pos.x <= (_charPos.x + _hitBox.right) / SPRITESIZE)
			{
				if ((_charPos.y + _hitBox.bottom + _falldownWeight) >= _viTileData->_pos.y * SPRITESIZE &&
					(_charPos.y + _hitBox.bottom + _falldownWeight) <= (_viTileData->_pos.y + 1) * SPRITESIZE)
				{
					_status = STAND; // 부딪혔다는거니 걍 리턴
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
			case PLAYER: // 플레이어 생성용
				break;
			case NPC: // NPC 생성용
				break;
			case ZONE: // 존 이동 용. 여기서는 이것만 체크
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
		플레이어 데이터 조작용 키 입력

		7월 16일 이후 추가
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
		보조무기 투척시 좌표 체크용 임시 루틴

		7월 16일 이후 추가
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
		세이브 데이터 확인용 txtout
		
		플레이어 데이터 값을 출력함으로 로드 전 후의 값 차이를 확인
		7월 20일 이후 변경
		------------------------------------- */

	char temp[50];
	
	sprintf(temp, "HP: %d / SCORE: %d / LIFE: %d", _data->getHP(), _data->getSCORE(), _data->getLIFE());
	
	fontsize(33, RGB(0, 255, 0));
	TextOut(getMemDC(), 0, 0, temp, strlen(temp));

}
