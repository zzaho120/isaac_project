#include "framework.h"
#include "CMonster.h"
#include"CFSM.h"
// #include"StateList.h"

#include"PooterState.h"
#include"HopperState.h"
#include"HostState.h"
#include"WormState.h"
#include"MulliganState.h"
#include"GurdyState.h"
#include"SmallflyState.h"

CMonster::CMonster()
{
	m_pAI = nullptr;
}

void CMonster::AI_init(CCharacter* monster)
{
	m_pAI = new CFSM(monster);
	switch (getMonster_Type())
	{
	case MONSTER_TYPE::FLY:
		m_pAI->AddState(new Fly_Idle);
		m_pAI->AddState(new Fly_Trace);
		m_pAI->AddState(new Fly_Atk);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::HOPPER:

		m_pAI->AddState(new Hopper_Idle);
		m_pAI->AddState(new Hopper_Trace);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::HOST:

		m_pAI->AddState(new Host_Idle);
		m_pAI->AddState(new Host_Trace);
		m_pAI->AddState(new Host_Atk);
		m_pAI->AddState(new Host_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::MULLIGAN:

		m_pAI->AddState(new Mulligan_Idle);
		m_pAI->AddState(new Mulligan_Trace);
		m_pAI->AddState(new Mulligan_Atk);
		m_pAI->AddState(new Mulligan_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::WORM:
		m_pAI->AddState(new Worm_idle);
		m_pAI->AddState(new Worm_trace);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::GURDY:
		m_pAI->AddState(new Gurdy_Idle);
		m_pAI->AddState(new Gurdy_Trace);
		m_pAI->AddState(new Gurdy_Atk);
		m_pAI->AddState(new Gurdy_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
	case MONSTER_TYPE::SMALLFLY:
		m_pAI->AddState(new Smallfly_Idle);
		m_pAI->AddState(new Smallfly_Trace);
		m_pAI->AddState(new Smallfly_Atk);
		m_pAI->AddState(new Smallfly_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
	default:
		break;
	}
}

void CMonster::AI_update()
{
	m_pAI->update();
}


