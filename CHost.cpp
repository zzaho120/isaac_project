#include "framework.h"
#include "CHost.h"
#include"BulletManager.h"
CHost::CHost()
{
}

CHost::~CHost()
{
}

HRESULT CHost::init(float x, float y)
{

	setAni(ANIMATION->findAnimation("hostidle"));
	ANIMATION->start("hostidle");

	rc = RectMakeCenter(x, y, IMAGE->findImage("host")->getFrameWidth(), IMAGE->findImage("host")->getFrameHeight());
	hp = 8;

	CCharacter::init({ x, y }, rc, IMAGE->findImage("host")->getFrameHeight()/2 -3, hp);
	
	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("host")->getFrameWidth();
	collidersize.y = collidersize.x / 3;
	collider = new CCollider(colliderpt, collidersize);
	IMAGE->addImage("shadowHost", "images/shadow.bmp", collidersize.x, collidersize.y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::HOST);
	AI_init(this, monsterType);

	return S_OK;
}

void CHost::release()
{
}

void CHost::update()
{
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void CHost::render()
{
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	IMAGE->render("shadowHost", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("host")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());

}

