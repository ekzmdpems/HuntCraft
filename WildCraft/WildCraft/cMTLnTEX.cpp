#include "stdafx.h"
#include "cMTLnTEX.h"


cMTLnTEX::cMTLnTEX()
	: m_pTexture(NULL), m_dwAttrID(0)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
}


cMTLnTEX::~cMTLnTEX()
{
	SAFE_RELEASE(m_pTexture);
}
