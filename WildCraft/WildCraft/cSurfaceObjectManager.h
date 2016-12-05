#pragma once

class iSurfaceObject : public cObject
{
public:
	iSurfaceObject() {};
	virtual ~iSurfaceObject() {};

	virtual void Render() PURE;
	virtual bool GetHeight(float x, float y, float z) PURE;
};

class cSurfaceObjectManager
{
public:
	cSurfaceObjectManager();
	~cSurfaceObjectManager();
};

