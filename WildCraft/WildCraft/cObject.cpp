#include "stdafx.h"
#include "cObject.h"


cObject::cObject() : m_nRefCount(1)
{
	OBJECT_MANAGER->AddObject(this);
}

cObject::~cObject()
{
	assert(m_nRefCount == 0 && "잘못된 해제가 발생했습니다.");
	OBJECT_MANAGER->RemoveObject(this);
}

void cObject::AddRef()
{
	assert(m_nRefCount != INT_MAX && "RefCount가 사용 가능한 범위를 넘어섭니다.");
	++m_nRefCount;
}
void cObject::Release()
{
	assert(m_nRefCount > 0 && "이미 해제된 메모리입니다.");

	--m_nRefCount;
	if (m_nRefCount == 0)
	{
		delete this;
	}
}
void cObject::AutoRelease()
{
	AUTO_RELEASE_POOL->AddObject(this);
}


cObjectManager::cObjectManager(){}

cObjectManager::~cObjectManager(){}

void cObjectManager::AddObject(cObject* pObject)
{
	m_setObject.insert(pObject);
}
void cObjectManager::RemoveObject(cObject* pObject)
{
	m_setObject.erase(pObject);
}
void cObjectManager::Destroy()
{
	assert(m_setObject.empty() && "생성된 cObject를 상속받은 객체 중 삭제되지 않은 객체가 있습니다.");
}


cAutoReleasePool::cAutoReleasePool(){}

cAutoReleasePool::~cAutoReleasePool(){}

void cAutoReleasePool::AddObject(cObject* pObject)
{
	m_setObjectPool.insert(pObject);
}
void cAutoReleasePool::Drain()
{
	for each(auto p in m_setObjectPool)
	{
		SAFE_RELEASE(p);
	}
	m_setObjectPool.clear();
}