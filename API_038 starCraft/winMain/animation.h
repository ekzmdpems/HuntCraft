#pragma once
#include <vector>
//=========================
//		 애니메이션
//일주일 분을 한시간에 해보자.
//=========================

class animation
{
private:
	typedef std::vector<POINT> frameList;
	typedef std::vector<int> playList;


private:
	int				_frameNum;			//프레임수
	frameList		_vFrameList;		//프레임 위치리스트 
	playList		_vPlayList;			//플레이 리스트

	int				_frameWidth;		//프레임 가로크기
	int				_frameHeight;		//프레임 세로크기

	BOOL			_loop;				//돌림이니?
	float			_frameUpdateSec;	//프레임 업데이트(초 단위)
	float			_elapsedSec;		//지난 프레임(초 단위)

	DWORD			_nowPlayIdx;		//지금 플레이 하고 있는 인덱스
	BOOL			_play;				//재생중이니?

public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);//이미지 총 가로세로크기와 한 프레임의 가로세로 크기로 셋팅

	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);//기본셋팅

	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);//플레이 프레임배열로 셋팅
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);//플레이 프레임시작과 종료로 셋팅

	void setFPS(int framePerSec);//초당 갱신 횟수

	void frameUpdate(float elpasedTime);//프레임 업데이트 타임

	void start(void);			//플레이 시작
	void stop(void);			//플레이 완전 정지
	void pause(void);			//플레이 일시 정지
	void resume(void);			//플레이 다시 시작
	


	//플레이 여부확인
	inline BOOL isPlay(void) { return _play; }

	//프레임 위치를 얻는다
	inline POINT getFramePos(void) { return _vFrameList[_vPlayList[_nowPlayIdx]]; }

	//프레임 가로 크기를 얻는다
	inline int getFrameWidth(void) { return _frameWidth; }

	//프레임 세로 크기를 얻는다.
	inline int getFrameHeight(void) { return _frameHeight; }



	animation(void);
	~animation(void);
};

