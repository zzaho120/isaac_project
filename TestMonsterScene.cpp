#include "framework.h"
#include "TestMonsterScene.h"

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
    ENEMY->respawnMinion(MONSTER_TYPE::HOPPER, { 500,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::HOST, { 400,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::WORM, { 300,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::FLY, { 600,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::MULLIGAN, { 700,500 });
    //ENEMY->respawnMinion(MONSTER_TYPE::GURDY, { 500,300 });
    return S_OK;
}

void TestMonsterScene::release()
{
    SAFE_DELETE(_player);
}

void TestMonsterScene::update()
{
    _player->update();
    
    if(COLLISION->isCollision(_player->getcollider(), ENEMY->getmoncollider(0)))
    {
        ENEMY->eraserEnemy(0);
    }
}

void TestMonsterScene::render()
{
    _map->render();
    _player->render();
}

void TestMonsterScene::setMonster(MONSTER_TYPE type, vector2 pt)
{
  /*  switch (type)
    {
    case MINION::MINION_WORM:
        _enemy->respawnMinion(new CWORM, pt.x, pt.y);
        break;
    case MINION::MINION_FLY:
        _enemy->respawnMinion(new CFly, pt.x, pt.y);
        break;
    case MINION::MINION_HOST:
        _enemy->respawnMinion(new CHost, pt.x, pt.y);
        break;
    case MINION::MINION_HOPPER:
        _enemy->respawnMinion(new CHopper, pt.x, pt.y);
        break;
    case MINION::MINION_MULLIGAN:
        _enemy->respawnMinion(new CMulligan, pt.x, pt.y);
        break;
    case MINION::MINION_NONE:
        break;
    }*/
}
