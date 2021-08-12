#include "framework.h"
#include "CMapSettingSub.h"

CMapSettingSub::CMapSettingSub() : isDebug(false)
{
    mapToolSetup();
}

CMapSettingSub::~CMapSettingSub()
{
}

HRESULT CMapSettingSub::init()
{
    isDebug = false;
    mapToolSetup();
    return S_OK;
}

void CMapSettingSub::release()
{ }

void CMapSettingSub::update()
{
    if (SUBWIN->GetIsActive() && InputManager->isStayKeyDown(VK_LBUTTON)) setMap();
    if (InputManager->isOnceKeyDown(VK_SHIFT)) isDebug = !isDebug;
}

void CMapSettingSub::render(HDC hdc)
{
    IMAGE->render("objMap", hdc, 0, SUBWINSIZEY - IMAGE->findImage("objMap")->getHeight());
    IMAGE->render("monsterMap", hdc, 0, SUBWINSIZEY - IMAGE->findImage("objMap")->getHeight() - IMAGE->findImage("monsterMap")->getHeight());
    TCHAR currentSelect[64];
    wsprintf(currentSelect, "monX : %d, monY : %d, objX : %d, objY : %d", 
        SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y, SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
    TextOut(hdc, 10, 240, currentSelect, strlen(currentSelect));
    if (isDebug)
    {
        for (int i = 0; i < SAMPLETILEY; i++)
        {
            for (int j = 0; j < SAMPLETILEX; j++)
            {
                Rectangle(hdc, _sampleTiles[i * SAMPLETILEX + j].rcTile.left,
                    _sampleTiles[i * SAMPLETILEX + j].rcTile.top,
                    _sampleTiles[i * SAMPLETILEX + j].rcTile.right,
                    _sampleTiles[i * SAMPLETILEX + j].rcTile.bottom);
            }
        }

        for (int i = 0; i < MONSTERTILEY; i++)
        {
            for (int j = 0; j < MONSTERTILEX; j++)
            {
                Rectangle(hdc, _monsterTile[i * SAMPLETILEX + j].rcTile.left,
                    _monsterTile[i * SAMPLETILEX + j].rcTile.top,
                    _monsterTile[i * SAMPLETILEX + j].rcTile.right,
                    _monsterTile[i * SAMPLETILEX + j].rcTile.bottom);
            }
        }
    }
}

void CMapSettingSub::mapToolSetup()
{
    for (int i = 0; i < SAMPLETILEY; i++)
    {
        for (int j = 0; j < SAMPLETILEX; j++)
        {
            _sampleTiles[i * SAMPLETILEX + j].objFrame.x = j;
            _sampleTiles[i * SAMPLETILEX + j].objFrame.y = i;
            
            _sampleTiles[i * SAMPLETILEX + j].rcTile = 
                RectMake(
                    TILEWIDTH * j, SUBWINSIZEY - IMAGE->findImage("objMap")->getHeight() + TILEHEIGHT * i,
                    TILEWIDTH, TILEHEIGHT);
        }
    }

    for (int i = 0; i < MONSTERTILEY; i++)
    {
        for (int j = 0; j < MONSTERTILEX; j++)
        {
            _monsterTile[i * MONSTERTILEX + j].monsterFrame.x = j;
            _monsterTile[i * MONSTERTILEX + j].monsterFrame.y = i;

            _monsterTile[i * MONSTERTILEX + j].rcTile =
                RectMake(
                    TILEWIDTH * j, SUBWINSIZEY - IMAGE->findImage("objMap")->getHeight() - IMAGE->findImage("monsterMap")->getHeight() + TILEHEIGHT * i,
                    TILEWIDTH, TILEHEIGHT);
        }
    }
}

void CMapSettingSub::setMap()
{
   for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
   {
        if (PtInRect(&_sampleTiles[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetObjFrame(PointMake(_sampleTiles[i].objFrame.x, _sampleTiles[i].objFrame.y));
        }
   }
   for (int i = 0; i < MONSTERTILEX * MONSTERTILEY; i++)
   {
       if (PtInRect(&_monsterTile[i].rcTile, SUBWIN->GetMousePos()))
       {
           SUBWIN->SetMonsterFrame(PointMake(_monsterTile[i].monsterFrame.x, _monsterTile[i].monsterFrame.y));
       }
   }
}
