#pragma once
#include "stdafx.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// UI를 손쉽게 호출하기 위한 클래스
// 선생님 소스 기본으로 해두었으니 필요하면 수정하고 설명 달아줄 것
// 
// 
// 
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class cUIObject;
enum Element
{
	MAIN,
	EX,
	BUTTON
};

class cUIManager
{
private:
	SINGLETONE(cUIManager);
public:
	enum class eUIType
	{
		UT_State
	};
private:
	std::map<eUIType, cUIObject*> m_mapUIObject;
	LPD3DXSPRITE				m_pSprite;
	LPD3DXSPRITE				m_pSprite2;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXIMAGE_INFO				m_stImageInfo;
	LPDIRECT3DTEXTURE9			m_pTexture2;
	D3DXIMAGE_INFO				m_stImageInfo2;
	bool		m_isLButtonDown;	//마우스클릭 여부
	POINT		m_ptPrevMouse;		//마우스클릭시 좌표저장
	bool		isClicked;
	RECT UI;
	cUIManager* m_Parent;
	Element e_type;
	SYNTHESIZE(bool, isActive, Actived);
	SYNTHESIZE(float, m_MoveX, MoveX);
	SYNTHESIZE(int, m_MoveY, MoveY);
	SYNTHESIZE(bool, isMove, DragAble);
	SYNTHESIZE(bool, isAble, ClickAble);
	SYNTHESIZE(int, isSelected, Selected);
	float pos_x, pos_y;
	std::vector<cUIManager*> v_mChild;
public:
	//부모노드, 속성, 일반ui, 마우스 오버된 ui, 위치
	void Init(cUIManager* root, Element element, const char* name, const char* name2, POINT pos);
	void Update();
	void render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void setChild(cUIManager *_child);
	cUIObject* GetUI(eUIType e);
	
	void Destroy();
};
#define UI_MANAGER cUIManager::GetInstance()

