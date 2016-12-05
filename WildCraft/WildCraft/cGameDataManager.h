#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� ���� �����Ǿ�� �ϴ� ������
// File�� ���� �����͸� �д� ó��
// 
// �������� �ϱ� ���� int �����, �Ҽ����̶�� ������ ���ؼ� �־��� ��
// SetSavePath �� ��θ� �������� Add�� �Ϸ��ϰ� AddEnd() �� ���ָ� ���Ͽ� �����Ͱ� �����.
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
	std::string				m_currPath;			// ���� ����

public:
	void SetSavePath(std::string savePath);
	void AddData(std::string szSection, std::string szKey, std::string szVal);
	void AddEnd();
	
	std::string LoadStringData(std::string loadFileName, std::string szSection, std::string szKey);
	int LoadIntergerData(std::string loadFileName, std::string szSection, std::string szKey);
	
	void Destroy();
	// ���� ������ �⺻ �δ�
};
#define GAME_DATA cGameDataManager::GetInstance()

