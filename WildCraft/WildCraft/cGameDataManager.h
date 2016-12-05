#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 게임 내내 유지되어야 하는 정보들
// File로 부터 데이터를 읽는 처리
// 
// 음수값도 하기 위해 int 사용함, 소수점이라면 적절히 곱해서 넣어줄 것
// SetSavePath 로 경로를 설정한후 Add를 완료하고 AddEnd() 를 해주면 파일에 데이터가 저장됨.
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ST_DATA
{
	std::string _Section;
	std::string _Key;
	std::string _Value;
};

class cGameDataManager
{
private:
	SINGLETONE(cGameDataManager);
private:
	std::vector<ST_DATA>	m_vecData;
	std::string				m_currPath;			// 현재 저장

public:
	void SetSavePath(std::string savePath);
	void AddData(std::string szSection, std::string szKey, std::string szVal);
	void AddEnd();
	
	std::string LoadStringData(std::string loadFileName, std::string szSection, std::string szKey);
	int LoadIntergerData(std::string loadFileName, std::string szSection, std::string szKey);
	
	void Destroy();
	// 각종 데이터 기본 로더
};
#define GAME_DATA cGameDataManager::GetInstance()

