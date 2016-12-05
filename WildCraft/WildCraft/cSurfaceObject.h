#pragma once
class cSurfaceObject : public cObject
{
	LPD3DXMESH		m_pMesh;
	SYNTHESIZE_S(LPD3DXEFFECT, m_pEffect, Shader);		// 쉐이더는 세팅만 가능함
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPosition, Position);
public:
	cSurfaceObject(LPSTR szTexturePath, LPSTR szHeightMapPath
		, int numVertsPerRow, int numVertsPerCol, int cellSpacing);
	void Render();
	bool GetHeight(IN float x,OUT float& y,IN float z);

private:
	cSurfaceObject();
	~cSurfaceObject();
};

