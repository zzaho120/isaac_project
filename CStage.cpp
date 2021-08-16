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
	player->update();
	minimap->update();
}

void CStage::render()
{
	curRoom->render();
	player->render();
	minimap->render();

	TCHAR str[128];
	wsprintf(str, "%d", curRoomIdx);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
}

void CStage::enter()
{
	curRoomIdx = 0;
	player = new CPlayer;
	minimap = new CMinimap;
	rnd = new RandomMapGenerator;
	rnd->mapGenerate();
	randomMapSetting();
	player->init();

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
		room[i] = new CMap(*rnd->getRNDGenMap(i));
	}

	curRoomIdx = 45;
	curRoom = room[curRoomIdx];
}

void CStage::changeRoom(int roomNum)
{
	curRoomIdx = roomNum;
	curRoom = room[curRoomIdx];
}
