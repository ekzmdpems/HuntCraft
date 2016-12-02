#pragma once
#include "gameNode.h"
//==================================================================
//		## bullets ## (총알, 미사일 클래스)
//==================================================================

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float speed;
	float angle;
	bool fire;
	int count;
};

//==================================================================
//		## bullet ## 공용총알 (쏠때마다 한발씩 장전해서 발사 - 자동삭제)
//==================================================================
class bullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;	//총알이미지 이름
	float _range;		//사거리
	float _bulletMax;	//총알 최대 갯수

public:
	//총알이미지이름, 총알갯수, 총알사거리로 초기화
	HRESULT init(char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사 (총알위치, 각도, 속도)
	void fire(float x, float y, float angle, float speed);
	//총알무브
	void move(void);

	//총알삭제
	void removeMissile(int arrNum);

	//총알벡터, 반복자 가져오기
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	bullet() {}
	~bullet() {}
};

//==================================================================
//		## missile ## (missile[10] => 배열처럼 미리장전해두고 총알발사)
//==================================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	//사거리

public:
	//총알갯수, 총알사거리로 초기화
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move(void);

	missile() {}
	~missile() {}
};

//==================================================================
//		## missileM1 ## (쏠때마다 한발씩 장전해서 발사 - 자동삭제)
//==================================================================
class missileM1 : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;		//사거리
	float _bulletMax;	//총알 최대 갯수

public:
	//총알갯수, 총알사거리로 초기화
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move(void);

	//총알삭제
	void removeMissile(int arrNum);

	//총알벡터, 반복자 가져오기
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	missileM1() {}
	~missileM1() {}
};

