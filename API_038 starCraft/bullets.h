#pragma once
#include "gameNode.h"
//==================================================================
//		## bullets ## (�Ѿ�, �̻��� Ŭ����)
//==================================================================

//�Ѿ� ����ü
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
//		## bullet ## �����Ѿ� (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
class bullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;	//�Ѿ��̹��� �̸�
	float _range;		//��Ÿ�
	float _bulletMax;	//�Ѿ� �ִ� ����

public:
	//�Ѿ��̹����̸�, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻� (�Ѿ���ġ, ����, �ӵ�)
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move(void);

	//�Ѿ˻���
	void removeMissile(int arrNum);

	//�Ѿ˺���, �ݺ��� ��������
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	bullet() {}
	~bullet() {}
};

//==================================================================
//		## missile ## (missile[10] => �迭ó�� �̸������صΰ� �Ѿ˹߻�)
//==================================================================
class missile : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	//��Ÿ�

public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move(void);

	missile() {}
	~missile() {}
};

//==================================================================
//		## missileM1 ## (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
class missileM1 : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;		//��Ÿ�
	float _bulletMax;	//�Ѿ� �ִ� ����

public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move(void);

	//�Ѿ˻���
	void removeMissile(int arrNum);

	//�Ѿ˺���, �ݺ��� ��������
	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	missileM1() {}
	~missileM1() {}
};

