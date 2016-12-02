#pragma once
#include "gameNode.h"
#include "MapDraw.h"

#include "playerData.h" // 7월 16일


#define SPRITESPEED 5
#define MOVESPEED 10

enum CHARACTERSTATUS
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STAND,
	WALK,
	JUMP,
	FALLDOWN,
	STAIRUP,
	STAIRDOWN,
	INTODOOR
};

enum TILEID
{
	PLAYER,
	NPC,
	ZONE
};

struct BULLET
{
	POINT _pos;
	int _xmove;
	float _nextmove;
	int _att = 0;

};

class characterClass : public gameNode
{
private:
	playerData* _data; // 7월 16일



	BULLET _bullet;

	
	RECT _hitBox;
	RECT _warpBox;

	POINT _charPos;
	int _viewPoint = 0;
	int _spriteSpeed = 0;
	int _status;
	float _falldownWeight = 0.f;

	int _fallJam = 0;
	int _cameraPos;
	int _length;
	//vector<TILEDATA> *_vTileData;
	vector<TILEDATA>::iterator _viTileData;
	TILEDATA _warpPoint;

	MapDraw* MapData;

public:
	HRESULT init(void) { return S_OK; }
	HRESULT init(int);
	void release(void);
	void update(void) {}
	void render(void);

	int update(int);

	int mapHitcheck();
	
	void charactermove();
	
	

	int eventCheck(POINT tile, int);
	TILEDATA zoneGet() { return _warpPoint; }

	int scrollFlag() { if (_status == FALLDOWN) return DOWN; else return (_viewPoint * 10) + _status; }
	//void mapLink(vector<TILEDATA>* mapData) { _vTileData = mapData; }
	void mapLink(MapDraw* mapData) { MapData = mapData; }

	int cameraWork();



	void bulletinit(POINT, int, int);
	void bulletinit(POINT, int, int, int);
	void bulletupdate();

	characterClass();
	~characterClass();


	/*---------------------------------
		7월 20일 이후 추가
	  ---------------------------------*/

	void statusLink(playerData* var) { _data = var; }
	playerData* statusReturn() { return _data; }
};

