#include "framework.h"
#include "CMinimap.h"
#include "CStage.h"
#include "CMap.h"
#include "RandomMapGenerator.h"

CMinimap::CMinimap()
{
	rnd = new RandomMapGenerator;

	memset(map, 0, sizeof(map));

	int startX = 100;
	int startY = 100;
	//CMap** curMap = STAGE->getCurStage()->getMap();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetRect(&map[i * 10 + j].rc,
				j * MINIMAPROOMX + startX,
				i * MINIMAPROOMY + startY,
				j * MINIMAPROOMX + startX + MINIMAPROOMX,
				i * MINIMAPROOMY + startY + MINIMAPROOMY);
			
			for (int i = 0; i < 100; i++)
			{
				if(i == 45) map[i].attribute[(UINT)MINIMAP_ATTR::ROOM] = ATTR_ROOM_CURROOM;
				else if ((rnd->getRNDGenMap()[i].getRoomAttr() & ATTR_ROOM_NONCHECK) == ATTR_ROOM_NONCHECK)
					map[i].attribute[(UINT)MINIMAP_ATTR::ROOM] = ATTR_ROOM_NONCHECK;

				if((rnd->getRNDGenMap()[i].getMarkAttr() & ATTR_ROOM_BOSS) == ATTR_ROOM_BOSS)
					map[i].attribute[(UINT)MINIMAP_ATTR::MARK] = ATTR_ROOM_BOSS;
				if ((rnd->getRNDGenMap()[i].getMarkAttr() & ATTR_ROOM_SHOP) == ATTR_ROOM_SHOP)
					map[i].attribute[(UINT)MINIMAP_ATTR::MARK] = ATTR_ROOM_SHOP;
				if ((rnd->getRNDGenMap()[i].getMarkAttr() & ATTR_ROOM_REWARD) == ATTR_ROOM_REWARD)
					map[i].attribute[(UINT)MINIMAP_ATTR::MARK] = ATTR_ROOM_REWARD;
			}
			/*int rndnum = RND->getInt(10);
			if(rndnum > 5)
				map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::ROOM] += ATTR_ROOM_CURROOM;
			else if (rndnum > 3) map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::ROOM] += ATTR_ROOM_NONCHECK;
			else map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::ROOM] += ATTR_ROOM_VISITROOM;

			if (rndnum == 5) map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::MARK] += ATTR_ROOM_BOSS;
			else if (rndnum == 3) map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::MARK] += ATTR_ROOM_SHOP;
			else if (rndnum == 1) map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::MARK] += ATTR_ROOM_SPECIAL;
			else map[i * 10 + j].attribute[(UINT)MINIMAP_ATTR::MARK] += ATTR_ROOM_NONEMARK;*/
		}
	}
}

CMinimap::~CMinimap()
{
	SAFE_DELETE(rnd);
}

HRESULT CMinimap::init()
{

	return S_OK;
}

void CMinimap::release()
{
}

void CMinimap::update()
{
}

void CMinimap::render()
{
	int frameX;
	for (int i = 0; i < 100; i++)
	{
		frameX = -1;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::ROOM] & ATTR_ROOM_CURROOM) == ATTR_ROOM_CURROOM)
			frameX = 1;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::ROOM] & ATTR_ROOM_NONCHECK) == ATTR_ROOM_NONCHECK)
			frameX = 0;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::ROOM] & ATTR_ROOM_VISITROOM) == ATTR_ROOM_VISITROOM)
			frameX = 2;
		IMAGE->frameRender("minimapRoom", getMemDC(), map[i].rc.left, map[i].rc.top, frameX, 0);
		frameX = -1;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::MARK] & ATTR_ROOM_NONEMARK) == ATTR_ROOM_NONEMARK)
			frameX = 0;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::MARK] & ATTR_ROOM_BOSS) == ATTR_ROOM_BOSS)
			frameX = 1;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::MARK] & ATTR_ROOM_REWARD) == ATTR_ROOM_REWARD)
			frameX = 2;
		if ((map[i].attribute[(UINT)MINIMAP_ATTR::MARK] & ATTR_ROOM_SHOP) == ATTR_ROOM_SHOP)
			frameX = 3;
		IMAGE->frameRender("minimapMark", getMemDC(), map[i].rc.left, map[i].rc.top, frameX, 0);
	}

	/*TCHAR str[128];
	for (int i = 0; i < rnd->getEndRoom().size(); i++)
	{
		wsprintf(str, "%d", rnd->getEndRoom()[i]);
		TextOut(getMemDC(), 500 + i * 20, 500, str, strlen(str));
	}
	wsprintf(str, "%d", rnd->getFloorplanCount());
	TextOut(getMemDC(), 500, 520, str, strlen(str));
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			wsprintf(str, "%d", i * 10 + j);
			TextOut(getMemDC(), 500 + j * 20, 80 + i * 30, str, strlen(str));
		}
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((rnd->getRNDGenMap()[i * 10 + j].getRoomAttr() & ATTR_ROOM_NONCHECK) == ATTR_ROOM_NONCHECK)
			{
				wsprintf(str, "O");
				TextOut(getMemDC(), 500 + j * 20, 100 + i * 30, str, strlen(str));
			}
		}
	}	*/
}