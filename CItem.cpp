#include "framework.h"
#include "CItem.h"
CItem::CItem()
{
}

CItem::~CItem()
{
}

HRESULT CItem::init()
{
	return E_NOTIMPL;
}

void CItem::release()
{
}

void CItem::update()
{
}

void CItem::render()
{
}
CHeart::CHeart()
{
}

CHeart::CHeart(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 20 ,20 }, 5, { _pt.x , _pt.y - shadowdistance }, { 30, 10 });
	type = ITEM_TYPE::ITEM_HEART;
}

CHeart::~CHeart()
{
}

HRESULT CHeart::init()
{
	return E_NOTIMPL;
}

void CHeart::release()
{
}

void CHeart::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}

CBomb::CBomb()
{
}

CBomb::~CBomb()
{
}

HRESULT CBomb::init()
{
	return E_NOTIMPL;
}

void CBomb::release()
{
}

void CBomb::render()
{
}
