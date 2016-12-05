#include "stdafx.h"
#include "cDynamicObjectManager.h"
#include "cDynamicObject.h"

cDynamicObjectManager::cDynamicObjectManager()
{
}


cDynamicObjectManager::~cDynamicObjectManager()
{
}


cDynamicObject* cDynamicObjectManager::GetDynamicObject(LPSTR szFolder, LPSTR szFilename, eShaderType e)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string(szFilename);

	if (m_mapDynamicObject.find(sFullPath) == m_mapDynamicObject.end())
	{
		auto pDynamicMesh = new cDynamicObject();
		pDynamicMesh->Load(szFolder, szFilename, e);
		m_mapDynamicObject[sFullPath] = pDynamicMesh;
	}
	return m_mapDynamicObject[sFullPath];
}
void cDynamicObjectManager::Destroy()
{
	for each(auto it in m_mapDynamicObject)
	{
		it.second->Destroy();
		SAFE_DELETE(it.second);
	}
}