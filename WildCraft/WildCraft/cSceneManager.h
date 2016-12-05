#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �� ��ȯ Ŭ����
// iSceneNode ���� �� �ʿ��� ������ ������ dwFlag �� ���� �Ѱ��ְ� �ش� �������� �����ϰ� �ϸ��
// Release() ���� ���� ��ȯ �ɶ� ������� �Ұ͵�, �������� �״�� ������
// �Ҹ��ڿ� Release���� ���ŵ��� �ʴ� �͵� ��� �����������
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
