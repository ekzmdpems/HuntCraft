#include "stdafx.h"
#include "cGameObject.h"
#include "cAction.h"

cGameObject::cGameObject(void)
	: m_vPosition(0, 0, 0)
	, m_pAction(nullptr)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cGameObject::~cGameObject(void)
{
	SAFE_RELEASE(m_pAction);
}

void cGameObject::Update()
{
	if (m_pAction)
		m_pAction->Update();

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixLookAtLH(&matR,
		&D3DXVECTOR3(0, 0, 0),
		&m_vDirection,
		&D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&matR, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	
	m_matWorld = matR * matT;
}

void cGameObject::Render()
{

}
