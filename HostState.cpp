#include "framework.h"
#include "HostState.h"
#include "BulletManager.h"
#include "enemyManager.h"
#include "CPlayer.h"
//=============================================������=========================================================
Host_Idle::Host_Idle() //������
{
	m_eState = STATE_TYPE::IDLE;
}

Host_Idle::~Host_Idle()
{
}

void Host_Idle::Enter()
{
	CCharacter* pMon = m_pFSM->GetMon();
	pMon->setAni(ANIMATION->findAnimation("hostidle"));
	ANIMATION->start("hostidle");
}
void Host_Idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (inrange(300, ENEMY->GetPlayer()->getPt()) && crossrange(20, ENEMY->GetPlayer()->getPt()))
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}


void Host_Idle::Exit()
{
}

bool Host_Idle::inrange(int range, vector2 pt)
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}

bool Host_Idle::crossrange(int range, vector2 pt)
{
	CCharacter* pMon = m_pFSM->GetMon();

	bool horizontality = pt.y >= pMon->getPt().y - range && pt.y <= pMon->getPt().y + range;
	bool Perpendicular = pt.x >= pMon->getPt().x - range && pt.x <= pMon->getPt().x + range;
	if (horizontality || Perpendicular)
	{
		return true;
	}
	else return false;
}
//=============================================������=========================================================

//=============================================�÷��̾������=========================================================
Host_Trace::Host_Trace() // �÷��̾��
{
	m_eState = STATE_TYPE::TRACE;
}

Host_Trace::~Host_Trace()
{
}
void Host_Trace::Enter()
{
	CCharacter* pMon = m_pFSM->GetMon();
	pMon->setAni(ANIMATION->findAnimation("hosttrace"));
	ANIMATION->start("hosttrace");
	delay = 0;
}

void Host_Trace::update()
{
	delay++;
	CCharacter* pMon = m_pFSM->GetMon();
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (delay >30)
	{
		m_pFSM->ChangeState(STATE_TYPE::ATTACK);
	}
}


void Host_Trace::Exit()
{
}
//=============================================�÷��̾������=========================================================


//=============================================���ݻ���=========================================================

Host_Atk::Host_Atk() //���ݻ���
{
	m_eState = STATE_TYPE::ATTACK;
}


Host_Atk::~Host_Atk()
{
}

void Host_Atk::Enter()
{
	count = 0;
	delay = 70;

	angle = 0.0f;
	speed = 0.0f;
	fire = 0;
	shadowDistance = 0;
	distance = 0;

}
void Host_Atk::update()
{
	
	CCharacter* pMon = m_pFSM->GetMon();
	if (count == 0)
	{
		angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);
		speed = 5;
		fire = pMon->getPt();
		shadowDistance = 20;
		distance = 200;

		BULLET->fire(angle, speed, fire, shadowDistance, distance,1, CHARACTER::MONSTER, 15, "HostBullet");
	}
	count++;

	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (count > delay)
	{
		if (inrange(300, ENEMY->GetPlayer()->getPt()) && crossrange(20, ENEMY->GetPlayer()->getPt()))
		{

			m_pFSM->ChangeState(STATE_TYPE::TRACE);

		}
		else m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}



void Host_Atk::Exit()
{
}
bool Host_Atk::inrange(int range, vector2 pt)
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}

bool Host_Atk::crossrange(int range, vector2 pt)
{
	CCharacter* pMon = m_pFSM->GetMon();

	bool horizontality = pt.y >= pMon->getPt().y - range && pt.y <= pMon->getPt().y + range;
	bool Perpendicular = pt.x >= pMon->getPt().x - range && pt.x <= pMon->getPt().x + range;
	if (horizontality || Perpendicular)
	{
		return true;
	}
	else return false;

}

//=============================================���ݻ���=========================================================


//=============================================����=========================================================
Host_Die::Host_Die() //����
{
	m_eState = STATE_TYPE::DEAD;
}

Host_Die::~Host_Die()
{
}

void Host_Die::Enter()
{
}

void Host_Die::Exit()
{
}

void Host_Die::update()
{
}
//=============================================����=========================================================