#include "framework.h"
#include "CWORM.h"
#include "CStage.h"
CWORM::CWORM()
{
}

CWORM::~CWORM()
{
}

HRESULT CWORM::init(float x, float y)
{
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("worm")->getFrameWidth(), IMAGE->findImage("worm")->getFrameHeight());
	hp = 8;

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("worm")->getFrameWidth(), IMAGE->findImage("worm")->getFrameHeight()), //rc
		{ x, y }, { 30,30 }, //collider
		10,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("worm")->getFrameWidth(),IMAGE->findImage("worm")->getFrameWidth() / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowWorm", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));


	setAni(ANIMATION->findAnimation("rightworm"));

	setMonster_Type(MONSTER_TYPE::WORM);
	AI_init(this,monsterType);

	return S_OK;
}
void CWORM::release() {}

void CWORM::update()
{
	AI_update();
	vector2 rcPt;
	rcPt.x = RectX(rc);
	rcPt.y = RectY(rc) + shadowdistance;
	foward = COLLISION->whereAreYouGoing(prevPt, rcPt);
	rcPt = COLLISION->tileCollision(STAGE->getCurStage()->getMap(), rcPt, prevPt, foward , 1);

	collider->setPos({ rcPt.x, rcPt.y - shadowdistance });
	colliderShadow->setPos(rcPt);
	rc = RectMakeCenter(collider->getPos(), IMAGE->findImage("mulliganhead")->getFrameWidth(), IMAGE->findImage("mulliganhead")->getFrameHeight());
}

void CWORM::render()
{
	Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
		collider->getPos().y - collider->getSize().y / 2,
		collider->getPos().x + collider->getSize().x / 2,
		collider->getPos().y + collider->getSize().y / 2);

	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowWorm", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("worm")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
