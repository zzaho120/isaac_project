#include "framework.h"
#include "CHopper.h"

CHopper::CHopper()
{
}

CHopper::~CHopper()
{
}

HRESULT CHopper::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("idlehopper"));

	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("hopper")->getFrameWidth(), IMAGE->findImage("hopper")->getFrameHeight());
	hp = 8;
	CCharacter::init({ x, y }, rc, IMAGE->findImage("hopper")->getFrameHeight()/2, 8);
	
	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("hopper")->getFrameWidth();
	collidersize.y = collidersize.x/3;
	collider = new CCollider(colliderpt, collidersize);
	IMAGE->addImage("shadowHopper", "images/shadow.bmp", collidersize.x, collidersize.y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::HOPPER);
	AI_init(this, monsterType);

	return S_OK;
}

void CHopper::release()
{
}

void CHopper::update()
{
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void CHopper::render()
{
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	IMAGE->render("shadowHopper", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("hopper")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
