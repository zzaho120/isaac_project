#include"framework.h"
#include "CObstacle.h"
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

CMap::CMap(CMap& map)
{
    for (int i = 0; i < TILEX * TILEY; i++)
        room.tile[i] = map.room.tile[i];
    
    room.roomType = map.room.roomType;

    for (int i = 0; i < map.vObstacle.size(); i++)
    {
        vObstacle.push_back(map.vObstacle[i]);
    }

    roomAttr = map.roomAttr;
    markAttr = map.markAttr;
}

CMap::CMap(CMap* map)
{
    for (int i = 0; i < TILEX * TILEY; i++)
        room.tile[i] = map->room.tile[i];

    room.roomType = map->room.roomType;

    for (int i = 0; i < map->vObstacle.size(); i++)
    {
        vObstacle.push_back(map->vObstacle[i]);
    }

    roomAttr = map->roomAttr;
    markAttr = map->markAttr;
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
    for (viObstacle = vObstacle.begin(); viObstacle != vObstacle.end(); viObstacle++)
    {
        (*viObstacle)->render();
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (room.tile[i].obj == OBJECT::OBJ_TOPDOOR)
            IMAGE->frameRender("normalDoor", getMemDC(), room.tile[i].rcTile.left - 52, room.tile[i].rcTile.top - 50, 0, 0);
        if (room.tile[i].obj == OBJECT::OBJ_BOTTOMDOOR)
            IMAGE->frameRender("normalDoor", getMemDC(), room.tile[i].rcTile.left - 52, room.tile[i].rcTile.top - 25, 1, 0);
        if (room.tile[i].obj == OBJECT::OBJ_LEFTDOOR)
            IMAGE->frameRender("normalDoor", getMemDC(), room.tile[i].rcTile.left - 70, room.tile[i].rcTile.top - 40, 2, 0);
        if (room.tile[i].obj == OBJECT::OBJ_RIGHTDOOR)
            IMAGE->frameRender("normalDoor", getMemDC(), room.tile[i].rcTile.left - 27, room.tile[i].rcTile.top - 40, 3, 0);
    }
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
        }
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        CObstacle* tempObstacle = new CObstacle(room.tile[i].pt,
                RectMakeCenter(room.tile[i].pt, TILEWIDTH, TILEHEIGHT),
                room.tile[i].obj);

        vObstacle.push_back(tempObstacle);
    }
}

void CMap::doorSetting(DOOR_DIRECTION direction)
{
    switch (direction)
    {
    case DOOR_DIRECTION::TOP:
        room.tile[7].obj = OBJECT::OBJ_TOPDOOR;
        vObstacle[7]->setObjType(OBJECT::OBJ_TOPDOOR);
        vObstacle[7]->setUnmovalbe(false);
        break;
    case DOOR_DIRECTION::LEFT:
        room.tile[60].obj = OBJECT::OBJ_LEFTDOOR;
        vObstacle[60]->setObjType(OBJECT::OBJ_LEFTDOOR);
        vObstacle[60]->setUnmovalbe(false);
        break;
    case DOOR_DIRECTION::RIGHT:
        room.tile[74].obj = OBJECT::OBJ_RIGHTDOOR;
        vObstacle[74]->setObjType(OBJECT::OBJ_RIGHTDOOR);
        vObstacle[74]->setUnmovalbe(false);
        break;
    case DOOR_DIRECTION::BOTTOM:
        room.tile[127].obj = OBJECT::OBJ_BOTTOMDOOR;
        vObstacle[127]->setObjType(OBJECT::OBJ_BOTTOMDOOR);
        vObstacle[127]->setUnmovalbe(false);
        break;
    default:
        return;
    }
}

void CMap::setMonster(MONSTER_TYPE type, vector2 pt)
{
    ENEMY->respawnMinion(type, pt);
}

vector<CObstacle*>::iterator CMap::getviObstacle(int number)
{
    viObstacle = vObstacle.begin() + number;
    return viObstacle;
}
