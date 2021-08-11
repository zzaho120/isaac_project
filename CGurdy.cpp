#include "framework.h"
#include "CGurdy.h"

CGurdy::CGurdy()
{

}

CGurdy::~CGurdy()
{
}

HRESULT CGurdy::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("gurdyfaceidle"));
	ANIMATION->start("gurdyfaceidle");
	anibody = ANIMATION->findAnimation("gurdybodyidle");
	ANIMATION->start("gurdybodyidle");
	body = RectMakeCenter(x, y, IMAGE->findImage("gurdybody")->getFrameWidth(), IMAGE->findImage("gurdybody")->getFrameHeight());

	vector2 pt = { x, y };
	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("gurdyface")->getFrameWidth(), IMAGE->findImage("gurdyface")->getFrameHeight());
	float shadowdistance = 50;
	int hp = 8;

	CCharacter::init(pt, rc, shadowdistance, hp);

	setMonster_Type(MONSTER_TYPE::GURDY);

	AI_init(this);

	return S_OK;
}

void CGurdy::release()
{
}

void CGurdy::update()
{
	AI_update();
}

void CGurdy::render()
{
	/*Rectangle(getMemDC(), getRC().left, getRC().top + shadowdistance, getRC().right, getRC().bottom + shadowdistance);
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);*/
	Rectangle(getMemDC(), body.left, body.top +shadowdistance, body.right, body.bottom + shadowdistance);
	Rectangle(getMemDC(), body.left, body.top, body.right, body.bottom);

	IMAGE->findImage("gurdybody")->aniRender(getMemDC(), body.left, body.top, anibody);
	IMAGE->findImage("gurdyface")->aniRender(getMemDC(), getRC().left, getRC().top - 30, getAni());
}
