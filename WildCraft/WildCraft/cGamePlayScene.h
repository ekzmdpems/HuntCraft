#pragma once
class cGamePlayScene : public iSceneNode
{
private:

public:
	const HRESULT Init(DWORD dwFlag) override;
	void Update() override;
	void Render() override;
	void Release() override;	// ��ȯ�Ǹ� ������� �Ұ�
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cGamePlayScene();
	virtual ~cGamePlayScene();
};
