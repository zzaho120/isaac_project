#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"
#include "CItem.h"
#include "RandomMapGenerator.h"

void CStage::update()
{
	player->update();
	if (InputManager->isOnceKeyDown('N'))
	{
		player->setBulletSize(player->getBulletSize() + 1);
	}

	// test
	if (RectX(testRc) < 0 && minimap->getMinimap()[curRoomIdx - 1].roomAttr != ROOM_TYPE_ATTR::NONEROOM)
	{
		changeRoom(curRoomIdx - 1);
		testRc = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}
	if (RectX(testRc) > WINSIZEX && minimap->getMinimap()[curRoomIdx + 1].roomAttr != ROOM_TYPE_ATTR::NONEROOM)
	{
		changeRoom(curRoomIdx + 1);
		testRc = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}

	if (RectY(testRc) < 0 && minimap->getMinimap()[curRoomIdx - 10].roomAttr != ROOM_TYPE_ATTR::NONEROOM)
	{
		changeRoom(curRoomIdx - 10);
		testRc = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}
	if (RectY(testRc) > WINSIZEY && minimap->getMinimap()[curRoomIdx + 10].roomAttr != ROOM_TYPE_ATTR::NONEROOM)
	{
		changeRoom(curRoomIdx + 10);
		testRc = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 100, 100);
	}

	if (InputManager->isStayKeyDown(VK_LEFT)) OffsetRect(&testRc, -5, 0);
	if (InputManager->isStayKeyDown(VK_RIGHT)) OffsetRect(&testRc, 5, 0);
	if (InputManager->isStayKeyDown(VK_UP)) OffsetRect(&testRc, 0, -5);
	if (InputManager->isStayKeyDown(VK_DOWN)) OffsetRect(&testRc, 0, 5);


	if (InputManager->isOnceKeyDown('M'))
	{
		player->setBulletDistance(player->getBulletDistance() + 10);
	}
	if (InputManager->isOnceKeyDown('B'))
	{
		player->setSpeed(player->getSpeed() + 1);
	}
	if (InputManager->isOnceKeyDown('V'))
	{
		player->setInnerEye(true);
	}
	playerGetItem();
	COLLISION->stageCollision(player);
	COLLISION->isMonsterDie();
}

void CStage::render()
{
	curRoom->render();
	player->render();
	minimap->render();
	playerUI->render(player);
	Rectangle(getMemDC(), testRc.left, testRc.top, testRc.right, testRc.bottom);
}

void CStage::enter()
{
	curRoomIdx = 0;
	player = new CPlayer;
	rnd = new RandomMapGenerator;

	rnd->mapGenerate();
	randomMapSetting();
	player->init();
	ALLUI->setPlayer(player);
	ALLUI->setrandomMap(rnd);

	minimap->setRND(rnd);
	minimap->mapAttrSetting();
	
	ENEMY->SetPlayer(player);
	player->setRoomLink(curRoom);

	testRc = RectMakeCenter({ WINSIZEX / 2, WINSIZEY / 2 }, 50, 50);

	ENEMY->SetPlayer(player);
	player->setRoomLink(curRoom);
	//ENEMY->setPlayerLink(player);
	ENEMY->respawnMinion(MONSTER_TYPE::HOPPER, { 500,500 });
	ENEMY->respawnMinion(MONSTER_TYPE::FLY, { 500,500 });
	ENEMY->respawnMinion(MONSTER_TYPE::WORM, { 400,500 });
	ENEMY->respawnMinion(MONSTER_TYPE::MULLIGAN, { 600,500 });
	ITEM->respawnItem(ITEM_TYPE::ITEM_HEART, { 500,300 });
	ITEM->respawnItem(ITEM_TYPE::ITEM_COIN, { 600,300 });
	ITEM->respawnItem(ITEM_TYPE::ITEM_BOMB, { 700,500 });
	ITEM->respawnItem(ITEM_TYPE::ITEM_KEY, { 300,500 });
	ITEM->respawnItem(ITEM_TYPE::ITEM_THEINNEREYE, { 200,500 });
	ITEM->respawnRandomBasicItem({ 300,400 });
}

void CStage::exit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(rnd);
	for(int i = 0; i < 100; i++)
		SAFE_DELETE(room[i]);
}

void CStage::randomMapSetting()
{
	for (int i = 0; i < 100; i++)
		room[i] = new CMap(*rnd->getRNDGenMap(i));
	changeRoom(45);
}

void CStage::changeRoom(int roomNum)
{
	ENEMY->eraserAllEnemy();

	curRoomIdx = roomNum;
	curRoom = room[curRoomIdx];
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		curRoom->setMonster(curRoom->getTile()[i].monster, curRoom->getTile()[i].pt);
	}
}

void CStage::playerGetItem()
{
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
			case ITEM_TYPE::ITEM_COIN:
				if (player->getCoin() >= 99) { break; }
				else
				{
					player->setCoin(player->getCoin() + 1);
					player->cantCoinOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_BOMB:
				if (player->getBomb() >= 99) { break; }
				else
				{
					player->setBomb(player->getBomb() + 1);
					player->cantBombOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_KEY:
				if (player->getKey() >= 99) { break; }
				else
				{
					player->setKey(player->getKey() + 1);
					player->cantKeyOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_THEINNEREYE:
				player->setInnerEye(true);
				ITEM->itemRemove(i);
				ITEM->respawnItem(ITEM_TYPE::ITEM_COIN, { 250, 300 });
				break;
			case ITEM_TYPE::ITEM_MOMSLIPSTICK:
				if (player->getKey() >= 99) { break; }
				else
				{
					player->setKey(player->getKey() + 1);
					player->cantKeyOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_PENTAGRAM:
				if (player->getKey() >= 99) { break; }
				else
				{
					player->setKey(player->getKey() + 1);
					player->cantKeyOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_BLOODBAG:
				if (player->getKey() >= 99) { break; }
				else
				{
					player->setKey(player->getKey() + 1);
					player->cantKeyOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_SPEEDBALL:
				if (player->getKey() >= 99) { break; }
				else
				{
					player->setKey(player->getKey() + 1);
					player->cantKeyOver();
					ITEM->itemRemove(i);
					break;
				}
			default:
				break;
			}
			break;
		}
	}
}
