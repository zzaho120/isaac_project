#include "framework.h"
#include "TestMonsterScene.h"
#include "CBullet.h"
#include "CMonster.h"
#include "CFSM.h"
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
    ENEMY->respawnMinion(MONSTER_TYPE::HOST, {400,500});
    ENEMY->respawnMinion(MONSTER_TYPE::WORM, { 300,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::FLY, { 600,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::MULLIGAN, { 700,500 });
    ENEMY->respawnMinion(MONSTER_TYPE::SMALLFLY, { 700,500 });*/
    //ENEMY->respawnMinion(MONSTER_TYPE::GURDY, { 500,300 });
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
    EFFECT->addEffect("pbullet", "images/bullets.bmp", 256, 128, 28, 32, 1, 0.5f, 200);
}

void TestMonsterScene::release()
{
   // SAFE_DELETE(_player);
}

void TestMonsterScene::update()
{
    _player->update();
    bool playerIdle = _player->getstate() == STATE_TYPE::IDLE;
    ENEMY->SetPlayer(_player);
    for (int i = 0; i < ENEMY->getvmonster().size(); i++)
    {
        bool ispcm = COLLISION->isCollision(_player->getcollider(), (*ENEMY->getvimonster(i))->getcollider());
        bool ispsm = COLLISION->isCollision(_player->GetcolliderShadow(), (*ENEMY->getvimonster(i))->GetcolliderShadow());
        if(ispcm && playerIdle && ispsm)
        {
            //ENEMY->eraserEnemy(i);
            _player->sethp(_player->gethp() - 1);
            _player->getAI()->ChangeState(STATE_TYPE::ATTACK);
            break;
        }
    }
    for (int i = 0; i < ENEMY->getvmonster().size(); i++)
    {
        for (int j = 0; j < BULLET->getvBullet().size(); j++)
        {
            bool ispbcm = COLLISION->isCollision((*BULLET->getviBullet(j))->getcollider(), (*ENEMY->getvimonster(i))->getcollider());
            bool ispbrm = COLLISION->isCollision((*BULLET->getviBullet(j))->GetcolliderShadow(), (*ENEMY->getvimonster(i))->GetcolliderShadow());
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
        bool ismbsp = COLLISION->isCollision((*BULLET->getviBullet(i))->GetcolliderShadow(), _player->GetcolliderShadow());
        bool ismB = (*BULLET->getviBullet(i))->gettype() == CHARACTER::MONSTER;
        if (ismbcp && ismbsp && ismB && playerIdle)
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
    ENEMY->respawnMinion(type, pt);
}
