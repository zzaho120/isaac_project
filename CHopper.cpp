#include "framework.h"
#include "CHopper.h"

CHopper::CHopper()
{
}

CHopper::~CHopper()
{
}

HRESULT CHopper::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("idlehopper"));

	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("hopper")->getFrameWidth(), IMAGE->findImage("hopper")->getFrameHeight());
	shadowdistance = 20;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);
	
	setMonster_Type(MONSTER_TYPE::HOPPER);
	AI_init(this);

	return S_OK;
}

void CHopper::release()
{
}

void CHopper::update()
{
	AI_update();
}

void CHopper::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top+ shadowdistance, getRC().right, getRC().bottom+ shadowdistance);
	//Rectangle(getMemDC(), getshadowRC().left, getshadowRC().top, getshadowRC().right, getshadowRC().bottom);
	IMAGE->findImage("hopper")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
