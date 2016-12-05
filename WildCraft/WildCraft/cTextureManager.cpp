#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}

cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(LPSTR szPath)
{
	return GetTexture(std::string(szPath));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string sPath)
{
	if (m_mapTexture.find(sPath) == m_mapTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture;
		D3DXCreateTextureFromFileA(DEVICE, sPath.c_str(), &pTexture);
		m_mapTexture[sPath] = pTexture;
	}
	return m_mapTexture[sPath];
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	for each(auto it in m_mapSpriteTexture)
	{
		SAFE_RELEASE(it.second);
	}
}
LPDIRECT3DTEXTURE9 cTextureManager::GetSpriteTexture(LPSTR szPath, D3DXIMAGE_INFO* pImageInfo)
{
	return GetSpriteTexture(std::string(szPath), pImageInfo);
}
LPDIRECT3DTEXTURE9 cTextureManager::GetSpriteTexture(std::string sPath, D3DXIMAGE_INFO* pImageInfo)
{
	if (m_mapSpriteTexture.find(sPath) == m_mapSpriteTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		D3DXCreateTextureFromFileExA(
			DEVICE,
			sPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[sPath],
			NULL,
			&pTexture);

		m_mapSpriteTexture[sPath] = pTexture;
	}

	if (pImageInfo)
	{
		*pImageInfo = m_mapImageInfo[sPath];
	}

	return m_mapSpriteTexture[sPath];
}