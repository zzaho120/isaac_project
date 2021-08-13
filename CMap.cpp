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
    // obstacle Collider must modifiy jusu
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
    }/*
    for (int i = 0; i < TILEX * TILEY; i++)
        IMAGE->frameRender("objectTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].objFrame.x, room.tile[i].objFrame.y);*/
    for(viObstacle = vObstacle.begin(); viObstacle != vObstacle.end(); viObstacle++)
        IMAGE->frameRender("objectTile", getMemDC(), (*viObstacle)->getPt().x, (*viObstacle)->getPt().y, (*viObstacle)->getFrame().x, (*viObstacle)->getFrame().y);

    if (vObstacle.size() > 0)
    {
        TCHAR str[128];
        wsprintf(str, "%d %d", vObstacle.size(), vObstacle[0]->getFrame().x);
        TextOut(getMemDC(), 100, 100, str, strlen(str));

        vObstacle[0]->render();
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        TCHAR str1[128];
        wsprintf(str1, "%d", (int)room.tile[i].obj);
        TextOut(getMemDC(), room.tile[i].pt.x, room.tile[i].pt.y, str1, strlen(str1));
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

            if (room.tile[i * TILEX + j].obj != OBJECT::OBJ_NONE)
            {
                CObstacle* tempObstacle = new CObstacle(room.tile[i * TILEX + j].pt, 
                    RectMakeCenter(room.tile[i * TILEX + j].pt, TILEWIDTH, TILEHEIGHT), 
                    room.tile[i * TILEX + j].obj);

                vObstacle.push_back(tempObstacle);
            }
        }
    }
}
