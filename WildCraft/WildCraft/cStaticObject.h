#pragma once
/*
class cStaticObject : cObject
{
	friend class cStaticObjectManager;

private:
	LPD3DXMESH					m_pMesh;
	LPD3DXEFFECT				m_pShader;
	std::vector<D3DXVECTOR3>	m_vecSurface;

	ST_BOUNDOBJECT				m_BoundObject;
	
public:
	cStaticObject(LPSTR szObjPath, LPSTR szSurface, D3DXMATRIXA16* matWorld);
	~cStaticObject();

	void Render();
	bool GetHeight(IN float x, OUT float& y, IN float z);

private:
	cStaticObject();
	std::map<std::string, cMTLnTEX*> m_mapMtlTex;
	void LoadObject(std::string szPath, IN D3DXMATRIXA16* pmat);
	void LoadSurface(std::string szPath, IN D3DXMATRIXA16* pmat);
	void LoadMtlLib(std::string szPath);
};
*/