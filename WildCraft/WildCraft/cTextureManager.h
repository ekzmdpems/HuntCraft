#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 텍스쳐 매니저
// GetTexture : 2의 배수로 정의된 텍스쳐
// GetSpriteTexture : 모든 텍스쳐, 텍스쳐 정보를 저장함
// 
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cTextureManager
{
private:
	SINGLETONE(cTextureManager);
private:
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, LPDIRECT3DTEXTURE9>	m_mapSpriteTexture;
	std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;
public:
	LPDIRECT3DTEXTURE9 GetTexture(LPSTR szPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string sPath);
	LPDIRECT3DTEXTURE9 GetSpriteTexture(LPSTR szPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetSpriteTexture(std::string sPath, D3DXIMAGE_INFO* pImageInfo);
	void Destroy();
};
#define TEXTURE_MANAGER cTextureManager::GetInstance()