#include "framework.h"
#include "TestMonsterScene.h"
#include "CBullet.h"
#include "CMonster.h"
#include "CFSM.h"
#include "CItem.h"
HRESULT TestMonsterScene::init()
{
    _map = new CMap;

    _map->init();

    tagTile* tile = _map->getTile();
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        setMonster(tile[i].monster, tile[i].pt);
    }
    return S_OK;
}

HRESULT TestMonsterScene::init(const char* fileName)
{
    _map = new CMap;

    _map->init(fileName);
    tagTile* tile = _map->getTile();
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (tile[i].monster == MONSTER_TYPE::NONE) continue;
        setMonster(tile[i].monster, tile[i].pt);
    }

    return S_OK;
    EFFECT->addEffect("pbullet", "images/bullets.bmp", 256, 128, 28, 32, 1, 0.5f, 200);
}

void TestMonsterScene::release()
{
    ENEMY->release();
}

void TestMonsterScene::update()
{
}

void TestMonsterScene::render()
{
    _map->render();
}

void TestMonsterScene::setMonster(MONSTER_TYPE type, vector2 pt)
{
    ENEMY->respawnMinion(type, pt);
}
