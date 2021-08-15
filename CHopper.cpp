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

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("hopper")->getFrameWidth(), IMAGE->findImage("hopper")->getFrameHeight()), //rc
		{ x, y }, { 30,30 }, //collider
		30,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("hopper")->getFrameWidth(),IMAGE->findImage("hopper")->getFrameWidth() / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowHopper", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

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
	collider->setPos({ RectX(rc), RectY(rc) });
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	foward = COLLISION->whereAreYouGoing(prevPt, colliderShadow->getPos());
}

void CHopper::render()
{
	Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
		collider->getPos().y - collider->getSize().y / 2,
		collider->getPos().x + collider->getSize().x / 2,
		collider->getPos().y + collider->getSize().y / 2);

	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowHopper", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("hopper")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
