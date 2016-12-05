#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 씬 전환 클래스
// iSceneNode 시작 시 필요한 세팅이 있으면 dwFlag 에 값을 넘겨주고 해당 세팅으로 시작하게 하면됨
// Release() 에는 씬이 전환 될때 없애줘야 할것들, 나머지는 그대로 유지됨
// 소멸자에 Release에서 제거되지 않는 것들 모두 제거해줘야함
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class iSceneNode
{
public:
	virtual const HRESULT Init(DWORD dwFlag)			PURE;
	virtual void Update()								PURE;
	virtual void Render()								PURE;
	virtual void Release()								PURE;
	virtual void WndProc(HWND, UINT, WPARAM, LPARAM)	PURE;

	iSceneNode() {};
	virtual ~iSceneNode() {};
};
using LPSCENENODE = iSceneNode*;

class cSceneManager
{
private:
	SINGLETONE(cSceneManager);
private:
	static iSceneNode*					m_currScene;
	std::map<std::string, iSceneNode*>	m_mapScenes;
public:
	void Update();
	void Render();
	void Destroy();
	void WndProc(HWND, UINT, WPARAM, LPARAM);

	iSceneNode* AddScene(std::string sName, iSceneNode* scene);
	void ChangeScene(std::string sName, DWORD dFlag = 0);
};
#define SCENE_MANAGER cSceneManager::GetInstance()
