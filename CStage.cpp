#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"
#include "CItem.h"

void CStage::update()
{
	player->update();

	for (int i = 0; i < ITEM->getItem().size(); i++)
	{
		bool isIbcp = COLLISION->isCollision((*ITEM->getviItem(i))->getcollider(), player->getcollider());
		bool isIbsp = COLLISION->isCollision((*ITEM->getviItem(i))->GetcolliderShadow(), player->GetcolliderShadow());
		if (isIbcp && isIbsp)
		{
			switch ((*ITEM->getviItem(i))->getItemType())
			{
			case ITEM_TYPE::ITEM_HEART:
				if (player->isFullHp()) { break; }
				else
				{
					player->sethp(player->gethp() + 2);
					player->cantHpOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE ::ITEM_COIN:
				if (player->getCoin() >= 99) { break; }
				else
				{
					player->setCoin(player->getCoin() + 1);
					player->cantCoinOver();
					ITEM->itemRemove(i);
					break;
				}
			default:
				break;
			}
			break;
		}
	}
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
	player->render();
	playerUI->render(player);
	// why obstacle size 108??
	int num = 0;
	int size = 0;
	TCHAR str[128];
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			wsprintf(str, "%d", i * TILEX + j);
			TextOut(getMemDC(), map->getTile()[i * TILEX + j].pt.x, map->getTile()[i * TILEX + j].pt.y, str, strlen(str));
		}
	}
	for (int i = 0; i < map->getvObstacle().size(); i++)
	{
		bool isTrue = map->getvObstacle()[i]->getUnmovalbe();
		if (isTrue)
		{
			wsprintf(str, "O   %d", (UINT)map->getTile()[i].obj);
			TextOut(getMemDC(), map->getvObstacle()[i]->getPt().x, map->getvObstacle()[i]->getPt().y + 20, str, strlen(str));
			num++;
		}
		size++;
	}
	wsprintf(str, "%d %d %d", num, size, map->getvObstacle().size());
	TextOut(getMemDC(), 200, 70, str, strlen(str));

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			Rectangle(getMemDC(), map->getTile()[i * TILEX + j].rcTile.left,
				map->getTile()[i * TILEX + j].rcTile.top,
				map->getTile()[i * TILEX + j].rcTile.right,
				map->getTile()[i * TILEX + j].rcTile.bottom);
		}
	}


	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
	/*Rectangle(getMemDC(), testRc.left, testRc.top, testRc.right, testRc.bottom);*/
}

void CStage::enter()
{
	player = new CPlayer;
	map = new CMap("save/test.map");
	playerUI = new CPlayerUI;

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
	ITEM->respawnItem(ITEM_TYPE::ITEM_HEART, { 500,300 });
	ITEM->respawnItem(ITEM_TYPE::ITEM_COIN, { 600,300 });
}

void CStage::exit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(map);
}
