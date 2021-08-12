#pragma once
#include "CCharacter.h"

class CMonster : public CCharacter
{
protected:
<<<<<<< Updated upstream
	CFSM* m_pAI;
=======

>>>>>>> Stashed changes
	MONSTER_TYPE monsterType;
	vector<CFSM*> vAI;
private:
	
public:
	CMonster();

	virtual HRESULT init(float x , float y ) = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	void setMonster_Type(MONSTER_TYPE number) { monsterType = number; }
	MONSTER_TYPE getMonster_Type() { return monsterType; }
};