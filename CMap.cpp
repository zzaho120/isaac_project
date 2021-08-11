#include"framework.h"
#include "CMap.h"

CMap::CMap()
{
    load();
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
    load();
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
    IMAGE->render("map", getMemDC(), 0, 0);
    for (int i = 0; i < TILEX * TILEY; i++)
        IMAGE->frameRender("objMap", getMemDC(), _obj[i].rcTile.left, _obj[i].rcTile.top, _obj[i].objFrameX, _obj[i].objFrameY);
}

void CMap::load()
{
    HANDLE file;
    DWORD read;

    file = CreateFile("save/Map2.map",
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    ReadFile(file, _obj, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
    CloseHandle(file);
}

void CMap::load(const char* fileName)
{
    HANDLE file;
    DWORD read;

    file = CreateFile(fileName,
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    ReadFile(file, _obj, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
    CloseHandle(file);
}

void CMap::tileSet()
{
    for (size_t i = 0; i < TILEY; i++)
    {
        for (size_t j = 0; j < TILEX; j++)
        {
            SetRect(&_obj[i * TILEX + j].rcTile,
                j * TILEWIDTH + mapStartX,
                i * TILEHEIGHT + mapStartY,
                j * TILEWIDTH + TILEWIDTH + mapStartX,
                i * TILEHEIGHT + TILEHEIGHT + mapStartY);

            _obj[i * TILEX + j].pt.x = RectX(_obj[i * TILEX + j].rcTile);
            _obj[i * TILEX + j].pt.y = RectY(_obj[i * TILEX + j].rcTile);

            switch (_obj[i * TILEX + j].obj)
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
            case OBJECT::OBJ_GOAL:
                break;
            }
        }
    }
}
