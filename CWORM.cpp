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
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("worm")->getFrameWidth(), IMAGE->findImage("worm")->getFrameHeight());
	hp = 8;

	CCharacter::init({ x,y }, rc, 10, hp);

	setAni(ANIMATION->findAnimation("rightworm"));

	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("worm")->getFrameWidth();
	collidersize.y = collidersize.x / 3;
	collider = new CCollider(colliderpt, collidersize);
	IMAGE->addImage("shadowWorm", "images/shadow.bmp", collidersize.x, collidersize.y, true, RGB(255, 0, 255));

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
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	IMAGE->render("shadowWorm", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("worm")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
