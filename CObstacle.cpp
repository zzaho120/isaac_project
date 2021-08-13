#include "framework.h"
#include "CObstacle.h"

CObstacle::CObstacle() :
	CObject(), objType(OBJECT::OBJ_NONE),
	strength(0), attribute(0)
{ }

CObstacle::CObstacle(Vec2 _pos, RECT _rc, OBJECT _type) :
	CObject(_pos, _rc), objType(_type)
{
	Vec2 colliderSize = { TILEWIDTH, TILEHEIGHT /*+ 5*/};
	collider = new CCollider(_pos, colliderSize);
	setObjectValue();
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
}

void CObstacle::render()
{
	IMAGE->frameRender("objectTile", getMemDC(), rc.left, rc.top, frame.x, frame.y);
}

void CObstacle::setObjectValue()
{
	switch (objType)
	{
	case OBJECT::OBJ_GOAL:
		break;
	case OBJECT::OBJ_FIREPLACE:
		frame = { 5, 0 };
		break;
	case OBJECT::OBJ_SPIKE:
		strength = -1;
		frame = { 2, 0 };
		attribute |= ATTR_DAMAGE;
		break;
	case OBJECT::OBJ_POOP:
		strength = 3;
		frame = { 1, 0 };
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_ROCK:
		frame = { 3, 0 };
		attribute |= ATTR_ONLYBOMB;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_STEEL:
		frame = { 4, 0 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_LT_PIT:
		frame = { 0, 1 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_MT_PIT:
		frame = { 1, 1 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_RT_PIT:
		frame = { 2, 1 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_L_PIT:
		frame = { 3, 1 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_M_PIT:
		frame = { 4, 1 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_R_PIT:
		frame = { 5, 1 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_LB_PIT:
		frame = { 0, 2 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_MB_PIT:
		frame = { 1, 2 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_RB_PIT:
		frame = { 2, 2 };
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_WALL:
		strength = -1;
		attribute |= ATTR_UNMOVABLE;
		break;
	case OBJECT::OBJ_DOOR:
		break;
	case OBJECT::OBJ_NONE:
		break;
	default:
		break;
	}
}
