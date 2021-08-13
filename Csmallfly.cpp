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

	CCharacter::init({ x,y }, rc, 30, hp);

	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("smallfly")->getFrameWidth();
	collidersize.y = collidersize.x / 3;
	collider = new CCollider(colliderpt, collidersize);
	IMAGE->addImage("shadowSmallfly", "images/shadow.bmp", collidersize.x, collidersize.y, true, RGB(255, 0, 255));

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
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	IMAGE->render("shadowSmallfly", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("smallfly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
