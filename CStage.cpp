#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"

void CStage::update()
{
	player->update();
}

void CStage::render()
{
	map->render();
	player->render();
}

void CStage::enter()
{
	player = new CPlayer;
	map = new CMap("save/test.map");

	map->init();
	player->init();

	tagTile* tile = map->getMap();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		map->setMonster(tile[i].monster, tile[i].pt);
	}
	ENEMY->SetPlayer(player);
	player->setRoomLink(map);
	//ENEMY->setPlayerLink(player);
}

void CStage::exit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(map);
}
