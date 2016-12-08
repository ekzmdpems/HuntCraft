#pragma once
class skyDome
{
public:

	LPDIRECT3DTEXTURE9			m_pSkyTex;
	LPDIRECT3DVERTEXBUFFER9		m_pVBSkyDome;
	LPDIRECT3DINDEXBUFFER9		m_pIBSkyDome;

	SKYBOXVERTEX		*m_pSkyDomeVert;
	std::wstring		m_pstrTex;						// 2���� �ؽ��� �̸�
	float				m_fRadius;						// ���� ����
	DWORD				m_dwColor;						// �ؽ��İ� ���� ��� �����
	int					m_nNumVertices;					// ���ؽ��� ��
	int					m_nDtheta;						// �浵 (0~360) �� ������
	int					m_nDphi;						// ���� �ݱ���(0~90) ����(-90~90)�̴�. �� ������


public:
	HRESULT InitSkyDome(LPCTSTR strTexName, int dtheta = 15, int dphi = 15, float radius = 1.0f);

	HRESULT SetupVertex();

	HRESULT SetupTexture(LPCTSTR strTexName);

	void SkyRender();		// ���� D3DTS_VIEW �� ����� ���ؼ�, ��ġ�� 0���� �ϰ� ȸ���� �������ش�.	

	skyDome(DWORD dwColor);
	~skyDome();
};

