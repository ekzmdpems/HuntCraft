#pragma once
// 새 Scene 은 헤더가 아니라 Init에서 초기화 해서 Scene Manager에 넣을 것

class cMainGame
{
public:
	const HRESULT Init();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	cMainGame();
	~cMainGame();
};

