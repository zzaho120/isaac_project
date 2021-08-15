#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"
#include "CItem.h"
#include "CMinimap.h"
#include "RandomMapGenerator.h"

void CStage::update()
{
	//player->update();
	if (RectX(rect) < 0 && minimap->getMinimap()[curRoomIdx - 1].roomAttr != ROOM_TYPE_ATTR::NONEROOM)
	{
		changeRoom(curRoomIdx - 1);
		rect = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}
	if (RectX(rect) > WINSIZEX)
	{
		changeRoom(curRoomIdx + 1);
		rect = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}

	if (RectY(rect) < 0)
	{
		changeRoom(curRoomIdx - 10);
		rect = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}
	if (RectY(rect) > WINSIZEY)
	{
		changeRoom(curRoomIdx + 10);
		rect = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}

	if (InputManager->isStayKeyDown(VK_LEFT)) OffsetRect(&rect, -5, 0);
	if (InputManager->isStayKeyDown(VK_RIGHT)) OffsetRect(&rect, 5, 0);
	if (InputManager->isStayKeyDown(VK_UP)) OffsetRect(&rect, 0, -5);
	if (InputManager->isStayKeyDown(VK_DOWN)) OffsetRect(&rect, 0, 5);

	minimap->update();
}

void CStage::render()
{
	curRoom->render();
	//player->render();
	minimap->render();
	Rectangle(getMemDC(), rect.left, rect.top, rect.right, rect.bottom);

	TCHAR str[128];
	wsprintf(str, "%d", curRoomIdx);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
}

void CStage::enter()
{
	curRoomIdx = 0;
	rect = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	//player = new CPlayer;
	minimap = new CMinimap;
	rnd = new RandomMapGenerator;
	rnd->mapGenerate();
	randomMapSetting();
	//player->init();

	/*tagTile* tile = ->getTile();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		map->setMonster(tile[i].monster, tile[i].pt);
	}*/

	ENEMY->SetPlayer(player);/*
	player->setRoomLink(map);*/
	minimap->setRND(rnd);
	minimap->mapAttrSetting();


}

void CStage::exit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(minimap);
	SAFE_DELETE(rnd);
	for(int i = 0; i < 100; i++)
		SAFE_DELETE(room[i]);
}

void CStage::randomMapSetting()
{
	for (int i = 0; i < 100; i++)
	{
		if (rnd->getRNDGenMap()->getRoomType() != ROOM::ROOM_NORMAL) continue;

		room[i] = new CMap(rnd->getRNDGenMap()[i]);
	}

	curRoomIdx = 45;
	curRoom = room[curRoomIdx];

}

void CStage::changeRoom(int roomNum)
{
	curRoomIdx = roomNum;
	curRoom = room[curRoomIdx];
}
