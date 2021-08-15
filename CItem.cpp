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
	CObject::init(_pt, rc, _pt, { 20 ,20 }, 5, { _pt.x , _pt.y + 5 }, { 30, 10 });
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
	RECT rec = RectMakeCenter(getcollider()->getPos(), 30, 30);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);
	
	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->frameRender("heartitem", getMemDC(), rec.left, rec.top,0,0);
}
CCoin::CCoin()
{
}

CCoin::CCoin(vector2 _pt)
{
	rc = RectMakeCenter(_pt, 30, 30);
	CObject::init(_pt, rc, _pt, { 20 ,20 }, 5, { _pt.x , _pt.y + 5 }, { 30, 10 });
	type = ITEM_TYPE::ITEM_COIN;
	ani = ANIMATION->findAnimation("coinani");
	ANIMATION->start("coinani");
}

CCoin::~CCoin()
{
}

HRESULT CCoin::init()
{
	return E_NOTIMPL;
}

void CCoin::release()
{
}

void CCoin::render()
{
	RECT rec = RectMakeCenter(getcollider()->getPos(), 30, 30);
	RECT recshadow = RectMakeCenter(GetcolliderShadow()->getPos(), 30, 10);

	IMAGE->render("itemshadow", getMemDC(), recshadow.left, recshadow.top);
	IMAGE->findImage("coin")->aniRender(getMemDC(), rec.left, rec.top, ani);
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

