#include "framework.h"
#include "CHost.h"
#include"BulletManager.h"
CHost::CHost()
{
}

CHost::~CHost()
{
}

HRESULT CHost::init(float x, float y)
{

	setAni(ANIMATION->findAnimation("hostidle"));
	ANIMATION->start("hostidle");

	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("host")->getFrameWidth(), IMAGE->findImage("host")->getFrameHeight());
	float shadowdistance = 20;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);
	
	setMonster_Type(MONSTER_TYPE::HOST);
	AI_init(this);

	return S_OK;
}

void CHost::release()
{
}

void CHost::update()
{
	AI_update();
}

void CHost::render()
{
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	IMAGE->findImage("host")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());

}

