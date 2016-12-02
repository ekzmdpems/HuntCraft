#include "stdafx.h"
#include "bullets.h"
//==================================================================
//		## bullet ## �����Ѿ� (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
//�Ѿ��̹����̸�, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
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

//�Ѿ˹߻� (�Ѿ���ġ, ����, �ӵ�)
void bullet::fire(float x, float y, float angle, float speed)
{
	//�Ѿ˹߻� ������ �����Ѵ�
	if (_bulletMax < _vBullet.size()) return;

	//�Ѿ˱���ü ������ ���Ϳ� ���
	//�Ѿ� ����ü ����
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

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

//�Ѿ˹���
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

		//�Ѿ��� ��Ÿ����� Ŀ������ �����Ҵ��� �̹��� �� �ݺ��� ����
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

//�Ѿ˻���
void bullet::removeMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

//==================================================================
//		## missile ## (missile[10] => �迭ó�� �̸������صΰ� �Ѿ˹߻�)
//==================================================================
//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
HRESULT missile::init(int bulletMax, float range)
{
	//��Ÿ� �ʱ�ȭ
	_range = range;

	//�Ѿ� ����ü �ʱ�ȭ
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("images/missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		//���Ϳ� ���
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
	//�Ѿ˹���
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

//�Ѿ˹߻�
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

//�Ѿ˹���
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

		//�Ѿ��� ��Ÿ����� Ŀ������
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

//==================================================================
//		## missileM1 ## (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
HRESULT missileM1::init(int bulletMax, float range)
{
	//�Ѿ˰��� ��Ÿ� �ʱ�ȭ
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

//�Ѿ˹߻�
void missileM1::fire(float x, float y)
{
	//�Ѿ˹߻� ������ �����Ѵ�
	if (_bulletMax < _vBullet.size()) return;

	//�Ѿ˱���ü ������ ���Ϳ� ���
	//�Ѿ� ����ü ����
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

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

//�Ѿ˹���
void missileM1::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//�Ѿ��� ��Ÿ����� Ŀ������ �����Ҵ��� �̹��� �� �ݺ��� ����
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//���⼭ ����
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

//�Ѿ˻���
void missileM1::removeMissile(int arrNum)
{
	SAFE_DELETE(_vBullet[arrNum].bulletImage);
	_vBullet.erase(_vBullet.begin() + arrNum);
}