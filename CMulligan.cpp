#include "framework.h"
#include "CMulligan.h"

CMulligan::CMulligan()
{
}

CMulligan::~CMulligan()
{
}

HRESULT CMulligan::init(float x, float y)
{
	anihead = ANIMATION->findAnimation("lefthead");
	setAni(ANIMATION->findAnimation("mulliganidle"));

	//setAnibody(ANIMATION->findAnimation("mulliganidle"));

	ANIMATION->start("lefthead");
	ANIMATION->start("mulliganidle");

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("mulliganhead")->getFrameWidth(), IMAGE->findImage("mulliganhead")->getFrameHeight()), //rc
		{ x, y }, { 70,70 }, //collider
		35,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("mulliganhead")->getFrameWidth(),IMAGE->findImage("mulliganhead")->getFrameWidth() / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowMulligan", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::MULLIGAN);
	AI_init(this, monsterType);

	return S_OK;
}

void CMulligan::release()
{
}

void CMulligan::update()
{
	AI_update();
	if (ani == ANIMATION->findAnimation("leftbody"))
	{
		anihead = ANIMATION->findAnimation("lefthead");
	}
	else anihead = ANIMATION->findAnimation("righthead");

	collider->setPos({ RectX(rc), RectY(rc)});
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	foward = COLLISION->whereAreYouGoing(prevPt, colliderShadow->getPos());
}

void CMulligan::render()
{
	Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
		collider->getPos().y - collider->getSize().y / 2,
		collider->getPos().x + collider->getSize().x / 2,
		collider->getPos().y + collider->getSize().y / 2);

	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowMulligan", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("mulliganbody")->aniRender(getMemDC(), RectX(getRC()) - IMAGE->findImage("mulliganbody")->getFrameWidth() / 2, RectY(getRC()), getAni());
	IMAGE->findImage("mulliganhead")->aniRender(getMemDC(), getRC().left, getRC().top, anihead);
}
