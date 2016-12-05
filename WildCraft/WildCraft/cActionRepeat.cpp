#include "stdafx.h"
#include "cActionRepeat.h"


cActionRepeat::cActionRepeat(void)
	: m_pAction(NULL)
{
}

cActionRepeat::~cActionRepeat(void)
{
	SAFE_RELEASE(m_pAction);
}

void cActionRepeat::Update()
{
	if (m_pAction)
	{
		m_pAction->Update();
	}
}

void cActionRepeat::OnActionFinish(cAction* pAction)
{
	if (m_pAction)
	{
		m_pAction->Start();
	}
}
