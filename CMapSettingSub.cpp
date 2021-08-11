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
            _sampleTiles[i * SAMPLETILEX + j].objFrameX = j;
            _sampleTiles[i * SAMPLETILEX + j].objFrameY = i;
            
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
            _monsterTile[i * MONSTERTILEX + j].monsterFrameX = j;
            _monsterTile[i * MONSTERTILEX + j].monsterFrameY = i;

            _monsterTile[i * MONSTERTILEX + j].rcTile =
                RectMake(
                    TILEWIDTH * j, SUBWINSIZEY - IMAGE->findImage("objMap")->getHeight() - IMAGE->findImage("monsterMap")->getHeight() + TILEHEIGHT * i,
                    TILEWIDTH, TILEHEIGHT);
        }
    }
}

void CMapSettingSub::setMap()
{
   for (size_t i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
   {
        if (PtInRect(&_sampleTiles[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetObjFrame(PointMake(_sampleTiles[i].objFrameX, _sampleTiles[i].objFrameY));
        }
        if (PtInRect(&_monsterTile[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetMonsterFrame(PointMake(_monsterTile[i].monsterFrameX, _monsterTile[i].monsterFrameY));
        }
   }
}
