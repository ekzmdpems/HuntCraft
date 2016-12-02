#pragma once
#include "gameNode.h"
//버튼을 만들자~!

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
	//버튼 방향
	BUTTONDIRECTION _direction;
	//버튼에 쓰일 이미지 이름과 이미지
	const char* _imageName;
	image* _image;

	//충돌체
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	//콜백 함수 원형 선언
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

