#include "stdafx.h"
#include "cSceneManager.h"

iSceneNode* cSceneManager::m_currScene = nullptr;

cSceneManager::cSceneManager()
{
}

cSceneManager::~cSceneManager()
{
}

void cSceneManager::Update()
{
	if (m_currScene != nullptr) m_currScene->Update();
}
void cSceneManager::Render()
{
	if (m_currScene != nullptr)	m_currScene->Render();
}
void cSceneManager::Destroy()
{
	if (m_currScene != nullptr) m_currScene->Release();
	for each(auto m in m_mapScenes)
	{
		SAFE_DELETE(m.second);
	}
}

iSceneNode* cSceneManager::AddScene(std::string sName, iSceneNode* scene)
{
	m_mapScenes.insert(std::make_pair(sName, scene));
	return scene;
}
void cSceneManager::ChangeScene(std::string sName, DWORD dFlag)
{
	if (m_mapScenes[sName] == m_currScene || m_mapScenes[sName] == nullptr)
	{
		return;
	}
	assert(SUCCEEDED(m_mapScenes[sName]->Init(dFlag)) && "SCENE 초기화에 실패했습니다.");
	if (m_currScene != nullptr) m_currScene->Release();
	m_currScene = m_mapScenes[sName];
}
void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_currScene != nullptr)	m_currScene->WndProc(hWnd, message, wParam, lParam);
}
