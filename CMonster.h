#pragma once
#include "CCharacter.h"
class CFSM;
class CMonster : public CCharacter
{
protected:
	CFSM* m_pAI;
	vector<CFSM*> vAI;

	MONSTER_TYPE monsterType;
private:
	
public:
	CMonster();

	virtual HRESULT init(float x , float y ) = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	CFSM* getAI() { return m_pAI; }
	void AI_init(CCharacter* monster);
	void AI_update();

	void setMonster_Type(MONSTER_TYPE number) { monsterType = number; }
	MONSTER_TYPE getMonster_Type() { return monsterType; }
};