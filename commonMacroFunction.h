#pragma once
//===============================================
//commonMacroFunction(�ʿ��� �κ��� �����������)
//===============================================

//����Ʈ
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT�����(�»�� ����)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}
//RECT�����(�߽������� ����)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}
//RECT�����(�»�� ����)
inline RECT RectMake(vector2 vec, int width, int height)
{
	RECT rc = { vec.x, vec.y, vec.x + width, vec.y + height };
	return rc;
}
//RECT�����(�߽������� ����)
inline RECT RectMakeCenter(vector2 vec, int width, int height)
{
	RECT rc = { vec.x - width / 2, vec.y - height / 2, vec.x + width / 2, vec.y + height / 2 };
	return rc;
}

//�簢�� �׸���
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

//�� �׸���
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

const int TILEX = 15;
const int TILEY = 9;

const int TILESIZEX = TILEX * TILEWIDTH;
const int TILESIZEY = TILEY * TILEHEIGHT;

const int OBJECTTILEX = 6;
const int OBJECTTILEY = 3;

const int MONSTERTILEX = 7;
const int MONSTERTILEY = 1;

const int ROOMTILEX = 3;
const int ROOMTILEY = 1;

const int MAPSIZEX = 1024 - 15;
const int MAPSIZEY = 768 - 39;

const int MAPSTARTX = 132 - 57;
const int MAPSTARTY = 143 - 63;

const int SUBWINSIZEX = 420;
const int SUBWINSIZEY = 500;

#define ATTR_UNMOVABLE 0x00000001
#define ATTR_ONLYBOMB 0x00000002


// map object
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

enum class ROOM
{
	ROOM_NORMAL,
	ROOM_BOSS,
	ROOM_SHOP,
	ROOM_END
};

// un-develop
enum class ITEM
{
	ITEM_BOMB,
	ITEM_KEY,
	ITEM_COIN,
	ITEM_HEART,
	ITEM_HALF_HEART,
	ITEM_NONE
};

// sub-window button function
enum class CTRL
{
	CTRL_DRAW,
	CTRL_INIT,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_EXIT,
	CTRL_EDIT,
	CTRL_LIST,
	CTRL_SETROOM,
	CTRL_REMOVE,
	CTRL_MONSTER,
	CTRL_OBJECT,
	CTRL_ROOM,
	CTRL_ITEM,
	CTRL_END
};

struct tagTile
{
	OBJECT obj;
	MONSTER_TYPE monster;
	RECT rcTile;

	Vec2 objFrame;
	Vec2 monsterFrame;
	Vec2 pt;
};

struct tagSampleTile
{
	RECT rcTile;
	Vec2 frame;
};

struct tagOBJAttribute
{
	int strength;
};


// ============================================= MapInfo ===================================================
// ============================================= MapInfo ===================================================