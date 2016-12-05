#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �浹 ����ü.  
// isPick �� Ray���� �浹 �����Ҷ� ���� �ٸ� ��� �� �� �ְ� ��
// isInsect ��  Culling �̳� ȿ�� �����Ҷ� �ش� ��鿡 ���ؼ� �����Ҷ� ��
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ST_BOUNDOBJECT {
	D3DXVECTOR3 vCenter;
	bool		isPicked;
	_ST_BOUNDOBJECT() 
		: vCenter{ 0,0,0 }, isPicked(false) {}
	_ST_BOUNDOBJECT(D3DXVECTOR3 _vCenter, bool _isPicked) 
		: vCenter(_vCenter), isPicked(_isPicked) {}
	virtual const bool IsPick(const D3DXVECTOR3& rayPos,const D3DXVECTOR3& rayDir) { return false; };
	virtual const bool IsInsect(const D3DXPLANE& plane) const { return false; };
} ST_BOUNDOBJECT;


typedef struct _ST_SPHERE : public _ST_BOUNDOBJECT
{
	float fRadius;
	_ST_SPHERE() 
		: _ST_BOUNDOBJECT::_ST_BOUNDOBJECT()
		, fRadius(0) {}
	_ST_SPHERE(D3DXVECTOR3 _vCenter, float _fRadius, bool _isPicked)
		: _ST_BOUNDOBJECT::_ST_BOUNDOBJECT(_vCenter, _isPicked)
		, fRadius(_fRadius) {}

	const bool IsPick(const D3DXVECTOR3& rayPos,const D3DXVECTOR3& rayDir) override
	{
		auto vLocalRayPos = rayPos - vCenter;
		auto qv = D3DXVec3Dot(&vLocalRayPos, &rayDir);
		auto qq = D3DXVec3Dot(&vLocalRayPos, &vLocalRayPos);
		auto vv = D3DXVec3Dot(&rayDir, &rayDir);
		auto rr = fRadius*fRadius;
		return (qv*qv - vv*(qq - rr)) > 0.0f;
	}
	const bool IsInsect(const D3DXPLANE& plane) const override 
	{
		if (D3DXPlaneDotCoord(&plane, &vCenter) + fRadius < 0)
		{
			return false;
		}
		return true;
	}
} ST_SPHERE;