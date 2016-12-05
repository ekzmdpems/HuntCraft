#include "stdafx.h"
#include "cRay.h"



cRay::cRay(void)
	: m_vRayPos(0, 0, 0)
	, m_vRayDir(0, 0, 1)
{
}


cRay::~cRay(void)
{
}

cRay cRay::RayAtViewSpace(int x, int y)
{
	D3DVIEWPORT9 vp;
	DEVICE->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;
	r.m_vRayPos = D3DXVECTOR3(0, 0, 0);
	r.m_vRayDir.x = (2.0f * x / vp.Width - 1.0f) / matProj._11;
	r.m_vRayDir.y = (-2.0f * y / vp.Height + 1.0f) / matProj._22;
	r.m_vRayDir.z = 1.0f;
	return r;
}

cRay cRay::RayAtWorldSpace(int x, int y)
{
	cRay r = cRay::RayAtViewSpace(x, y);

	D3DXMATRIXA16 matView,matInvView;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformNormal(&r.m_vRayDir, &r.m_vRayDir, &matInvView);
	D3DXVec3TransformCoord(&r.m_vRayPos, &r.m_vRayPos, &matInvView);
	return r;
}

const bool cRay::IsPicked(ST_BOUNDOBJECT& s) const
{
	return s.IsPick(m_vRayPos, m_vRayDir);		// 실제 충돌은 해당 객체에서 얻음
}
