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

	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("fly")->getFrameWidth(), IMAGE->findImage("fly")->getFrameHeight());
	hp = 8;

	CCharacter::init({ x, y }, rc, 40, hp);

	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("fly")->getFrameWidth();
	collidersize.y = collidersize.x / 3;
	collider = new CCollider(colliderpt, collidersize);
	IMAGE->addImage("shadowFly", "images/shadow.bmp", collidersize.x, collidersize.y, true, RGB(255, 0, 255));

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
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void CFly::render()
{
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	IMAGE->render("shadowFly", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("fly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
