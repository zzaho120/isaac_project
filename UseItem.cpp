#include "framework.h"
#include "UseItem.h"

CUseItem::CUseItem()
{
	type = ITEM_TYPE::ITEM_NONE;
}

CUseItem::CUseItem(vector2 _pt)
{
}

CUseItem::~CUseItem()
{
}

HRESULT CUseItem::init()
{
	return E_NOTIMPL;
}

void CUseItem::release()
{
}

void CUseItem::update()
{
}

void CUseItem::render()
{
}

CUseBomb::CUseBomb()
{
}

CUseBomb::CUseBomb(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 20 ,20 }, 5, { _pt.x , _pt.y + 10 }, { 30, 10 });
	usetype = USE_ITEM::BOMB;
}

CUseBomb::~CUseBomb()
{
}

HRESULT CUseBomb::init()
{
	return E_NOTIMPL;
}

void CUseBomb::release()
{
	
}

void CUseBomb::update()
{
	count++;
	if (count == 50)
	{
	}
}

void CUseBomb::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 45, 45);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("bomb", getMemDC(), rec.left, rec.top, 0, 0);
}
