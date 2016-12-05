#include "stdafx.h"
#include "cCamera.h"



cCamera::cCamera(void)
	: m_eType(eCameraType::RAND)
	, m_vLook(0, 0, 1)
	, m_vRight(1, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPos(0, 0, 0)
	, m_pTarget(nullptr)
	, m_isLButtonDown(false)
	, m_fAngleX(0.0f), m_fAngleY(0.0f)
	, m_fDistance(0.0f)
{
}

cCamera::~cCamera(void)
{
}

void cCamera::Init(eCameraType e)
{
	m_eType = e;
}

void cCamera::Update()
{
	D3DXMATRIXA16 matView;
	if (m_pTarget)
	{
		AngleSet();		//  조정하려면 전역 변수들을 조정할 것
		D3DXMatrixLookAtLH(&matView, &m_vPos, m_pTarget, &m_vUp);
	}
	else
	{
		UpdateKey();	// wasd
		D3DXMatrixLookAtLH(&matView, &m_vPos, &m_vLook, &m_vUp);
	}
	DEVICE->SetTransform(D3DTS_VIEW, &matView);
}
void cCamera::UpdateKey()
{
	if (KEY_ASSISTER->isStayKeyDown('W'))
	{
		//tWalk(0.5f);
	}
	if (KEY_ASSISTER->isStayKeyDown('S'))
	{
		//tWalk(-0.5f);
	}
	if (KEY_ASSISTER->isStayKeyDown('A'))
	{
		//rYaw(-0.01f);
	}
	if (KEY_ASSISTER->isStayKeyDown('D'))
	{
		//rYaw(0.01f);
	}
	if (KEY_ASSISTER->isStayKeyDown('Q'))
	{
		//tFly(0.5f);
	}
	if (KEY_ASSISTER->isStayKeyDown('E'))
	{
		//tFly(-0.5f);
	}
}
void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_pTarget  && m_isLButtonDown)
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			auto AngleMax = D3DX_PI / 2.0f - EPSILON;

			int nDeltaX = pt.x - m_ptPrevMouse.x;
			int nDeltaY = pt.y - m_ptPrevMouse.y;

			m_fAngleX += nDeltaY * 0.01f;
			if (m_fAngleX > AngleMax)	m_fAngleX = AngleMax;
			else if (m_fAngleX < -AngleMax)	m_fAngleX = -AngleMax;
			m_fAngleY -= nDeltaX * 0.01f;
			m_ptPrevMouse = pt;
		}
	}
	break;
	case WM_MOUSEWHEEL:
	{
		int n = GET_WHEEL_DELTA_WPARAM(wParam);
		if (m_pTarget)
		{
			m_fDistance -= n / 100.f;
		}
	}
	break;
	}
}

void cCamera::AngleSet()
{
	D3DXMATRIXA16 matRX, matRY, mat;
	D3DXMatrixRotationX(&matRX, m_fAngleX);
	D3DXMatrixRotationY(&matRY, m_fAngleY);		// 실질 맥스 행렬로 함

	mat = matRX * matRY;
	D3DXVec3TransformCoord(&m_vLook, &D3DXVECTOR3(0, 0, 1), &mat);
	D3DXVec3Normalize(&m_vLook, &m_vLook);

	D3DXVec3TransformCoord(&m_vRight, &D3DXVECTOR3(1, 0, 0), &mat);
	D3DXVec3Normalize(&m_vRight, &m_vRight);

	D3DXVec3TransformCoord(&m_vUp, &D3DXVECTOR3(0, 1, 0), &mat);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	D3DXVec3TransformCoord(&m_vPos, &D3DXVECTOR3(0, 0, m_fDistance), &mat);
	if(m_pTarget) m_vPos = m_vPos + *m_pTarget;
}

void cCamera::tStrafe(float fUnit)
{
	if (m_eType == eCameraType::RAND)
	{
		m_vPos += D3DXVECTOR3(m_vRight.x, 0, m_vRight.z) * fUnit;
	}
	else
	{
		m_vPos += m_vRight * fUnit;
	}
}
void cCamera::tFly(float fUnit)
{
	if (m_eType == eCameraType::AIR)
	{
		m_vPos += m_vUp * fUnit;
	}
}
void cCamera::tWalk(float fUnit)
{
	if (m_eType == eCameraType::RAND)
	{
		D3DXVECTOR3 dir;
		D3DXVec3Cross(&dir, &m_vRight, &D3DXVECTOR3(0, 1, 0));
		m_vPos += D3DXVECTOR3(dir.x, 0, dir.z) * fUnit;
	}
	else
	{
		m_vPos += m_vLook * fUnit;
	}
}

void cCamera::rPitch(float fAngle)	// 오른쪽 기준으로 고개 까닥까닥
{
	D3DXMATRIXA16 mat;
	D3DXMatrixRotationAxis(&mat, &m_vRight, fAngle);
	
	D3DXVec3TransformCoord(&m_vUp, &m_vUp, &mat);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	D3DXVec3TransformCoord(&m_vLook, &m_vLook, &mat);
	D3DXVec3Normalize(&m_vLook, &m_vLook);
}
void cCamera::rYaw(float fAngle)					// 수평 회전 
{
	D3DXMATRIXA16 mat;
	if (m_eType == eCameraType::RAND)		// 지상 모드
	{
		D3DXMatrixRotationY(&mat, fAngle);
	}
	else									// 공중 모드
	{
		D3DXMatrixRotationAxis(&mat, &m_vUp, fAngle);
	}
	D3DXVec3TransformCoord(&m_vRight, &m_vRight, &mat);
	D3DXVec3Normalize(&m_vRight, &m_vRight);

	D3DXVec3TransformCoord(&m_vLook, &m_vLook, &mat);
	D3DXVec3Normalize(&m_vLook, &m_vLook);
}
void cCamera::rRoll(float fAngle)		// 기울이기, 비행모드만 가능
{
	if (m_eType == eCameraType::AIR)		
	{
		D3DXMATRIXA16 mat;
		D3DXMatrixRotationAxis(&mat, &m_vLook, fAngle);
		
		D3DXVec3TransformCoord(&m_vRight, &m_vRight, &mat);
		D3DXVec3Normalize(&m_vRight, &m_vRight);

		D3DXVec3TransformCoord(&m_vUp, &m_vUp, &mat);
		D3DXVec3Normalize(&m_vUp, &m_vUp);
	}
}