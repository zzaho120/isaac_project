#pragma once
//===============================================
//commonMacroFunction(필요한 부분은 직접만들어써라)
//===============================================

//포인트
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//선그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT만들기(좌상단 기준)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}
//RECT만들기(좌상단 기준)
inline RECT RectMake(vector2 vec, int width, int height)
{
	RECT rc = { vec.x, vec.y, vec.x + width, vec.y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(vector2 vec, int width, int height)
{
	RECT rc = { vec.x - width / 2, vec.y - height / 2, vec.x + width / 2, vec.y + height / 2 };
	return rc;
}

//사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc, RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
inline void ElllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void BeginSolidColor(HDC hdc, HBRUSH* brush, COLORREF color)
{
	*brush = CreateSolidBrush(color);
	*brush = (HBRUSH)SelectObject(hdc, *brush);
}

inline float RectX(RECT rec)
{
	float x = ((rec.right - rec.left) / 2) + rec.left;
	return x;
}
inline float RectY(RECT rec)
{
	float y = ((rec.bottom - rec.top) / 2) + rec.top;
	return y;
}
inline float RectWidth(RECT rec)
{
	float width = rec.right - rec.left;
	return width;
}
inline float RectHeight(RECT rec)
{
	float height = rec.bottom - rec.top;
	return height;
}
inline RECT& movetoRight(RECT& rec, int speed)
{
	OffsetRect(&rec, speed, 0);

	return rec;
}
inline RECT& movetoLeft(RECT& rec, int speed)
{
	OffsetRect(&rec, -speed, 0);
	return rec;
}
inline RECT& movetoUp(RECT& rec, int speed)
{
	OffsetRect(&rec, 0, -speed);
	return rec;
}
inline RECT& movetoDown(RECT& rec, int speed)
{
	OffsetRect(&rec, 0, speed);
	return rec;
}

enum class STATE_TYPE
{
	IDLE,
	TRACE,
	ATTACK,
	DEAD,
};

enum class MONSTER_TYPE
{
	NONE,
	FLY,
	HOPPER,
	HOST,
	MULLIGAN,
	WORM,
	GURDY,
	SMALLFLY
};

// ============================================= MapInfo ===================================================
// ============================================= MapInfo ===================================================
const int TILEWIDTH = 57;
const int TILEHEIGHT = 63;
const int TILEX = 13;
const int TILEY = 7;
const int TILESIZEX = TILEX * TILEWIDTH;
const int TILESIZEY = TILEY * TILEHEIGHT;
const int SAMPLETILEX = 6;
const int SAMPLETILEY = 3;
const int MONSTERTILEX = 6;
const int MONSTERTILEY = 1;
const int MAPSIZEX = 1024 - 15;
const int MAPSIZEY = 768 - 39;
const int mapStartX = 132;
const int mapStartY = 143;

#define ATTR_UNMOVABLE 0x00000001
#define ATTR_ONLYBOMB 0x00000002

enum class OBJECT
{
	OBJ_GOAL,
	OBJ_FIREPLACE,
	OBJ_SPIKE,
	OBJ_POOP,
	OBJ_ROCK,
	OBJ_STEEL,
	OBJ_PIT,
	OBJ_WALL,
	OBJ_DOOR,
	OBJ_NONE
};

enum class ITEM
{
	ITEM_BOMB,
	ITEM_KEY,
	ITEM_COIN,
	ITEM_HEART,
	ITEM_HALF_HEART,
	ITEM_NONE
};

struct tagTile
{
	OBJECT obj;
	MONSTER_TYPE monster;
	RECT rcTile;

	int objFrameX;
	int objFrameY;
	int monsterFrameX;
	int monsterFrameY;

	vector2 pt;
};

struct tagObjectTile
{
	RECT rcTile;
	int objFrameX;
	int objFrameY;
};

struct tagMonsterTile
{
	RECT rcTile;
	int monsterFrameX;
	int monsterFrameY;
};
struct tagCurrentTile
{
	int x;
	int y;
};

struct tagOBJAttribute
{
	int strength;
};


// ============================================= MapInfo ===================================================
// ============================================= MapInfo ===================================================