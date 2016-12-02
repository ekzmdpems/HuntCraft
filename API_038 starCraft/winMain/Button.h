#pragma once
#include "gameNode.h"
//��ư�� ������~!

typedef void(*CALLBACK_FUNCTION) (void);

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class Button : public gameNode
{
private:
	//��ư ����
	BUTTONDIRECTION _direction;
	//��ư�� ���� �̹��� �̸��� �̹���
	const char* _imageName;
	image* _image;

	//�浹ü
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	//�ݹ� �Լ� ���� ����
	CALLBACK_FUNCTION _callbackFunction;

public:

	virtual HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	Button();
	~Button();
};

