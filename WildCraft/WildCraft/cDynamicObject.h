#pragma once
struct ST_BONE;

class cDynamicObject 
{
	friend class cDynamicObjectManager;
private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	SYNTHESIZE_S(LPD3DXEFFECT,	m_pEffect, Effect);

private:
	ST_SPHERE					m_stBoundingSphere;
	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
	void (cDynamicObject::*m_RenderMode)(ST_BONE* pBone);

public:
	cDynamicObject(LPSTR szFolder, LPSTR szFileName, eShaderType e);
	~cDynamicObject();

	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);
	void SetAnimationIndex(int nIndex);
	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter += v;
	}
private:
	cDynamicObject();
	void Load(LPSTR szFolder, LPSTR szFilename, eShaderType e);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
};

