#include "framework.h"
#include "CMapSetting.h"

CMapSetting::CMapSetting() : isDebug(false)
{
    mapToolSetup();
}

CMapSetting::~CMapSetting()
{
}

HRESULT CMapSetting::init()
{
    isDebug = false;
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
}

void CMapSetting::render()
{
    IMAGE->render("map", getMemDC(), 0, 0);
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (isDebug) Rectangle(getMemDC(), _tile[i].rcTile.left, _tile[i].rcTile.top, _tile[i].rcTile.right, _tile[i].rcTile.bottom);
        IMAGE->frameRender("objMap", getMemDC(), _tile[i].rcTile.left, _tile[i].rcTile.top, _tile[i].objFrameX, _tile[i].objFrameY);
        IMAGE->frameRender("monsterMap", getMemDC(), _tile[i].rcTile.left, _tile[i].rcTile.top, _tile[i].monsterFrameX, _tile[i].monsterFrameY);
    }

    TCHAR str[128];
    wsprintf(str, "%d %d", m_ptMouse);
    TextOut(getMemDC(), 100, 100, str, strlen(str));
}

void CMapSetting::tileInit()
{
    for (size_t i = 0; i < TILEX * TILEY; i++)
    {
        _tile[i].objFrameX = 0;
        _tile[i].objFrameY = 0;
        _tile[i].monsterFrameX = 0;
        _tile[i].monsterFrameY = 0;
        _tile[i].obj = OBJECT::OBJ_NONE;
        _tile[i].monster = MONSTER_TYPE::NONE;
    }
}

void CMapSetting::mapToolSetup()
{
    for (size_t i = 0; i < TILEY; i++)
    {
        for (size_t j = 0; j < TILEX; j++)
        {
            SetRect(&_tile[i * TILEX + j].rcTile,
                j * TILEWIDTH + mapStartX,
                i * TILEHEIGHT + mapStartY,
                j * TILEWIDTH + TILEWIDTH + mapStartX,
                i * TILEHEIGHT + TILEHEIGHT + mapStartY);
        }
    }
    tileInit();
}

void CMapSetting::setMap()
{
    for (size_t i = 0; i < TILEX * TILEY; i++)
    {
        if (PtInRect(&_tile[i].rcTile, m_ptMouse))
        {
            bool isNonMon = _tile[i].monsterFrameX == 0 && _tile[i].monsterFrameY == 0;
            if (isNonMon)
            {
                _tile[i].objFrameX = SUBWIN->GetObjFrame().x;
                _tile[i].objFrameY = SUBWIN->GetObjFrame().y;
                _tile[i].obj = objSelect(SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
                InvalidateRect(m_hWnd, NULL, false);
            }
        }
    }

    for (size_t i = 0; i < TILEX * TILEY; i++)
    {
        if (PtInRect(&_tile[i].rcTile, m_ptMouse))
        {
            bool isNonObj = _tile[i].objFrameX == 0 && _tile[i].objFrameY == 0;
            if (isNonObj)
            {
                _tile[i].monsterFrameX = SUBWIN->GetMonsterFrame().x;
                _tile[i].monsterFrameY = SUBWIN->GetMonsterFrame().y;
                _tile[i].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
                InvalidateRect(m_hWnd, NULL, false);
            }
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

    file = CreateFile("save/Map2.map",
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
            return MONSTER_TYPE::MULLIGAN;
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
        }
    }
}
