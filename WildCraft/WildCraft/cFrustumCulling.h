#pragma once
class cFrustumCulling
{
private:
	SINGLETONE(cFrustumCulling);
private:
	D3DXPLANE	m_Plane[6];
public:
	void Update();
	const bool Intersect(const ST_BOUNDOBJECT* s) const;
};
#define FRUSTUM_CULLING cFrustumCulling::GetInstance()

