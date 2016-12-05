#pragma once
#include <bitset>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Ű �Ŵ���
// �츮 ���ӿ��� ����Ű�� �ʿ���� ��
// 
// 
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class cKeyInputAssister
{
private:
	SINGLETONE(cKeyInputAssister);
private:
	std::bitset<256> _keyUp;
	std::bitset<256> _keyDown;
public:
	const bool isOnceKeyDown(const int key);	//Ű�� �ѹ��� ���ȳ�?
	const bool isOnceKeyUp(const int key);		//Ű�� �ѹ� ������ �����?
	const bool isStayKeyDown(const int key);	//Ű�� ��� ���� �ֳ�?
	const bool isToggleKey(const int key);		//Ű�� ����̳�?
};
#define KEY_ASSISTER cKeyInputAssister::GetInstance()

