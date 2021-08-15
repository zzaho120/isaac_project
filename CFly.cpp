#include "framework.h"
#include "CFly.h"

CFly::CFly()
{
}

CFly::~CFly()
{
}

HRESULT CFly::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("rightfly"));
	ANIMATION->start("rightfly");

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("fly")->getFrameWidth(), IMAGE->findImage("fly")->getFrameHeight()), //rc
		{ x, y }, { 30,30 }, //collider
		30,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("fly")->getFrameWidth(),IMAGE->findImage("fly")->getFrameWidth() / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowFly", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::FLY);

	AI_init(this, monsterType);

	return S_OK;
}

void CFly::release()
{
}

void CFly::update()
{
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc) });
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	foward = COLLISION->whereAreYouGoing(prevPt, colliderShadow->getPos());
}

void CFly::render()
{
	Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
		collider->getPos().y - collider->getSize().y / 2,
		collider->getPos().x + collider->getSize().x / 2,
		collider->getPos().y + collider->getSize().y / 2);
	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowFly", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("fly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
