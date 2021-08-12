#include "framework.h"
#include "CMapSetting.h"

CMapSetting::CMapSetting() : isDebug(false), roomType(ROOM::ROOM_NORMAL)
{
    mapToolSetup();
}

CMapSetting::~CMapSetting()
{
}

HRESULT CMapSetting::init()
{
    isDebug = false;
    roomType = ROOM::ROOM_NORMAL;
    mapToolSetup();
    return S_OK;
}

void CMapSetting::release()
{
}

void CMapSetting::update()
{
    if (!SUBWIN->GetIsActive() && InputManager->isStayKeyDown(VK_LBUTTON)) setMap();
    if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_F5)) isDebug = !isDebug;
    roomType = (ROOM)SUBWIN->GetRoomFrame().x;
}

void CMapSetting::render()
{
    switch (roomType)
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
    {
        if (isDebug)
        {
            if(_tile[i].obj == OBJECT::OBJ_WALL)
                Rectangle(getMemDC(), _tile[i].rcTile.left, _tile[i].rcTile.top, _tile[i].rcTile.right, _tile[i].rcTile.bottom);
        }
        IMAGE->frameRender("objectTile", getMemDC(), _tile[i].rcTile.left, _tile[i].rcTile.top, _tile[i].objFrame.x, _tile[i].objFrame.y);
        IMAGE->frameRender("monsterTile", getMemDC(), _tile[i].rcTile.left, _tile[i].rcTile.top, _tile[i].monsterFrame.x, _tile[i].monsterFrame.y);
    }

    TCHAR str[128];
    wsprintf(str, "%d %d", m_ptMouse);
    TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void CMapSetting::tileInit()
{
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        bool isWall = i < 15 || i % TILEX == 0 || i % TILEX == 14 || i > TILEX * TILEY - 15;
        if (isWall) _tile[i].obj = OBJECT::OBJ_WALL;
        else _tile[i].obj = OBJECT::OBJ_NONE;
        _tile[i].monster = MONSTER_TYPE::NONE;

        _tile[i].objFrame = 0;
        _tile[i].monsterFrame = 0;
    }
}

void CMapSetting::mapToolSetup()
{
    for (int i = 0; i < TILEY; i++)
    {
        for (int j = 0; j < TILEX; j++)
        {
            SetRect(&_tile[i * TILEX + j].rcTile,
                j * TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + MAPSTARTY,
                j * TILEWIDTH + TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + TILEHEIGHT + MAPSTARTY);
        }
    }
    tileInit();
}

void CMapSetting::setMap()
{
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (PtInRect(&_tile[i].rcTile, m_ptMouse))
        {
            bool isNonMon = _tile[i].monsterFrame.x == 0 && _tile[i].monsterFrame.y == 0;
            bool isWall = _tile[i].obj == OBJECT::OBJ_WALL;
            if (isNonMon && !isWall)
            {
                _tile[i].objFrame = { static_cast<float>(SUBWIN->GetObjFrame().x), static_cast<float>(SUBWIN->GetObjFrame().y) };
                _tile[i].obj = objSelect(SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
                InvalidateRect(m_hWnd, NULL, false);
            }
        }
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (PtInRect(&_tile[i].rcTile, m_ptMouse))
        {
            bool isNonObj = _tile[i].objFrame.x == 0 && _tile[i].objFrame.y == 0;
            bool isWall = _tile[i].obj == OBJECT::OBJ_WALL;
            if (isNonObj && !isWall)
            {
                _tile[i].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
                _tile[i].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };
                InvalidateRect(m_hWnd, NULL, false);
            }
        }
    }

    // must modified
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (_tile[i].monster == MONSTER_TYPE::GURDY)
        {
            bool isRightWall = _tile[i + 1].obj == OBJECT::OBJ_WALL;
            if (isRightWall)
            {
                _tile[i].monster = MONSTER_TYPE::NONE;
                _tile[i].monsterFrame = 0;
                break;
            }

            _tile[i].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
            _tile[i].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };

            /*_tile[i + 1].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
            _tile[i + 1].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };

            _tile[i + TILEX].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
            _tile[i + TILEX].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };

            _tile[i + TILEX + 1].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
            _tile[i + TILEX + 1].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };*/

            break;
        }
    }
}

bool CMapSetting::save(const char* fileName)
{
    HANDLE file;
    DWORD write;
    bool result;

    file = CreateFile(fileName,
        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    result = WriteFile(file, _tile, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

    CloseHandle(file);

    return result;
}

bool CMapSetting::load(const char* fileName)
{
    HANDLE file;
    DWORD read;
    bool result;

    file = CreateFile(fileName,
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    result = ReadFile(file, _tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
    CloseHandle(file);

    return result;
}

OBJECT CMapSetting::objSelect(int frameX, int frameY)
{
    if (frameY == 0)
    {
        switch (frameX)
        {
        case 0:
            return OBJECT::OBJ_NONE;
            break;

        case 1:
            return OBJECT::OBJ_POOP;
            break;

        case 2:
            return OBJECT::OBJ_SPIKE;
            break;

        case 3:
            return OBJECT::OBJ_ROCK;
            break;

        case 4:
            return OBJECT::OBJ_STEEL;
            break;

        case 5:
            return OBJECT::OBJ_FIREPLACE;
            break;
        }
    }
    else if (frameY == 1 || frameY == 2)
        return OBJECT::OBJ_PIT;
}

MONSTER_TYPE CMapSetting::monsterSelect(int frameX, int frameY)
{
    if (frameY == 0)
    {
        switch (frameX)
        {
        case 0:
            return MONSTER_TYPE::NONE;
            break;
        case 1:
            return MONSTER_TYPE::WORM;
            break;
        case 2:
            return MONSTER_TYPE::FLY;
            break;
        case 3:
            return MONSTER_TYPE::HOST;
            break;
        case 4:
            return MONSTER_TYPE::HOPPER;
            break;
        case 5:
            return MONSTER_TYPE::MULLIGAN;
            break;
        case 6:
            return MONSTER_TYPE::GURDY;
            break;
        }
    }
}
