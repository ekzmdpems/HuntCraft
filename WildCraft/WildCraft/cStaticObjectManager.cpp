#include "stdafx.h"
#include "cStaticObjectManager.h"
#include "cStaticObject.h"
/*
cStaticObjectManager::cStaticObjectManager()
{
}


cStaticObjectManager::~cStaticObjectManager()
{
}
LPD3DXMESH cStaticObjectManager::GetStaticObject(LPSTR szFolder, LPSTR szFilename, D3DXMATRIXA16* pMat)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	if (m_mapStaticObject.find(sFullPath) == m_mapStaticObject.end())
	{
		auto pStaticMesh = new cStaticObject;
		pStaticMesh->LoadObject(sFullPath, pMat);
		m_mapStaticObject[sFullPath] = pStaticMesh;
	}
	return m_mapStaticObject[sFullPath];
}
void cStaticObjectManager::Destroy()
{
	for each(auto it in m_mapXfileObject)
	{
		//it.second->Destroy();
		//SAFE_DELETE(it.second);
	}
}
*/