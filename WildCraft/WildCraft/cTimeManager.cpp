#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager::cTimeManager()
	: m_dwDeltaTime(0), m_dwLastTimeStamp(0)
	, m_fTimeScale(0), m_Update(nullptr)
	, m_dwFPS(0), m_dwFPScurr(0), m_dwFPSTime(0)
	, m_bFPScounting(false)
	, m_AccurateLastTimeStamp(0)
{
}

cTimeManager::~cTimeManager()
{
}

const HRESULT cTimeManager::Init(bool bAccurate)
{
	m_fTimeScale = 0.001f;
	if (bAccurate)
	{
		__int64 periodFrequency;
		if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)& m_AccurateLastTimeStamp);
			m_fTimeScale = 1.0f / periodFrequency;
			m_Update = &cTimeManager::UpdateQuery;
		}
		else
		{
			m_dwLastTimeStamp = timeGetTime();
			m_Update = &cTimeManager::UpdateTimeGet;
		}
	}
	else
	{
		m_dwLastTimeStamp = GetTickCount();
		m_Update = &cTimeManager::UpdateTick;
	}
	m_dwFPS = m_dwFPScurr = m_dwFPSTime = 0;

	return S_OK;
}

void cTimeManager::UpdateQuery()
{
	__int64 iCurr;
	QueryPerformanceCounter((LARGE_INTEGER*)&iCurr);
	m_dwDeltaTime = ((iCurr - m_AccurateLastTimeStamp) * 1000/m_fTimeScale);
	m_dwLastTimeStamp = iCurr;
}
void cTimeManager::UpdateTimeGet()
{
	DWORD dwCurr = timeGetTime();
	m_dwDeltaTime = (dwCurr - m_dwLastTimeStamp);
	m_dwLastTimeStamp = dwCurr; 
}
void cTimeManager::UpdateTick()
{
	DWORD dwCurr = GetTickCount();
	m_dwDeltaTime = (dwCurr - m_dwLastTimeStamp);
	m_dwLastTimeStamp = dwCurr;
}

void cTimeManager::Update()
{
	(this->*m_Update)();

	if (m_bFPScounting)
	{
		m_dwFPSTime += m_dwDeltaTime;
		if (m_dwFPSTime > 1000)
		{
			m_dwFPSTime -= 1000;
			m_dwFPScurr = m_dwFPS;
			m_dwFPS = 0;
		}
		else
		{
			m_dwFPS++;
		}
	}
}

float cTimeManager::GetDeltaTime()
{
	return m_dwDeltaTime;
}




