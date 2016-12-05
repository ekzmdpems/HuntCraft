#include "stdafx.h"
#include "cFrustumCulling.h"


cFrustumCulling::cFrustumCulling()
{
	ZeroMemory(m_Plane, sizeof(D3DXPLANE) * 6);
}


cFrustumCulling::~cFrustumCulling()
{
}

void cFrustumCulling::Update()
{
	D3DXMATRIXA16 matView, matProj, viewProjection;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixMultiply(&viewProjection, &matView, &matProj);

	// Left
	m_Plane[0].a = viewProjection._14 + viewProjection._11;
	m_Plane[0].b = viewProjection._24 + viewProjection._21;
	m_Plane[0].c = viewProjection._34 + viewProjection._31;
	m_Plane[0].d = viewProjection._44 + viewProjection._41;
	// Right
	m_Plane[1].a = viewProjection._14 - viewProjection._11;
	m_Plane[1].b = viewProjection._24 - viewProjection._21;
	m_Plane[1].c = viewProjection._34 - viewProjection._31;
	m_Plane[1].d = viewProjection._44 - viewProjection._41;
	// Top							
	m_Plane[2].a = viewProjection._14 - viewProjection._12;
	m_Plane[2].b = viewProjection._24 - viewProjection._22;
	m_Plane[2].c = viewProjection._34 - viewProjection._32;
	m_Plane[2].d = viewProjection._44 - viewProjection._42;
	// Bottom
	m_Plane[3].a = viewProjection._14 + viewProjection._12;
	m_Plane[3].b = viewProjection._24 + viewProjection._22;
	m_Plane[3].c = viewProjection._34 + viewProjection._32;
	m_Plane[3].d = viewProjection._44 + viewProjection._42;
	// Near
	m_Plane[4].a = viewProjection._13;
	m_Plane[4].b = viewProjection._23;
	m_Plane[4].c = viewProjection._33;
	m_Plane[4].d = viewProjection._43;
	// Far
	m_Plane[5].a = viewProjection._14 + viewProjection._13;
	m_Plane[5].b = viewProjection._24 + viewProjection._23;
	m_Plane[5].c = viewProjection._34 + viewProjection._33;
	m_Plane[5].d = viewProjection._44 + viewProjection._43;

	for (int i = 0; i < 6; i++)
	{
		D3DXPlaneNormalize(&m_Plane[i], &m_Plane[i]);
	}
}

const bool cFrustumCulling::Intersect(const ST_BOUNDOBJECT* s) const
{
	for (int i = 0; i < 6; i++)
		if (!s->IsInsect(m_Plane[i]))	return false;
	return true;
}