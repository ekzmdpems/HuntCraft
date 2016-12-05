#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Object 리소스 관련 클래스 모두 여기있음
// Main 함수에서 OBJECT_MANAGER->Destroy 필요
// AutoRelese는 다른 루틴에서 존재가 필요 할때 씀, 쓰고나면 Drain 필요
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cObject
{
private:
	DWORD m_nRefCount;
public:
	cObject();
	virtual ~cObject();

	void AddRef();
	void Release();
	void AutoRelease();
};

class cObjectManager
{
private:
	SINGLETONE(cObjectManager);
private:
	std::set<cObject*> m_setObject;
public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Destroy();
};
#define OBJECT_MANAGER cObjectManager::GetInstance()


class cAutoReleasePool
{
private:
	SINGLETONE(cAutoReleasePool);
private:
	std::set<cObject*> m_setObjectPool;
public:
	void AddObject(cObject* pObject);
	void Drain();
};
#define AUTO_RELEASE_POOL cAutoReleasePool::GetInstance()
