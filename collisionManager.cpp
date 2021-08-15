#include "framework.h"
#include "collisionManager.h"
#include "CCollider.h"
#include "CMap.h"
#include "CStage.h"
#include "CPlayer.h"
#include "CObstacle.h"
collisionManager::collisionManager()
{
}

collisionManager::~collisionManager()
{
}

//HRESULT collisionManager::init()
//{
//	return S_OK;
//}
//
//void collisionManager::release()
//{
//}
//
//void collisionManager::update()
//{
//}
//
//void collisionManager::render()
//{
//}

bool collisionManager::isCollision(CCollider* _left, CCollider* _right)
{
	float fDist = abs(_left->getPos().x - _right->getPos().x);
	float fSize = _left->getSize().x / 2.f + _right->getSize().x / 2.f;

	if (fDist < fSize)
	{
		// x 축으로 겹친다.
		fDist = abs(_left->getPos().y - _right->getPos().y);
		fSize = _left->getSize().y / 2.f + _right->getSize().y / 2.f;

		if (fDist < fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}

	return false;
}


bool collisionManager::isCollision(RECT _left, RECT _right)
{
	int leftSize = _left.right - _left.left;
	int rightSize = _right.right - _right.left;

	int leftPt = _left.left + leftSize / 2;
	int rightPt = _right.left + rightSize / 2;

	float fDist = abs(leftPt - rightPt);
	float fSize = leftSize / 2.f + rightSize / 2.f;

	if (fDist < fSize)
	{
		leftSize = _left.bottom - _left.top;
		rightSize = _right.bottom - _right.top;
		leftPt = _left.top + leftSize / 2;
		rightPt = _right.top + rightSize / 2;

		fDist = abs(leftPt - rightPt);
		fSize = leftSize / 2.f + rightSize / 2.f;

		if (fDist < fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}

	return false;
}


int collisionManager::whereAreYouGoing(float& _prevX, float& _prevY, float _x, float _y)
{
	float incrementX = _x - _prevX;
	float incrementY = _y - _prevY;
	_prevX = _x;
	_prevY = _y;
	if (incrementX == 0 && incrementY == 0)
	{
		return FOWARD::NONE;
	}
	if (incrementX > 0 && incrementY == 0)
	{
		return FOWARD::RIGHT;
	}
	if (incrementX < 0 && incrementY == 0)
	{
		return FOWARD::LEFT;
	}
	if (incrementX == 0 && incrementY > 0)
	{
		return FOWARD::DOWN;
	}
	if (incrementX == 0 && incrementY < 0)
	{
		return FOWARD::UP;
	}
	if (incrementX > 0 && incrementY > 0)
	{
		return FOWARD::RIGHTDOWN;
	}
	if (incrementX > 0 && incrementY < 0)
	{
		return FOWARD::RIGHTTOP;
	}
	if (incrementX < 0 && incrementY > 0)
	{
		return FOWARD::LEFTDOWN;
	}
	if (incrementX < 0 && incrementY < 0)
	{
		return FOWARD::LEFTTOP;
	}
}

int collisionManager::whereAreYouGoing(vector2& _prevPt, vector2 _Pt)
{
	float incrementX = _Pt.x - _prevPt.x;
	float incrementY = _Pt.y - _prevPt.y;

	if (incrementX == 0 && incrementY == 0)
	{
		return FOWARD::NONE;
	}
	if (incrementX > 0 && incrementY == 0)
	{
		return FOWARD::RIGHT;
	}
	if (incrementX < 0 && incrementY == 0)
	{
		return FOWARD::LEFT;
	}
	if (incrementX == 0 && incrementY > 0)
	{
		return FOWARD::DOWN;
	}
	if (incrementX == 0 && incrementY < 0)
	{
		return FOWARD::UP;
	}
	if (incrementX > 0 && incrementY > 0)
	{
		return FOWARD::RIGHTDOWN;
	}
	if (incrementX > 0 && incrementY < 0)
	{
		return FOWARD::RIGHTTOP;
	}
	if (incrementX < 0 && incrementY > 0)
	{
		return FOWARD::LEFTDOWN;
	}
	if (incrementX < 0 && incrementY < 0)
	{
		return FOWARD::LEFTTOP;
	}
}


vector2 collisionManager::tileCollision(CMap* _map, vector2 _pt, vector2& _prevPt, int _foward)
{
	float width = 30;
	float height = 30;
	/*float width = TILEWIDTH / 10 * 8;
	float height = TILEHEIGHT / 10 * 8;*/
	
	RECT rc = RectMakeCenter(_pt, width, height);
	RECT prevRc = RectMakeCenter(_prevPt, width, height);

	int hereIndex = (rc.left / TILEWIDTH-1 ) + (rc.top / TILEHEIGHT-1 ) * TILEX;
	

	int testIndex[3] = { 0,1,2 };
	switch (_foward)
	{
	case FOWARD::DOWN:
		testIndex[0] = hereIndex + TILEX;
		testIndex[1] = hereIndex + TILEX + 1;
		break;
	case FOWARD::LEFT:
		testIndex[0] = hereIndex;
		testIndex[1] = hereIndex + TILEX;
		break;
	case FOWARD::RIGHT:
		testIndex[0] = hereIndex + 1;
		testIndex[1] = hereIndex + 1 + TILEX;
		break;
	case FOWARD::UP:
		testIndex[0] = hereIndex ;
		testIndex[1] = hereIndex  + 1;
		break;
	case FOWARD::LEFTDOWN:
		testIndex[0] = hereIndex ;
		testIndex[1] = hereIndex + TILEX;
		testIndex[2] = hereIndex + TILEX + 1;
		//testIndex[3] = hereIndex + TILEX - 1;
		break;
	case FOWARD::LEFTTOP:
		testIndex[0] = hereIndex + TILEX;
		testIndex[1] = hereIndex;
		testIndex[2] = hereIndex + 1;
		//testIndex[3] = hereIndex - TILEX;
		break;
	case FOWARD::RIGHTDOWN:
		testIndex[0] = hereIndex + 1;
		testIndex[1] = hereIndex + TILEX + 1;
		testIndex[2] = hereIndex + TILEX;
		//testIndex[3] = hereIndex + TILEX - 1;
		break;
	case FOWARD::RIGHTTOP:
		testIndex[0] = hereIndex +TILEX +1;
		testIndex[1] = hereIndex + 1;
		testIndex[2] = hereIndex;
		//testIndex[3] = hereIndex - TILEX - 1;
		break;
	default:
		break;
	}
	RECT temprc;
	bool isBump = 0;
	bool cant = 0;
	
	for (int i = 0; i < 3; i++)
	{
		isBump = isCollision(rc, _map->getTile()[testIndex[i]].rcTile);
		//isBump = IntersectRect(&temprc, &_map->getTile()[testIndex[i]].rcTile, &rc);
		cant = (_map->getvObstacle()[testIndex[i]]->getUnmovalbe());
		
		if (isBump && cant)
		{
			switch (_foward)
			{
			case FOWARD::DOWN:
				rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
				rc.top = rc.bottom - height;
				break;
			case FOWARD::LEFT:
				rc.left = _map->getTile()[testIndex[i]].rcTile.right;
				rc.right = rc.left + width;
				break;
			case FOWARD::RIGHT:
				rc.right = _map->getTile()[testIndex[i]].rcTile.left;
				rc.left = rc.right - width;
				break;
			case FOWARD::UP:
				rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
				rc.bottom = rc.top + height;
				break;
			case FOWARD::LEFTDOWN:
				switch (i)
				{
				case 0:
					rc.left = _map->getTile()[testIndex[i]].rcTile.right;
					rc.right = rc.left + width;
					break;
				case 1:
					if (prevRc.left >= _map->getTile()[testIndex[i]].rcTile.right)
					{
						rc.left = _map->getTile()[testIndex[i]].rcTile.right;
						rc.right = rc.left + width;
					}
					else
					{
						rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
						rc.top = rc.bottom - height;
					}
					break;
				case 2:
					rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
					rc.top = rc.bottom - height;
					break;
				}
				break;
			case FOWARD::LEFTTOP:
				switch (i)
				{
				case 0:
					rc.left = _map->getTile()[testIndex[i]].rcTile.right;
					rc.right = rc.left + width;
					break;
				case 1:
					if (prevRc.top >= _map->getTile()[testIndex[i]].rcTile.bottom)
					{
						
						rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
						rc.bottom = rc.top + height;
					}
					else
					{
						rc.left = _map->getTile()[testIndex[i]].rcTile.right;
						rc.right = rc.left + width;
					}
					break;
				case 2:
					rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
					rc.bottom = rc.top + height;
					break;
				}
				break;
			case FOWARD::RIGHTDOWN:
				switch (i)
				{
				case 0:
					rc.right = _map->getTile()[testIndex[i]].rcTile.left;
					rc.left = rc.right - width;
					break;
				case 1:
					if (prevRc.right <= _map->getTile()[testIndex[i]].rcTile.left)
					{
						rc.right = _map->getTile()[testIndex[i]].rcTile.left;
						rc.left = rc.right - width;
					}
					else
					{
						rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
						rc.top = rc.bottom - height;
					}
					break;
				case 2:
					rc.bottom = _map->getTile()[testIndex[i]].rcTile.top;
					rc.top = rc.bottom - height;
					break;
				}
				break;
			case FOWARD::RIGHTTOP:
				switch (i)
				{
				case 0:
					rc.right = _map->getTile()[testIndex[i]].rcTile.left;
					rc.left = rc.right - width;
					break;
				case 1:
					if (prevRc.right <= _map->getTile()[testIndex[i]].rcTile.left)
					{
						rc.right = _map->getTile()[testIndex[i]].rcTile.left;
						rc.left = rc.right - width;
					}
					else
					{
						rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
						rc.bottom = rc.top + height;
					}
					break;
				case 2:
					rc.top = _map->getTile()[testIndex[i]].rcTile.bottom;
					rc.bottom = rc.top + height;
					break;
				}
				break;
			default:
				break;
			}
		}
	}
	vector2 Pt = { RectX(rc), RectY(rc) };
	_prevPt = Pt;
	return Pt;
}
