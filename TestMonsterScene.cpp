#include "framework.h"
#include "TestMonsterScene.h"
#include "CBullet.h"
#include "CMonster.h"
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
    bool playerIdle = _player->getstate() == STATE_TYPE::IDLE;
    for (int i = 0; i < ENEMY->getvmonster().size(); i++)
    {
        bool ispcm = COLLISION->isCollision(_player->getcollider(), (*ENEMY->getvimonster(i))->getcollider());
        bool isprm = COLLISION->isCollision(_player->getRC(), (*ENEMY->getvimonster(i))->getRC());
        if(ispcm && playerIdle && isprm)
        {
            ENEMY->eraserEnemy(i);
            _player->sethp(_player->gethp() - 1);
            break;
        }
    }
    for (int i = 0; i < ENEMY->getvmonster().size(); i++)
    {
        for (int j = 0; j < BULLET->getvBullet().size(); j++)
        {
            bool ispbcm = COLLISION->isCollision((*BULLET->getviBullet(j))->getcollider(), (*ENEMY->getvimonster(i))->getcollider());//�÷��̾� �ҷ��� ���� �ݶ��̴��� �浹
            bool ispbrm = COLLISION->isCollision((*BULLET->getviBullet(j))->getRC(), (*ENEMY->getvimonster(i))->getRC());//�÷��̾� �ҷ��� ���� �ݶ��̴��� �浹
            bool ispB = (*BULLET->getviBullet(j))->gettype() == CHARACTER::PLAYER;
            if(ispbcm && ispbrm && ispB) 
            { 
                ENEMY->eraserEnemy(i);
                BULLET->eraserBullet(j);
                break;
            }
        }
    }
    for (int i = 0; i < BULLET->getvBullet().size(); i++)
    {
        bool ismbcp = COLLISION->isCollision((*BULLET->getviBullet(i))->getcollider(), _player->getcollider());
        bool ismbrp = COLLISION->isCollision((*BULLET->getviBullet(i))->getRC(), _player->getRC());
        bool ismB = (*BULLET->getviBullet(i))->gettype() == CHARACTER::MONSTER;
        if (ismbcp && ismbrp && ismB && playerIdle)
        {
            BULLET->eraserBullet(i);
            _player->sethp(_player->gethp() - 1);
            break;
        }
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
