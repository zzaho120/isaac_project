#include "framework.h"
#include "Csmallfly.h"

Csmallfly::Csmallfly()
{
}

Csmallfly::~Csmallfly()
{
}

HRESULT Csmallfly::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("smallflyani"));
	ANIMATION->start("smallflyani");

	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("smallfly")->getFrameWidth(), IMAGE->findImage("smallfly")->getFrameHeight());
	hp = 8;

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("smallfly")->getFrameWidth(), IMAGE->findImage("smallfly")->getFrameHeight()), //rc
		{x, y }, { 18,18 }, //collider
		36,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("smallfly")->getFrameWidth(),IMAGE->findImage("smallfly")->getFrameWidth() / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowSmallfly", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::SMALLFLY);
	AI_init(this, monsterType);
	return S_OK;
}

void Csmallfly::release()
{
}

void Csmallfly::update()
{
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc)});
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void Csmallfly::render()
{
	Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
		collider->getPos().y - collider->getSize().y / 2,
		collider->getPos().x + collider->getSize().x / 2,
		collider->getPos().y + collider->getSize().y / 2);

	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowSmallfly", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("smallfly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
