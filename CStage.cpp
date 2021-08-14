#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"

void CStage::update()
{
	player->update();
}

void CStage::render()
{
	map->render();
	player->render();

	// why obstacle size 108??
	int num = 0;
	int size = 0;
	TCHAR str[128];
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			wsprintf(str, "%d", i * TILEX + j);
			TextOut(getMemDC(), map->getMap()[i * TILEX + j].pt.x, map->getMap()[i * TILEX + j].pt.y, str, strlen(str));
		}
	}
	for (int i = 0; i < map->getvObstacle().size(); i++)
	{
		bool isTrue = (map->getvObstacle()[i]->getAttribute() & ATTR_UNMOVABLE) == ATTR_UNMOVABLE;
		if (isTrue)
		{
			wsprintf(str, "O");
			TextOut(getMemDC(), map->getvObstacle()[i]->getPt().x, map->getvObstacle()[i]->getPt().y + 20, str, strlen(str));
			num++;
		}
		size++;
	}
	wsprintf(str, "%d %d %d", num, size, map->getvObstacle().size());
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			Rectangle(getMemDC(), map->getMap()[i * TILEX + j].rcTile.left,
				map->getMap()[i * TILEX + j].rcTile.top,
				map->getMap()[i * TILEX + j].rcTile.right,
				map->getMap()[i * TILEX + j].rcTile.bottom);
		}
	}


	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
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
