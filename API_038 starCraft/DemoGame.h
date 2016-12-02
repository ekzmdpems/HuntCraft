#pragma once
#include "gameNode.h"


/* ------------------------- */
/*       게임용 개발 헤더     */
/* ------------------------- */
#include "MapDraw.h"
#include "characterClass.h"
#include "screenFade.h"
#include "saveScene.h"
#include "playerData.h"

enum FLAG
{
	NONE,
	GAMEPLAYING,
	FADE,
	SAVE,
	SHOP
};

class DemoGame:public gameNode
{
private:
	saveScene* _saveScene;
	MapDraw* _mapDraw;
	characterClass* _richter;
	screenFade* _fade;
	
	playerData* _playerData; // 7월 20일 추가


	int _flag;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	

	DemoGame();
	~DemoGame();






	/* 7월 20일 추가*/
	void dataLoad();
};

