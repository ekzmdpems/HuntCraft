#pragma once
class skyDome
{
public:

	LPDIRECT3DTEXTURE9			m_pSkyTex;
	LPDIRECT3DVERTEXBUFFER9		m_pVBSkyDome;
	LPDIRECT3DINDEXBUFFER9		m_pIBSkyDome;

	SKYBOXVERTEX		*m_pSkyDomeVert;
	std::wstring		m_pstrTex;						// 2개의 텍스쳐 이름
	float				m_fRadius;						// 정점 간격
	DWORD				m_dwColor;						// 텍스쳐가 없을 경우 색사용
	int					m_nNumVertices;					// 버텍스의 수
	int					m_nDtheta;						// 경도 (0~360) 의 증가량
	int					m_nDphi;						// 위도 반구시(0~90) 구는(-90~90)이다. 의 증가량


public:
	HRESULT InitSkyDome(LPCTSTR strTexName, int dtheta = 15, int dphi = 15, float radius = 1.0f);

	HRESULT SetupVertex();

	HRESULT SetupTexture(LPCTSTR strTexName);

	void SkyRender();		// 내부 D3DTS_VIEW 의 행렬을 구해서, 위치는 0으로 하고 회전만 적용해준다.	

	skyDome(DWORD dwColor);
	~skyDome();
};

