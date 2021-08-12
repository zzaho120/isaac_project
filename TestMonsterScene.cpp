#include "framework.h"
#include "TestMonsterScene.h"
#include "CGurdy.h"

HRESULT TestMonsterScene::init()
{
    _player = new CPlayer;
    _map = new CMap;

    _map->init();
    _player->init();

    tagTile* tile = _map->getMap();
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        setMonster(tile[i].monster, tile[i].pt);
    }
    /*ENEMY->respawnMinion(MONSTER_TYPE::HOPPER, { 500,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::HOST, { 400,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::WORM, { 300,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::FLY, { 600,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::MULLIGAN, { 700,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::GURDY, { 500,300 });*/
    return S_OK;
}

HRESULT TestMonsterScene::init(const char* fileName)
{
    _map->init(fileName);
    _player->init();

    tagTile* tile = _map->getMap();
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        setMonster(tile[i].monster, tile[i].pt);
    }
    return S_OK;
}

void TestMonsterScene::release()
{
   // SAFE_DELETE(_player);
}

void TestMonsterScene::update()
{
    _player->update();
}

void TestMonsterScene::render()
{
    _map->render();
    _player->render();
}

void TestMonsterScene::setMonster(MONSTER_TYPE type, vector2 pt)
{
    ENEMY->respawnMinion(type, pt);
    /*switch (type)
    {
    case MONSTER_TYPE::WORM:
        ENEMY->respawnMinion(new CWORM, pt.x, pt.y);
        break;
    case MONSTER_TYPE::FLY:
        ENEMY->respawnMinion(new CFly, pt.x, pt.y);
        break;
    case MONSTER_TYPE::HOST:
        ENEMY->respawnMinion(new CHost, pt.x, pt.y);
        break;
    case MONSTER_TYPE::HOPPER:
        ENEMY->respawnMinion(new CHopper, pt.x, pt.y);
        break;
    case MONSTER_TYPE::MULLIGAN:
        ENEMY->respawnMinion(new CMulligan, pt.x, pt.y);
        break;
    case MONSTER_TYPE::NONE:
        break;
    }*/
}
