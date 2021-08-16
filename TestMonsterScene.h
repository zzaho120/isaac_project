#pragma once
#include"gameNode.h"
#include"CMap.h"
#include"CPlayer.h"

class CFSM;
class CBullet;
class CMonster;
class TestMonsterScene : public gameNode
{
private:
	int count;
	CMap* _map;
public:
	HRESULT init();
	HRESULT init(const char* fileName);
	void release();
	void update();
	void render();

	void setMonster(MONSTER_TYPE type, vector2 pt);
};