#pragma once
class cRay
{
private:
	D3DXVECTOR3 m_vRayPos;
	D3DXVECTOR3 m_vRayDir;
public:
	static cRay RayAtViewSpace(int x, int y);
	static cRay RayAtWorldSpace(int x, int y);
	const bool IsPicked(ST_BOUNDOBJECT& s) const;

	cRay();
	~cRay();
};

