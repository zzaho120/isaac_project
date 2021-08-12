#include "framework.h"
#include "CObject.h"

CObject::CObject() : 
	pt({ 0, 0 }), rc(RectMakeCenter(0,0,0,0)),
	ani(nullptr) , shadowdistance(0)
{
}

CObject::CObject(Vec2 _pos, RECT _rc) :
	pt(_pos), rc(_rc),
	ani(nullptr), shadowdistance(0)
{
}

CObject::~CObject()
{
	//SAFE_DELETE(ani);
}

HRESULT CObject::init()
{
	pt = 0;
	rc = RectMake(0, 0, 0, 0);
	return S_OK;
}

HRESULT CObject::init(vector2 _pt, RECT _rc, float _shadowdistance)
{
	pt = _pt;
	rc = _rc;
	shadowdistance = _shadowdistance;
	return S_OK;
}

void CObject::release()
{
}

void CObject::update()
{
}

void CObject::render()
{
}
