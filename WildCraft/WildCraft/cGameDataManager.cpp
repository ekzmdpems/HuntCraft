#include "stdafx.h"
#include "cGameDataManager.h"


cGameDataManager::cGameDataManager()
{
}


cGameDataManager::~cGameDataManager()
{
}

void cGameDataManager::SetSavePath(std::string saveFileName)
{
	m_currPath = saveFileName;
}
void cGameDataManager::AddData(std::string szSection, std::string szKey, std::string szVal)
{
	 m_vecData.push_back(ST_DATA{ szSection,szKey,szVal });
}
void cGameDataManager::AddEnd()
{
	assert(!m_currPath.empty() && "파일 경로 지정하지 않음");
	for (int i = 0; i < m_vecData.size(); i++)
	{
		WritePrivateProfileStringA(m_vecData[i]._Section.c_str(), m_vecData[i]._Key.c_str(), m_vecData[i]._Value.c_str(), m_currPath.c_str());
	}
	m_vecData.clear();
	m_currPath.clear();
}

std::string cGameDataManager::LoadStringData(std::string loadFileName, std::string szSection, std::string szKey)
{
	char ch[1024];
	GetPrivateProfileStringA(szSection.c_str(), szKey.c_str(), "",ch, 1024, loadFileName.c_str());
	return std::string(ch);
}
int cGameDataManager::LoadIntergerData(std::string loadFileName, std::string szSection, std::string szKey)
{
	int data = 0;
	GetPrivateProfileIntA(szSection.c_str(), szKey.c_str(), data, loadFileName.c_str());
	return data;
}

void cGameDataManager::Destroy()
{
}