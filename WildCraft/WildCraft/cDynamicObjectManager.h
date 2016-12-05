#pragma once
class cDynamicObject;

class cDynamicObjectManager
{
private:
	SINGLETONE(cDynamicObjectManager);
private:
	std::map<std::string, cDynamicObject*> m_mapDynamicObject;
public:
	cDynamicObject* GetDynamicObject(LPSTR szFolder, LPSTR szFilename, eShaderType e);
	void Destroy();
};
#define DYNAMIC_OBJECT_MANAGER cDynamicObjectManager::GetInstance()