#include "stdafx.h"
#include "Button.h"


Button::Button()
{
}


Button::~Button()
{
}


HRESULT Button::init(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction)
{
	gameNode::init();

	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	
	//버튼 초기화.
	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnDownFramePoint = btnDownFramePoint;
	_btnUpFramePoint = btnUpFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());


	return S_OK;
}
void Button::release(void)
{
	gameNode::release();


}
void Button::update(void)
{
	gameNode::update();

	if (PtInRect(&_rc, _ptMouse))
	{
		if (_leftButtonDown)
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (!_leftButtonDown && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction();
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void Button::render(void)
{
	switch (_direction)
	{
	case BUTTONDIRECTION_NULL : case BUTTONDIRECTION_UP:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
	case BUTTONDIRECTION_DOWN:
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);
		break;
	}

}