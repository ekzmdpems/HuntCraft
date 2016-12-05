#include "stdafx.h"
#include "cUIManager.h"
#include "cUIObject.h"

cUIManager::cUIManager()
{
}


cUIManager::~cUIManager()
{
}
cUIObject* cUIManager::GetUI(eUIType e)
{
	return nullptr;
}
void cUIManager::Destroy()
{
	for each(auto it in m_mapUIObject)
	{
		SAFE_RELEASE(it.second);
	}
}