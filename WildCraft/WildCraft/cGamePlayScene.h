#pragma once
class cGamePlayScene : public iSceneNode
{
private:

public:
	const HRESULT Init(DWORD dwFlag) override;
	void Update() override;
	void Render() override;
	void Release() override;	// 전환되면 없애줘야 할것
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cGamePlayScene();
	virtual ~cGamePlayScene();
};

