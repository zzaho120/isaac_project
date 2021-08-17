#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"
#include "CMinimap.h"
#include "UseItem.h"
#include "RandomMapGenerator.h"

void CStage::update()
{
	curRoom->update();
	player->update();
	curRoom->update();
	if (InputManager->isOnceKeyDown('N'))
	{
		player->setBulletSize(player->getBulletSize() + 1);
	}
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
	playerEnterDoor();

	COLLISION->stageCollision(player);
	COLLISION->isMonsterDie();
}

void CStage::render()
{
	curRoom->render();
	player->render();
}

void CStage::enter()
{
	doorCnt = 0;
	curRoomIdx = 0;
	player = new CPlayer;
	rnd = new RandomMapGenerator;

	rnd->mapGenerate();
	randomMapSetting();
	player->init();
	ALLUI->setPlayer(player);
	ALLUI->setrandomMap(rnd);

	ALLUI->getMinimap()->setRND(rnd);
	ALLUI->getMinimap()->mapAttrSetting();
	
	ENEMY->SetPlayer(player);
	player->setRoomLink(curRoom);

	ITEM->setPlayer(player);

	ENEMY->SetPlayer(player);
	player->setRoomLink(curRoom);

	(*curRoom->getviObstacle(40))->setObjType(OBJECT::OBJ_POOP);
	(*curRoom->getviObstacle(42))->setObjType(OBJECT::OBJ_ROCK);
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

	for (int roomNum = 0; roomNum < 100; roomNum++)
	{
		if (room[roomNum]->getRoomType() == ROOM::ROOM_NONE) continue;
		if (roomNum - 10 >= 0)
		{
			if (room[roomNum - 10]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::TOP);
			}
		}
		if (roomNum + 10 < 100)
		{
			if (room[roomNum + 10]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::BOTTOM);
			}

		}
		if (roomNum % 10 > 0)
		{
			
			if (room[roomNum - 1]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::LEFT);
			}
		}
		if (roomNum % 10 < 9)
		{
			if (room[roomNum + 1]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::RIGHT);
			}
		}
	}

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
				player->setBulletDistance(player->getBulletDistance() + 100);
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_PENTAGRAM:
				player->setBulletDamage(player->getBulletDamage() + 1);
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_BLOODBAG:
				player->setMaxHp(player->getMaxHp() + 2);
				player->sethp(player->gethp() + 10);
				player->cantHpOver();
				player->setSpeed(player->getSpeed() + 0.3);
				player->cantSpeedOver();
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_SPEEDBALL:
				player->setSpeed(player->getSpeed() + 0.3);
				player->cantSpeedOver();
				player->setBulletSpeed(player->getBulletSpeed() + 0.2);
				player->cantBulletSpeedOver();
				ITEM->itemRemove(i);
			default:
				break;
			}
			break;
		}
	}
}

void CStage::playerEnterDoor()
{
	DOOR_DIRECTION door_direction = COLLISION->doorCollision(curRoom, player);
	if(door_direction == DOOR_DIRECTION::TOP)
	{
		if (room[curRoomIdx - 10]->getRoomType() != ROOM::ROOM_NONE)
		{
			player->setPt(curRoom->getTile()[112].pt);
			changeRoom(curRoomIdx - 10);
		}
	}
	else if (door_direction == DOOR_DIRECTION::BOTTOM)
	{
		if (room[curRoomIdx + 10]->getRoomType() != ROOM::ROOM_NONE)
		{
			changeRoom(curRoomIdx + 10);
			player->setPt(curRoom->getTile()[22].pt);
		}
	}
	else if (door_direction == DOOR_DIRECTION::LEFT)
	{
		if (room[curRoomIdx - 1]->getRoomType() != ROOM::ROOM_NONE)
		{
			changeRoom(curRoomIdx - 1);
			player->setPt(curRoom->getTile()[73].pt);
		}
	}
	else if (door_direction == DOOR_DIRECTION::RIGHT)
	{
		if (room[curRoomIdx + 1]->getRoomType() != ROOM::ROOM_NONE)
		{
			changeRoom(curRoomIdx + 1);
			player->setPt(curRoom->getTile()[61].pt);
		}
	}
}
