#include "stdafx.h"
#include "cActionMove.h"
#include "cGameObject.h"

cActionMove::cActionMove(void)
	: m_vFrom(0, 0, 0)
	, m_vTo(0, 0, 0)
{
}

cActionMove::~cActionMove(void)
{
}

void cActionMove::Start()
{
	m_fPassedActionTime = 0.0f;
	if (m_pTarget)
	{
		m_pTarget->SetPosition(m_vFrom);
	}
}

void cActionMove::Update()
{
	m_fPassedActionTime += TIME_MANAGER->GetDeltaTime();
	float t = m_fPassedActionTime / m_fActionTime;

	if (t > 1.0f)
	{
		t = 1.0f;
		if (m_pDelegate)
		{
			m_pDelegate->OnActionFinish(this);
		}
	}

	D3DXVECTOR3 p(0, 0, 0);
	D3DXVec3Lerp(&p, &m_vFrom, &m_vTo, t);
	if (m_pTarget)
	{
		// 타겟의 방향 설정
		m_pTarget->SetPosition(p);
	}
}
