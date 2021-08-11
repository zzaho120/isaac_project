#include "framework.h"
#include "CCharacter.h"

CCharacter::CCharacter() :
	CObject(), hp(0)
{
}

CCharacter::CCharacter(Vec2 _pos, RECT _rc, int _hp) :
	CObject(_pos, _rc), hp(_hp)
{
}

CCharacter::~CCharacter()
{
}

HRESULT CCharacter::init()
{
	CObject::init();
	hp = 0;
	return S_OK;
}

HRESULT CCharacter::init(vector2 _pt, RECT _rc, float _shadowdistance, int _hp)
{
	CObject::init(_pt, _rc, _shadowdistance);
	hp = _hp;
	return S_OK;
}
