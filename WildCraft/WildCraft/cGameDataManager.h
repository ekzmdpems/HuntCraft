#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ���� ���� �����Ǿ�� �ϴ� ������
// File�� ���� �����͸� �д� ó��
// 
// 
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cGameDataManager
{
private:
	SINGLETONE(cGameDataManager);
public:
	const HRESULT Init();
	void Destroy();
	// ���� ������ �⺻ �δ�
};
#define GAME_DATA cGameDataManager::GetInstance()
