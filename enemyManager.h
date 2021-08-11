#pragma once
//#include"CHopper.h"
//#include"CFly.h"
//#include"CHost.h"
//#include"CWORM.h"
//#include"CMulligan.h"
//#include"CGurdy.h"

#include"singleton.h"
class CMonster;

class CHopper;
class CFly;
class CHost;
class CWORM;
class CMulligan;
class CGurdy;
class Csmallfly;

struct summon
{
	MONSTER_TYPE m_Mtype;
	Vec2 p_pos;
	bool isrespawn;
};

class enemyManager : public Singleton<enemyManager>
{
private:
	typedef vector<CMonster*> vminion;
	typedef vector<CMonster*>::iterator viminion;

	vector<summon> vsummon;
	vector<summon>::iterator visummon;

private:
	vminion _vminion;
	viminion _viminion;
protected:
	

	bool summonFly;
public:
	enemyManager();
	~enemyManager();
	

	HRESULT init();
	void release();
	void update();
	void render();

	void respawnMinion(MONSTER_TYPE type, Vec2 pos);
	void respawn(MONSTER_TYPE type, Vec2 pos);
	void respawnupdate();
	void summonFlytest(bool test) { summonFly = test; }
	void eraserEnemy(int number) { _vminion.erase(_vminion.begin() + number); }
};

