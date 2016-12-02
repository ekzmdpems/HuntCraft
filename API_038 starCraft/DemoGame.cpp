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

	// 7�� 16�� �߰�
	// ���� ��ǥ�� systemdata.ini�� ���� �����Ͽ� ������
	_mapDraw->init(INIDATA->loadDataInterger("Data/systemdata", "start", "map"), INIDATA->loadDataInterger("Data/systemdata", "start", "pos"));


	_richter = new characterClass;
	_richter->mapLink(_mapDraw);
	_richter->init(0);
	

	/* 7�� 20�� �߰� */

	_playerData = new playerData;

	_playerData->reset();

	/*

	switch (startFlag())
	{
	case 0: // ������
		_playerData->reset();
		break;

	case 1: // �ε����
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

			// �������� ���¿� ���� ȭ�� ��ȯ ���� �޸� �Ѵ�
			_fade->init(_richter->scrollFlag());

			_flag = FADE;
		}

		_mapDraw->mapScroll(_richter->cameraWork());
		break;

	case SAVE: // ���̺� ���� ��ƾ �Է�
		if (_saveScene->update(0))
		{
			SAFE_DELETE(_saveScene);
			_flag = GAMEPLAYING;
		}
		break;

	case SHOP: // ���� ���� ��ƾ �Է�

		break;

	case FADE:
		_fade->update();

		if (_fade->fadeCheck() == 1) // �� �̵� ó��
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
			else // �� ��Ȳ�� �ƴ϶�� �� �̵�
			{
				_playerData->setRESTART(_richter->zoneGet()._event); // 7�� 20�� �߰�. �� ���� �� ���� ���� ����


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

	/* 7�� 20�� �߰�*/
	if (KEYMANAGER->isOnceKeyDown('0')) // ������ �ε� �׽�Ʈ
		dataLoad();

	if (KEYMANAGER->isOnceKeyDown('9')) // �ش� �� ����� �׽�Ʈ
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




/* 7�� 20�� �߰� */


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
