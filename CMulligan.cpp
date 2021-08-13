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


	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("mulliganhead")->getFrameWidth(), IMAGE->findImage("mulliganhead")->getFrameHeight());
	int hp = 8;

	CCharacter::init({ x,y }, rc,  IMAGE->findImage("mulliganhead")->getFrameHeight()/2, hp);

	vector2 colliderpt = { x, y + shadowdistance };
	vector2 collidersize;
	collidersize.x = IMAGE->findImage("mulliganhead")->getFrameWidth();
	collidersize.y = collidersize.x / 3;
	collider = new CCollider(colliderpt, collidersize);
	IMAGE->addImage("shadowMulligan", "images/shadow.bmp", collidersize.x, collidersize.y, true, RGB(255, 0, 255));

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
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void CMulligan::render()
{
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	IMAGE->render("shadowMulligan", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("mulliganbody")->aniRender(getMemDC(), RectX(getRC()) - IMAGE->findImage("mulliganbody")->getFrameWidth() / 2, RectY(getRC()), getAni());
	IMAGE->findImage("mulliganhead")->aniRender(getMemDC(), getRC().left, getRC().top, anihead);
}
