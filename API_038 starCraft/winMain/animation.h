#pragma once
#include <vector>
//=========================
//		 �ִϸ��̼�
//������ ���� �ѽð��� �غ���.
//=========================

class animation
{
private:
	typedef std::vector<POINT> frameList;
	typedef std::vector<int> playList;


private:
	int				_frameNum;			//�����Ӽ�
	frameList		_vFrameList;		//������ ��ġ����Ʈ 
	playList		_vPlayList;			//�÷��� ����Ʈ

	int				_frameWidth;		//������ ����ũ��
	int				_frameHeight;		//������ ����ũ��

	BOOL			_loop;				//�����̴�?
	float			_frameUpdateSec;	//������ ������Ʈ(�� ����)
	float			_elapsedSec;		//���� ������(�� ����)

	DWORD			_nowPlayIdx;		//���� �÷��� �ϰ� �ִ� �ε���
	BOOL			_play;				//������̴�?

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);//�̹��� �� ���μ���ũ��� �� �������� ���μ��� ũ��� ����

	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);//�⺻����

	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);//�÷��� �����ӹ迭�� ����
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);//�÷��� �����ӽ��۰� ����� ����

	void setFPS(int framePerSec);//�ʴ� ���� Ƚ��

	void frameUpdate(float elpasedTime);//������ ������Ʈ Ÿ��

	void start(void);			//�÷��� ����
	void stop(void);			//�÷��� ���� ����
	void pause(void);			//�÷��� �Ͻ� ����
	void resume(void);			//�÷��� �ٽ� ����
	


	//�÷��� ����Ȯ��
	inline BOOL isPlay(void) { return _play; }

	//������ ��ġ�� ��´�
	inline POINT getFramePos(void) { return _vFrameList[_vPlayList[_nowPlayIdx]]; }

	//������ ���� ũ�⸦ ��´�
	inline int getFrameWidth(void) { return _frameWidth; }

	//������ ���� ũ�⸦ ��´�.
	inline int getFrameHeight(void) { return _frameHeight; }



	animation(void);
	~animation(void);
};

