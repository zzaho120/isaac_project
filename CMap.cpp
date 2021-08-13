#include"framework.h"
#include "CMap.h"

CMap::CMap()
{
    tileSet();
}

CMap::CMap(const char* fileName)
{
    load(fileName);
    tileSet();
}

CMap::~CMap()
{
}

HRESULT CMap::init()
{
    tileSet();
    return S_OK;
}

HRESULT CMap::init(const char* fileName)
{
    load(fileName);
    tileSet();
    return S_OK;
}

void CMap::release()
{
}

void CMap::update()
{
 
}

void CMap::render()
{
    switch(room.roomType)
    {
    case ROOM::ROOM_NORMAL:
        IMAGE->render("basement_normal", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_BOSS:
        IMAGE->render("basement_boss", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_SHOP:
        IMAGE->render("shop", getMemDC(), 0, 0);
        break;
    }
    for (int i = 0; i < TILEX * TILEY; i++)
        IMAGE->frameRender("objectTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].objFrame.x, room.tile[i].objFrame.y);
}

void CMap::load(const char* fileName)
{
    HANDLE file;
    DWORD read;
    tagRoom load[1];

    file = CreateFile(fileName,
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    ReadFile(file, load, sizeof(tagRoom), &read, NULL);
    room = load[0];

    CloseHandle(file);
}

void CMap::tileSet()
{
    for (size_t i = 0; i < TILEY; i++)
    {
        for (size_t j = 0; j < TILEX; j++)
        {
            SetRect(&room.tile[i * TILEX + j].rcTile,
                j * TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + MAPSTARTY,
                j * TILEWIDTH + TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + TILEHEIGHT + MAPSTARTY);

            room.tile[i * TILEX + j].pt.x = RectX(room.tile[i * TILEX + j].rcTile);
            room.tile[i * TILEX + j].pt.y = RectY(room.tile[i * TILEX + j].rcTile);

            switch (room.tile[i * TILEX + j].obj)
            {
            case OBJECT::OBJ_FIREPLACE:
                _OBJattribute[i * TILEX + j].strength = 3;
                break;
            case OBJECT::OBJ_SPIKE:
                break;
            case OBJECT::OBJ_POOP:
                _OBJattribute[i * TILEX + j].strength = 3;
                break;
            case OBJECT::OBJ_ROCK:
                _attribute[i * TILEX + j] |= ATTR_UNMOVABLE;
                _attribute[i * TILEX + j] |= ATTR_ONLYBOMB;
                break;
            case OBJECT::OBJ_STEEL:
                _attribute[i * TILEX + j] |= ATTR_UNMOVABLE;
                break;
            case OBJECT::OBJ_PIT:
                _attribute[i * TILEX + j] |= ATTR_UNMOVABLE;
                break; 
            case OBJECT::OBJ_WALL:
                _attribute[i * TILEX + j] |= ATTR_UNMOVABLE;
                break;
            case OBJECT::OBJ_GOAL:
                break;
            }
        }
    }
}
