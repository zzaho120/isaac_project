#include "framework.h"
#include "CObstacle.h"

CObstacle::CObstacle() :
	CObject(), objType(OBJECT::OBJ_NONE),
	strength(0), isUnmovable(false), isDestroyByBomb(false),
	isDestroyByBullet(false)
{ }

CObstacle::CObstacle(Vec2 _pos, RECT _rc, OBJECT _type) :
	CObject(_pos, _rc), objType(_type), 
	strength(4), isUnmovable(false), isDestroyByBomb(false),
	isDestroyByBullet(false)
{
	Vec2 colliderSize = { TILEWIDTH, TILEHEIGHT /*+ 5*/};
	collider = new CCollider(_pos, colliderSize);
	setObjectValue();
}

CObstacle::CObstacle(CObstacle* copy)
{
	objType = copy->getObjType();
	strength = copy->getStrength();
	frame = copy->getFrame();

	isUnmovable = copy->getUnmovalbe();
	isDestroyByBomb = copy->getDestroyBomb();
	isDestroyByBullet = copy->getDestroyBullet();

	pt = copy->getPt();
	rc = copy->getRC();
	collider = copy->getcollider();
	colliderShadow = copy->GetcolliderShadow();
}

CObstacle::~CObstacle()
{
}

HRESULT CObstacle::init()
{
	return S_OK;
}

void CObstacle::release()
{
}

void CObstacle::update()
{
	setObjectValue();
}

void CObstacle::render()
{
	if (objType == OBJECT::OBJ_NONE) return;
	if (objType == OBJECT::OBJ_TOPDOOR || objType == OBJECT::OBJ_CLOSETOPDOOR)
		IMAGE->frameRender("normalDoor", getMemDC(), rc.left - 52, rc.top - 50, frame.x, frame.y);
	else if (objType == OBJECT::OBJ_BOTTOMDOOR || objType == OBJECT::OBJ_CLOSEBOTTOMDOOR)
		IMAGE->frameRender("normalDoor", getMemDC(), rc.left - 52, rc.top - 25, frame.x, frame.y);
	else if (objType == OBJECT::OBJ_LEFTDOOR || objType == OBJECT::OBJ_CLOSELEFTDOOR)
		IMAGE->frameRender("normalDoor", getMemDC(), rc.left - 70, rc.top - 40, frame.x, frame.y);
	else if (objType == OBJECT::OBJ_RIGHTDOOR || objType == OBJECT::OBJ_CLOSERIGHTDOOR)
		IMAGE->frameRender("normalDoor", getMemDC(), rc.left - 27, rc.top - 40, frame.x, frame.y);
	else if (objType == OBJECT::OBJ_POOP)
		IMAGE->frameRender("poop", getMemDC(), rc.left, rc.top, 4 - strength, 0);
	else IMAGE->frameRender("objectTile", getMemDC(), rc.left, rc.top, frame.x, frame.y);
}

void CObstacle::setObjectValue()
{
	switch (objType)
	{
	case OBJECT::OBJ_GOAL:
		setValue(false, false, false, true);
		break;
	case OBJECT::OBJ_FIREPLACE:
		frame = { 5, 0 };
		setValue(false, false, true, true);
		break;
	case OBJECT::OBJ_SPIKE:
		frame = { 2, 0 };
		setValue(false, false, true, true);
		break;
	case OBJECT::OBJ_POOP:
		frame = { 1, 0 };
		setValue(true, true, true, false);
		break;
	case OBJECT::OBJ_ROCK:
		frame = { 3, 0 };
		setValue(true, true, false, false);
		break;
	case OBJECT::OBJ_STEEL:
		frame = { 4, 0 };
		setValue(true, false, false, false);
		break;
	case OBJECT::OBJ_LT_PIT:
		frame = { 0, 1 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_MT_PIT:
		frame = { 1, 1 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_RT_PIT:
		frame = { 2, 1 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_L_PIT:
		frame = { 3, 1 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_M_PIT:
		frame = { 4, 1 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_R_PIT:
		frame = { 5, 1 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_LB_PIT:
		frame = { 0, 2 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_MB_PIT:
		frame = { 1, 2 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_RB_PIT:
		frame = { 2, 2 };
		setValue(true, false, false, true);
		break;
	case OBJECT::OBJ_WALL:
		strength = -1;
		setValue(true, false, false, false);
		break;
	case OBJECT::OBJ_TOPDOOR:
		frame = { 0, 0 };
		setValue(false, false, false, false);
		break;
	case OBJECT::OBJ_LEFTDOOR:
		frame = { 2, 0 };
		setValue(false, false, false, false);
		break;
	case OBJECT::OBJ_RIGHTDOOR:
		frame = { 3, 0 };
		setValue(false, false, false, false);
		break;
	case OBJECT::OBJ_BOTTOMDOOR:
		frame = { 1, 0 };
		setValue(false, false, false, false);
		break;
	case OBJECT::OBJ_CLOSETOPDOOR:
		frame = { 0, 1 };
		setValue(true, false, false, false);
		break;
	case OBJECT::OBJ_CLOSELEFTDOOR:
		frame = { 2, 1 };
		setValue(true, false, false, false);
		break;
	case OBJECT::OBJ_CLOSERIGHTDOOR:
		frame = { 3, 1 };
		setValue(true, false, false, false);
		break;
	case OBJECT::OBJ_CLOSEBOTTOMDOOR:
		frame = { 1, 1 };
		setValue(true, false, false, false);
		break;
	case OBJECT::OBJ_NONE:
		frame = { 0,0 };
		setValue(false, false, false, true);
		break;
	default:
		break;
	}
}

void CObstacle::setValue(bool move, bool bomb, bool bullet, bool pass)
{
	isUnmovable = move;
	isDestroyByBomb = bomb;
	isDestroyByBullet = bullet;
	isPassBullet = pass;
}
