#include "stdafx.h"
#include "cTitleScene.h"


cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

const HRESULT cTitleScene::Init(DWORD dwFlag)
{
	GAME_DATA->SetSavePath("./Setting.ini");
	GAME_DATA->AddData("Section1", "Korl", "315");
	GAME_DATA->AddData("Section1", "Korl1", "315");
	GAME_DATA->AddData("Section1", "Korl2", "315");
	GAME_DATA->AddData("Section1", "Korl3", "315");

	GAME_DATA->AddData("Section2", "Korl1", "315");
	GAME_DATA->AddData("Section2", "Korl2", "315");
	GAME_DATA->AddEnd();

	return S_OK;
}
void cTitleScene::Update()
{

}
void cTitleScene::Render()
{

}
void cTitleScene::Release()
{

}
void cTitleScene::WndProc(HWND, UINT, WPARAM, LPARAM)
{

}