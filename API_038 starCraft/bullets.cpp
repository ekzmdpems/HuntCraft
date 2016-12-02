#include "stdafx.h"
#include "bullets.h"
//==================================================================
//		## bullet ## 공용총알 (쏠때마다 한발씩 장전해서 발사 - 자동삭제)
//==================================================================
//총알이미지이름, 총알갯수, 총알사거리로 초기화
HRESULT bullet::init(char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release(void)
{
	_vBullet.clear();
}

asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf
void bullet::update(void)
{
	move();
}

void bullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

//총알발사 (총알위치, 각도, 속도)
void bullet::fire(float x, float y, float angle, float speed)
{
	//총알발사 갯수를 제한한다
	if (_bulletMax < _vBullet.size()) return;

	//총알구조체 선언후 벡터에 담기
	//총알 구조체 선언
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

//총알무브
void bullet::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += (-sinf(_viBullet->angle)) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때 동적할당한 이미지 및 반복자 삭제
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

//총알삭제
void bullet::removeMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//==================================================================
//		## missile ## (missile[10] => 배열처럼 미리장전해두고 총알발사)
//==================================================================
//총알갯수, 총알사거리로 초기화
HRESULT missile::init(int bulletMax, float range)
{
	//사거리 초기화
	_range = range;

	//총알 구조체 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("images/missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		//벡터에 담기
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release(void)
{
	_vBullet.clear();
}

void missile::update(void)
{
	//총알무브
	move();
}

void missile::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

//총알발사
void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		break;
	}
}

//총알무브
void missile::move(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//총알이 사거리보다 커졌을때
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

//==================================================================
//		## missileM1 ## (쏠때마다 한발씩 장전해서 발사 - 자동삭제)
//==================================================================
//총알갯수, 총알사거리로 초기화
HRESULT missileM1::init(int bulletMax, float range)
{
	//총알갯수 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void missileM1::release(void)
{
	_vBullet.clear();
}

void missileM1::update(void)
{
	move();
}
void missileM1::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}

}

//총알발사
void missileM1::fire(float x, float y)
{
	//총알발사 갯수를 제한한다
	if (_bulletMax < _vBullet.size()) return;

	//총알구조체 선언후 벡터에 담기
	//총알 구조체 선언
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("images/missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

//총알무브
void missileM1::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//총알이 사거리보다 커졌을때 동적할당한 이미지 및 반복자 삭제
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//여기서 삭제
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

//총알삭제
void missileM1::removeMissile(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}