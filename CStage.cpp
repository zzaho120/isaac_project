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
	curRoom->render();
	player->render();
	minimap->render();

	playerUI->render(player);

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
	playerUI = new CPlayerUI;

	rnd->mapGenerate();
	randomMapSetting();
	player->init();

	minimap->setRND(rnd);
	minimap->mapAttrSetting();
	/*tagTile* tile = ->getTile();
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		map->setMonster(tile[i].monster, tile[i].pt);
	}*/

	ENEMY->SetPlayer(player);
	player->setRoomLink(curRoom);
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
