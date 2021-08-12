#pragma once
#include"gameNode.h"
#include"CMap.h"
#include"CPlayer.h"

class CBullet;
class CMonster;
class TestMonsterScene : public gameNode
{
private:
	int count;
	CMap* _map;
	CPlayer* _player;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setMonster(MONSTER_TYPE type, vector2 pt);
	CPlayer* getplayer() { return _player; }
};