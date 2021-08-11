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


	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("mulliganhead")->getFrameWidth(), IMAGE->findImage("mulliganhead")->getFrameHeight());
	float shadowdistance = 20;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);

	setMonster_Type(MONSTER_TYPE::MULLIGAN);
	AI_init(this);

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
}

void CMulligan::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	IMAGE->findImage("mulliganbody")->aniRender(getMemDC(), RectX(getRC()) - IMAGE->findImage("mulliganbody")->getFrameWidth() / 2, RectY(getRC()), getAni());
	IMAGE->findImage("mulliganhead")->aniRender(getMemDC(), getRC().left, getRC().top, anihead);
}
