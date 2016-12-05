#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 시간 관리자
// 초기화 할때  bAccurate 는 정확하게 계산여부,  선택하면 연산이 느려지며 계산이 정확해짐
// bFPScouning 을 TRUE 하면 GetFPS 함수를 통해 DWORD FPS 를 구할 수 있음 
// 정확한 타이머 현재 작동 안됨, 주의
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);
private:
	void(cTimeManager::*m_Update)();	// 타임 셋에 따라 갱신 함수 달라짐
	float m_fTimeScale;

	DWORD m_dwLastTimeStamp;
	DWORD m_dwDeltaTime;

	__int64 m_AccurateLastTimeStamp;
private:
	DWORD m_dwFPSTime;
	DWORD m_dwFPS;
	SYNTHESIZE_G(DWORD, m_dwFPScurr, FPS);
	SYNTHESIZE(bool, m_bFPScounting, FpsEnabled);	// fps 셀거냐 말거냐

public:
	const HRESULT Init(bool bAccurate = false);	// 정확하게 할거면 true 해줌
	void Update();
	float GetDeltaTime();

private:
	void UpdateQuery();
	void UpdateTimeGet();
	void UpdateTick();
};
#define TIME_MANAGER cTimeManager::GetInstance()