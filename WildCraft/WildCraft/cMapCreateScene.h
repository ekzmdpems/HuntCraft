#pragma once
class cMapCreateScene : public iSceneNode
{
private:

public:
	const HRESULT Init(DWORD dwFlag) override;
	void Update() override;
	void Render() override;
	void Release() override;	// ��ȯ�Ǹ� ������� �Ұ�
	void WndProc(HWND, UINT, WPARAM, LPARAM) override;

	cMapCreateScene();
	virtual ~cMapCreateScene();
};
