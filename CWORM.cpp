#include "framework.h"
#include "CWORM.h"

CWORM::CWORM()
{
}

CWORM::~CWORM()
{
}

HRESULT CWORM::init(float x, float y)
{


	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("worm")->getFrameWidth(), IMAGE->findImage("worm")->getFrameHeight());
	float shadowdistance = 20;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);

	setAni(ANIMATION->findAnimation("rightworm"));

	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("worm")->getFrameWidth();
	collidersize.y = IMAGE->findImage("worm")->getFrameHeight();
	collider = new CCollider(colliderpt, collidersize);

	setMonster_Type(MONSTER_TYPE::WORM);
	AI_init(this,monsterType);

	return S_OK;
}
void CWORM::release() {}

void CWORM::update()
{
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void CWORM::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	IMAGE->findImage("worm")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
