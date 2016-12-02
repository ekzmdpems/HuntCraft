#include "stdafx.h"
#include "animation.h"


animation::animation()
	:_frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIdx(0),
	_play(FALSE)
{
}


animation::~animation()
{
}

//�̹��� �� ���μ���ũ��� �� �������� ���μ��� ũ��� ����
HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//���� ������ ��
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//���� ������ ��
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//�� ������ �� ���
	_frameNum = _frameNumWidth * _frameNumHeight;

	//������ ��ġ ����Ʈ ����
	_vFrameList.clear();
	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//������ ��ġ ����Ʈ�� �߰�
			_vFrameList.push_back(framePos);
		}
	}

	//�⺻ ������ ���� ����
	setDefPlayFrame();

	return S_OK;
}



//�⺻ ����
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//���� ���� ����
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_vPlayList.clear();

	//�ٽ� �ǵ��� ���� �ִϸ��̼��̶��...
	if (reverse)
	{
		//���� �ִϸ��̼��̸�...
		if (_loop)
		{
			//���� ������
			for (int i = 0; i < _frameNum; i++)
			{
				_vPlayList.push_back(i);
			}

			//�ö� ������
			for (int i = _frameNum - 2; i > 0; i--)		// �����⶧���� ������ ���� �������� ������.
			{
				_vPlayList.push_back(i);
			}
		}
		//���� �ִϸ��̼��� �ƴϸ�..
		else
		{
			//���� ������
			for (int i = 0; i < _frameNum; i++)
			{
				_vPlayList.push_back(i);
			}

			//�ö� ������
			for (int i = _frameNum - 2; i > 0; i--)		// ������ �ƴϱ� ������ ������ ���� ������ ���� ����
			{
				_vPlayList.push_back(i);
			}
		}
	}

	//�ٽ� �ǵ��� ���� �ִϸ��̼��� �ƴ϶��..
	else
	{
		//���� ����
		for (int i = 0; i < _frameNum; i++)
		{
			_vPlayList.push_back(i);
		}
	}
}

//�÷��� �����ӹ迭�� ����
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{

	//���� ���� ����
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_vPlayList.clear();

	//�����ϰ� ���������� ����
	for (int i = 0; i < arrLen; i++)
	{
		_vPlayList.push_back(playArr[i]);
	}
}

//�÷��� �����ӽ��۰� ����� ����
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	//���� ���� ����
	_loop = loop;

	//�÷��� ����Ʈ Ŭ����
	_vPlayList.clear();

	if (start == end)
	{
		//���������Ӱ� ���������� �������
		_vPlayList.clear();
		stop();			//�ִϸ��̼� ������ �� �ʿ䰡 ����.
		return;
	}


	//���� �������� ���� ������ ���� ū��� 
	if (start > end)
	{
		//�ٽ� �ǵ��� ���� �ִϸ��̼��̶��...
		if (reverse)
		{
			//���� �ִϸ��̼��̸�...
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_vPlayList.push_back(i);
				}

				for (int i = end + 1; i < start; i++)
				{
					_vPlayList.push_back(i);
				}

			}

			//���� �ִϸ��̼��� �ƴϸ�..
			else
			{
				for (int i = start; i >= end; i--)
				{
					_vPlayList.push_back(i);
				}

				for (int i = end + 1; i <= start; i++)
				{
					_vPlayList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i >= end; i--)
			{
				_vPlayList.push_back(i);
			}
		}
	}
	else
	{
		//�ٽ� �ǵ��� ���� �ִϸ��̼��̶��...
		if (reverse)
		{
			//���� �ִϸ��̼��̸�...
			if (_loop)
			{
				for (int i = start; i <= end; i++)
				{
					_vPlayList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_vPlayList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i <= end; i++)
				{
					_vPlayList.push_back(i);
				}

				for (int i = end - 1; i >= start; i--)
				{
					_vPlayList.push_back(i);
				}
			}
		}
		else
		{
			for (int i = start; i <= end; i++)
			{
				_vPlayList.push_back(i);
			}
		}
	}
}
//�ʴ� ���� Ƚ��
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//������ ������Ʈ Ÿ��
void animation::frameUpdate(float elpasedTime)
{
	if (_play)
	{
		_elapsedSec += elpasedTime;
		//������ ������Ʈ �ð��� �Ǿ��ٸ�..
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _vPlayList.size())
			{
				//���� �÷��� ���..
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				//���� �÷��̰� �ƴ϶��..
				else
				{
					_nowPlayIdx--;
					_play = FALSE;
				}
			}
		}
	}
}


//�÷��� ����
void animation::start(void)
{
	_play = TRUE;
	_nowPlayIdx = 0;
}

//�÷��� ���� ����
void animation::stop(void)
{
	_play = FALSE;
	_nowPlayIdx = 0;
}

//�÷��� �Ͻ� ����
void animation::pause(void)
{
	_play = FALSE;
}

//�÷��� �ٽ� ����
void animation::resume(void)
{
	_play = TRUE;
}