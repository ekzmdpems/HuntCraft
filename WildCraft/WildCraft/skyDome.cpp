#include "stdafx.h"
#include "skyDome.h"


skyDome::skyDome(DWORD dwColor)
{
	m_pSkyTex = NULL;
	m_pVBSkyDome = NULL;
	m_pIBSkyDome = NULL;
	m_pSkyDomeVert = NULL;
	m_dwColor = dwColor;
	m_fRadius = 1.0f;
	m_nDtheta = 15;
	m_nDphi = 15;
	m_nNumVertices = 0;
}


skyDome::~skyDome()
{
	SAFE_DELETE_ARRAY(m_pSkyDomeVert);
	SAFE_RELEASE(m_pSkyTex);
	SAFE_RELEASE(m_pVBSkyDome);
	SAFE_RELEASE(m_pIBSkyDome);
}

HRESULT skyDome::SetupVertex()
{
	SAFE_DELETE_ARRAY(m_pSkyDomeVert);
	m_nNumVertices = (int)((360.0f / m_nDtheta)*(90.0f / m_nDphi) * 4);
	m_pSkyDomeVert = new SKYBOXVERTEX[m_nNumVertices];

	int pos = -5;

	int nCnt = 0;
	for (int phi = 0; phi<90; phi += m_nDphi)	// 위도 0~90(반구)
	{
		for (int theta = 0; theta<360; theta += m_nDtheta)	// 경도(0~360)원
		{
			m_pSkyDomeVert[nCnt].p.x = m_fRadius * sin(DegToRad(phi)) * cos(DegToRad(theta));
			m_pSkyDomeVert[nCnt].p.z = m_fRadius * sin(DegToRad(phi)) * sin(DegToRad(theta));
			m_pSkyDomeVert[nCnt].p.y = m_fRadius * cos(DegToRad(phi)) + pos;
			m_pSkyDomeVert[nCnt].diffuse = m_dwColor;
			++nCnt;

			// 위도 증가
			m_pSkyDomeVert[nCnt].p.x = m_fRadius * sin(DegToRad(phi + m_nDphi)) * cos(DegToRad(theta));
			m_pSkyDomeVert[nCnt].p.z = m_fRadius * sin(DegToRad(phi + m_nDphi)) * sin(DegToRad(theta));
			m_pSkyDomeVert[nCnt].p.y = m_fRadius * cos(DegToRad(phi + m_nDphi)) + pos;
			m_pSkyDomeVert[nCnt].diffuse = m_dwColor;
			++nCnt;

			// 경도 증가
			m_pSkyDomeVert[nCnt].p.x = m_fRadius * sin(DegToRad(phi)) * cos(DegToRad(theta + m_nDtheta));
			m_pSkyDomeVert[nCnt].p.z = m_fRadius * sin(DegToRad(phi)) * sin(DegToRad(theta + m_nDtheta));
			m_pSkyDomeVert[nCnt].p.y = m_fRadius * cos(DegToRad(phi)) + pos;
			m_pSkyDomeVert[nCnt].diffuse = m_dwColor;
			++nCnt;

			if (phi > -90 && phi < 90)
			{
				m_pSkyDomeVert[nCnt].p.x = m_fRadius * sin(DegToRad(phi + m_nDphi)) * cos(DegToRad(theta + m_nDtheta));
				m_pSkyDomeVert[nCnt].p.z = m_fRadius * sin(DegToRad(phi + m_nDphi)) * sin(DegToRad(theta + m_nDtheta));
				m_pSkyDomeVert[nCnt].p.y = m_fRadius * cos(DegToRad(phi + m_nDphi)) + pos;
				m_pSkyDomeVert[nCnt].diffuse = m_dwColor;
				++nCnt;
			}
		}
	}

	return S_OK;
}

HRESULT skyDome::InitSkyDome(LPCTSTR strTexName, int dtheta, int dphi, float radius)
{
	m_nDtheta = dtheta;
	m_nDphi = dphi;
	m_fRadius = radius;

	SetupVertex();
	SetupTexture(strTexName);

	return S_OK;
}

HRESULT skyDome::SetupTexture(LPCTSTR strTexName)
{
	m_pstrTex.clear();
	m_pstrTex.insert(0, strTexName);

	SAFE_RELEASE(m_pSkyTex);
	if (m_pstrTex.empty() || m_pstrTex == _T(""))
	{
		m_pSkyTex = NULL;
	}
	else
	{
		if (FAILED(D3DXCreateTextureFromFile(DEVICE, m_pstrTex.c_str(), &m_pSkyTex)))
		{
			m_pSkyTex = NULL;
		}
	}

	return S_OK;
}

void skyDome::SkyRender()
{
	// 카메라 행렬을 얻은후, 이동을 제외한후, 다시 등록한다.
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 mat;
	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	mat = matView;
	matView._41 = matView._42 = matView._43 = 0.0f;
	DEVICE->SetTransform(D3DTS_VIEW, &matView);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//컬링은 양면
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z버퍼 끄기

	DEVICE->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);	//텍스쳐 UV Address를 설정.
	DEVICE->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	DEVICE->SetFVF(D3DFVF_SKYBOXVERTEX);

	DEVICE->SetTexture(0, m_pSkyTex);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, m_nNumVertices - 2, (void*)m_pSkyDomeVert, sizeof(SKYBOXVERTEX));

	// 초기화
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetRenderState(D3DRS_LIGHTING, TRUE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//컬링은 양면
	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	DEVICE->SetTransform(D3DTS_VIEW, &mat);
}
