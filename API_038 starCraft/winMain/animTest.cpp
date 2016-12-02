#include "stdafx.h"
#include "animTest.h"


animTest::animTest()
{
}


animTest::~animTest()
{

}

HRESULT animTest::init(void)
{
	//낙타이미지
	_camel = IMAGEMANAGER->addImage("camel", "IU.bmp", 800, 800, true, RGB(255, 0, 255));
	_camel2 = IMAGEMANAGER->addImage("camel1", "IU.bmp", 800, 800, true, RGB(255, 0, 255));
	_camel3 = IMAGEMANAGER->addImage("camel2", "IU.bmp", 800, 800, true, RGB(255, 0, 255));


	//애니메이션 테스트1
	_ani = new animation;
	_ani->init(_camel->getWidth(), _camel->getHeight(), 200, 200);
	_ani->setDefPlayFrame(false, false);
	_ani->setFPS(100);


	//애니메이션 테스트2	시작과끝
	_ani2 = new animation;
	_ani2->init(_camel2->getWidth(), _camel2->getHeight(), 200, 200);
	_ani2->setPlayFrame(5,8,false, true);
	_ani2->setFPS(500);

	//에니메이션 테스트3	배열~(이게 쩜)
	int arrAni[] = { 10, 13, 14, 15 };
	_ani3 = new animation;
	_ani3->init(_camel3->getWidth(), _camel3->getHeight(), 200, 200);
	_ani3->setPlayFrame(arrAni, 4, true);
	_ani3->setFPS(5);

	return S_OK;
}

void animTest::release(void)
{
	SAFE_DELETE(_ani);
	SAFE_DELETE(_ani2);

	SAFE_DELETE(_ani3);

}

void animTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_ani->start();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_ani2->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_ani3->start();
	}

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() );
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() );
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() );
}

void animTest::render(void)
{
	_camel->aniRender(getMemDC(), 100, 200, _ani);
	_camel2->aniRender(getMemDC(), 300, 200, _ani2);
	_camel3->aniRender(getMemDC(), 500, 200, _ani3);
}



