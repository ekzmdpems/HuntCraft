#pragma once

enum class eCameraType
{
	RAND,
	AIR
};

class cCamera
{
private:
	
	D3DXVECTOR3				m_vUp;			// 정규화된 벡터
	D3DXVECTOR3				m_vRight;
	D3DXVECTOR3				m_vLook;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vPos, Position);
	SYNTHESIZE_S(eCameraType, m_eType, CameraType);
private:
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;

	float					m_fAngleX, m_fAngleY;		// 아예 초기화 할때 필요한 변수
	float					m_fDistance;
	SYNTHESIZE(D3DXVECTOR3*, m_pTarget, TargetVector);	// 가리킬 대상
public:
	cCamera(void);
	~cCamera(void);

	void Init(eCameraType eType);
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void tStrafe(float fUnit);		// 수평 이동
	void tFly(float fUnit);			// 고도 이동
	void tWalk(float fUnit);		// 회전 이동

	void rPitch(float fAngle);		// 우향 회전
	void rYaw(float fAngle);		// 상향 회전
	void rRoll(float fAngle);		// 전방 회전

	void AngleSet();				// 전역 변수로 세팅함
	void UpdateKey();
};
