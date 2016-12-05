#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 쉐이더 메니저
// 다른 것처럼 미리 세팅해 두고 꺼내씀
// 지금 현재 되는 것 ST_XFILE
// 
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum class eShaderType
{
	ST_NORMAL,			// 일반용
	ST_WATER,			// 물
	ST_XFILE			// Xfile용
};

class cShaderManager
{
private:
	SINGLETONE(cShaderManager);
private:
	std::map<eShaderType, LPD3DXEFFECT> m_mapEffect;
public:
	LPD3DXEFFECT GetShader(eShaderType e);
	void Destroy();

private:
	LPD3DXEFFECT LoadShader(std::string sPath);
	LPD3DXEFFECT LoadShaderXFILE(std::string sPath);
	// 세팅값이 달라질 수 있음
};
#define SHADER_MANAGER cShaderManager::GetInstance()
