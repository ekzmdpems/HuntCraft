#include "stdafx.h"
#include "DemoGame.h"


DemoGame::DemoGame()
{
}


DemoGame::~DemoGame()
{
}


HRESULT DemoGame::init(void)
{
	_flag = GAMEPLAYING;

	_mapDraw = new MapDraw;

	// 7월 16일 추가
	// 시작 좌표를 systemdata.ini의 값을 참조하여 결정함
	_mapDraw->init(INIDATA->loadDataInterger("Data/systemdata", "start", "map"), INIDATA->loadDataInterger("Data/systemdata", "start", "pos"));


	_richter = new characterClass;
	_richter->mapLink(_mapDraw);
	_richter->init(0);
	

	/* 7월 20일 추가 */

	_playerData = new playerData;

	_playerData->reset();

	/*

	switch (startFlag())
	{
	case 0: // 뉴게임
		_playerData->reset();
		break;

	case 1: // 로드게임
		dataLoad();
		break;
	}
	*/


	_richter->statusLink(_playerData);

	return S_OK;
}

void DemoGame::release(void)
{
	SAFE_DELETE(_mapDraw);
	SAFE_DELETE(_richter);
}

void DemoGame::update(void)
{
	switch (_flag)
	{
	case GAMEPLAYING:
		_mapDraw->update();

		if (_richter->update(0))
		{
			_fade = new screenFade;

			// 리히터의 상태에 따라 화면 전환 값을 달리 한다
			_fade->init(_richter->scrollFlag());

			_flag = FADE;
		}

		_mapDraw->mapScroll(_richter->cameraWork());
		break;

	case SAVE: // 세이브 관련 루틴 입력
		if (_saveScene->update(0))
		{
			SAFE_DELETE(_saveScene);
			_flag = GAMEPLAYING;
		}
		break;

	case SHOP: // 상점 관련 루틴 입력

		break;

	case FADE:
		_fade->update();

		if (_fade->fadeCheck() == 1) // 맵 이동 처리
		{
			if ((_richter->zoneGet()._event / 10) == INIDATA->loadDataInterger("Data/systemdata", "save", "map"))
			{
				_flag = SAVE;
				_saveScene = new saveScene;
				_saveScene->statusLink(_playerData);
				_saveScene->init();
			}
			else if ((_richter->zoneGet()._event / 10) == INIDATA->loadDataInterger("Data/systemdata", "shop", "map"))
			{ 
				_flag = SHOP;
			}
			else // 위 상황이 아니라면 맵 이동
			{
				_playerData->setRESTART(_richter->zoneGet()._event); // 7월 20일 추가. 존 시작 시 시작 지점 저장


				_mapDraw->init(_richter->zoneGet()._event / 10, _richter->zoneGet()._event % 10);
				_richter->mapLink(_mapDraw);
				_richter->init(_richter->zoneGet()._event % 10);
				_mapDraw->mapScroll(_richter->cameraWork());
			}
		}
		else if (_fade->fadeCheck() == 2)
		{
			SAFE_DELETE(_fade);
			_flag = GAMEPLAYING;
		}
		break;
	}

	/* 7월 20일 추가*/
	if (KEYMANAGER->isOnceKeyDown('0')) // 데이터 로드 테스트
		dataLoad();

	if (KEYMANAGER->isOnceKeyDown('9')) // 해당 맵 재시작 테스트
	{
		_mapDraw->init(_playerData->getRESTART() / 10, _playerData->getRESTART() % 10);
		_richter->mapLink(_mapDraw);
		_richter->init(_playerData->getRESTART() % 10);
		_mapDraw->mapScroll(_richter->cameraWork());
	}

}

void DemoGame::render(void)
{
	switch (_flag)
	{
	case GAMEPLAYING:
	case FADE:
		_mapDraw->render();
		_richter->render();
		if (_flag == FADE)
			_fade->render();
		break;
	case SAVE:
		_saveScene->render();
		break;
	}
	
	
}




/* 7월 20일 추가 */


void DemoGame::dataLoad()
{
	FILE *fp;
	PLAYERSTATUS temp;

	char Path[300];
	GetCurrentDirectory(300, Path);
	strcat(Path, "\\Data\\save.dat");

	fp = fopen(Path, "rb");
	if (fp == NULL)
	{
		return;
	}

	fread(&temp, sizeof(struct PLAYERSTATUS), 1, fp);

	_playerData->setData(temp);


	fclose(fp);
}
