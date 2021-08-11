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

	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("fly")->getFrameWidth(), IMAGE->findImage("fly")->getFrameHeight());
	float shadowdistance = 50;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);

	setMonster_Type(MONSTER_TYPE::FLY);

	AI_init(this);

	return S_OK;
}

void CFly::release()
{
}

void CFly::update()
{
	AI_update();

}

void CFly::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	IMAGE->findImage("fly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());


}
