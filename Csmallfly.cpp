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

	setMonster_Type(MONSTER_TYPE::SMALLFLY);

	AI_init(this);
	return S_OK;
}

void Csmallfly::release()
{
}

void Csmallfly::update()
{
	AI_update();
}

void Csmallfly::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	IMAGE->findImage("smallfly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
