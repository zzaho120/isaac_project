#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"

HRESULT CStage::init()
{
	map = new CMap("test.map");
	player = new CPlayer;

	player->setRoomLink(map);
	//ENEMY->setPlayerLink(player);
	return S_OK;
}

void CStage::release()
{
}

void CStage::update()
{
}

void CStage::render()
{
}
