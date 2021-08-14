#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"
void CStage::update()
{
	player->update();

	//if (InputManager->isStayKeyDown('Y'))
	//{
	//	testPt.y -= 3;
	//}
	//if (InputManager->isStayKeyDown('H'))
	//{
	//	testPt.y += 3;
	//}
	//if (InputManager->isStayKeyDown('G'))
	//{
	//	testPt.x -= 3;
	//}
	//if (InputManager->isStayKeyDown('J'))
	//{
	//	testPt.x += 3;
	//}
	//testFoward = COLLISION->whereAreYouGoing(testPrevPt, testPt);
	////testPt = COLLISION->tileCollision(map, testPt, testSize, testFoward);
	//testRc = RectMakeCenter(testPt, testWidth, testHeight);
	//int hereIndex = (testRc.left / TILEWIDTH - 1) + (testRc.top / TILEHEIGHT) * TILEX;

	//if ((map->getvObstacle()[hereIndex]->getAttribute() & ATTR_UNMOVABLE) == ATTR_UNMOVABLE)
	//{
	//	testPt = { 200, 500 };
	//}
	//testRc = RectMakeCenter(testPt, testWidth, testHeight);
}

void CStage::render()
{
	
	map->render();
	TCHAR str[128];
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			wsprintf(str, "%d", i * TILEX + j);
			TextOut(getMemDC(), map->getTile()[i * TILEX + j].pt.x, map->getTile()[i * TILEX + j].pt.y, str, strlen(str));
		}
	}
	
	/*for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			Rectangle(getMemDC(), map->getTile()[i * TILEX + j].rcTile.left,
				map->getTile()[i * TILEX + j].rcTile.top,
				map->getTile()[i * TILEX + j].rcTile.right,
				map->getTile()[i * TILEX + j].rcTile.bottom);
		}
	}*/
	for (int i = 0; i < map->getvObstacle().size(); i++)
	{
		bool deb = (map->getvObstacle()[i]->getAttribute() & ATTR_UNMOVABLE) == ATTR_UNMOVABLE;
		wsprintf(str, "%d", (map->getvObstacle()[i]->getAttribute() & ATTR_UNMOVABLE) == ATTR_UNMOVABLE);
		TextOut(getMemDC(), map->getvObstacle()[i]->getPt().x, map->getvObstacle()[i]->getPt().y + 20, str, strlen(str));
	}
	
	player->render();

	/*Rectangle(getMemDC(), testRc.left, testRc.top, testRc.right, testRc.bottom);*/
}

void CStage::enter()
{
	player = new CPlayer;
	map = new CMap("save/test.map");

	map->init();
	player->init();

	tagTile* tile = map->getTile();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		map->setMonster(tile[i].monster, tile[i].pt);
	}
	ENEMY->SetPlayer(player);
	player->setRoomLink(map);
	//ENEMY->setPlayerLink(player);
	//testPt = { 500, 500 };
	//testWidth = 30;
	//testHeight = 30;
	//testSize = { 30, 30 };
	//testRc = RectMakeCenter(testPt, testWidth, testHeight);
	//testFoward = 0;
}

void CStage::exit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(map);
}
