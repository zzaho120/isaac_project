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

	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("smallfly")->getFrameWidth(), IMAGE->findImage("smallfly")->getFrameHeight());
	float shadowdistance = 50;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);

	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("smallfly")->getFrameWidth();
	collidersize.y = IMAGE->findImage("smallfly")->getFrameHeight();
	collider = new CCollider(colliderpt, collidersize);

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
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void Csmallfly::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	IMAGE->findImage("smallfly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
