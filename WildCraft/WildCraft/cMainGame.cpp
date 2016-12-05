#include "stdafx.h"
#include "cMainGame.h"

#include "cMapCreateScene.h"
#include "cTitleScene.h"
#include "cGamePlayScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	OBJECT_MANAGER->Destroy();
	TEXTURE_MANAGER->Destroy();
	SHADER_MANAGER->Destroy();
	SCENE_MANAGER->Destroy();
	DEVICE_MANAGER->Destroy();
}


const HRESULT cMainGame::Init()
{
#pragma region 기본 세팅, 손댈 것 없음
	DEVICE_MANAGER->Init();
	TIME_MANAGER->Init(false);
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);

	D3DVIEWPORT9 matViewport = { 0, 0, rc.right, rc.bottom, 0.0f, 1.0f };
	DEVICE->SetViewport(&matViewport);
#pragma endregion

	// SCENE 초기화 해서 넣는 곳
	LPSCENENODE scene = new cMapCreateScene;
	SCENE_MANAGER->AddScene("MapCreateScene", scene);
	scene = new cGamePlayScene;
	SCENE_MANAGER->AddScene("PlayScene", scene);
	scene = new cTitleScene;
	SCENE_MANAGER->AddScene("TitleScene", scene);
	SCENE_MANAGER->ChangeScene("TitleScene");

	return S_OK;
}
void cMainGame::Update()
{
	TIME_MANAGER->Update();
	SCENE_MANAGER->Update();
}
void cMainGame::Render()
{
	DEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	DEVICE->BeginScene();
	SCENE_MANAGER->Render();
	DEVICE->EndScene();
	DEVICE->Present(NULL, NULL, NULL, NULL);

}
void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SCENE_MANAGER->WndProc(hWnd, message, wParam, lParam);
}