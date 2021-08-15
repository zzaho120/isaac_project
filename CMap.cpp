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

    vObstacle.swap(map.vObstacle);

    roomAttr = map.roomAttr;
    markAttr = map.markAttr;
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
}

void CMap::render(int destX, int destY)
{
    switch (room.roomType)
    {
    case ROOM::ROOM_NORMAL:
        IMAGE->render("basement_normal", getMemDC(), destX * MAPSIZEX, destY * MAPSIZEY);
        break;
    case ROOM::ROOM_BOSS:
        IMAGE->render("basement_boss", getMemDC(), destX * MAPSIZEX, destY * MAPSIZEY);
        break;
    case ROOM::ROOM_SHOP:
        IMAGE->render("shop", getMemDC(), destX * MAPSIZEX, destY * MAPSIZEY);
        break;
    }
    for (viObstacle = vObstacle.begin(); viObstacle != vObstacle.end(); viObstacle++)
    {
        (*viObstacle)->render();
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
        //vObstacle[7]->setObjType(OBJECT::OBJ_DOOR);
        break;
    case DOOR_DIRECTION::LEFT:
       // vObstacle[60]->setObjType(OBJECT::OBJ_DOOR);
        break;
    case DOOR_DIRECTION::RIGHT:
        //vObstacle[74]->setObjType(OBJECT::OBJ_DOOR);
        break;
    case DOOR_DIRECTION::BOTTOM:
       // vObstacle[127]->setObjType(OBJECT::OBJ_DOOR);
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
