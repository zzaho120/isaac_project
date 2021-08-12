#include "framework.h"
#include "PooterState.h"
#include "BulletManager.h"
#include "enemyManager.h"
//=============================================대기상태=========================================================
Fly_Idle::Fly_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Fly_Idle::~Fly_Idle()
{
}

void Fly_Idle::Enter()
{
	count = 0;
	movetime = 32;
	delay = 35;
	atkcount = 0;

	idle = 0;

	foward = RND->getFromIntTo(0, 7);
	distance = 0.0f;
	parabola = 0.0f;
	angle = 0.0f;
}
void Fly_Idle::update()
{
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;
	atkcount++;
	Move();
	if (inrange(200, _pt))
	{
		m_pFSM->ChangeState(STATE_TYPE::ATTACK);
	}
}



void Fly_Idle::Exit()
{
}
void Fly_Idle::Move()
{
	CObject* pMon = m_pFSM->GetMon();

	if (count > delay)
	{
		count = 0;
		parabola = 0.0f;
		foward = RND->getFromIntTo(0, 7);
		distance = RND->getFromIntTo(0, 2);
	}
	RECT rec = pMon->getRC();

	if (count <= movetime && count % 2 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) + cosf(PI - foward * PI_4) * (distance - parabola),
			RectY(rec) - sinf(PI - foward * PI_4) * (distance - parabola),
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		parabola += PI_16;
	}

	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	count++;
}

bool Fly_Idle::inrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}
//=============================================대기상태=========================================================



//=============================================감지상태=========================================================
void Fly_Trace::Enter()
{
}

void Fly_Trace::update()
{
}


void Fly_Trace::Exit()
{
}
//=============================================대기상태=========================================================


//=============================================공격상태=========================================================
Fly_Atk::Fly_Atk()
{
	m_eState = STATE_TYPE::ATTACK;

}

Fly_Atk::~Fly_Atk()
{
}

void Fly_Atk::Enter()
{
	count = 0;
	delay = 70;

	angle = 0.0f;
	speed = 0.0f;
	fire = 0;
	shadowDistance = 0;
	distance = 0;
}

void Fly_Atk::update()
{
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;

	CCharacter* pMon = m_pFSM->GetMon();
	if (count == 0)
	{
		angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, _pt.x, _pt.y);
		speed = 5;
		fire = pMon->getPt();
		shadowDistance = 20;
		distance = 200;

		BULLET->fire(angle, speed, fire, shadowDistance, 30, CHARACTER::MONSTER, 10);
		if (isleft(_pt.x))
		{
			pMon->setAni(ANIMATION->findAnimation("leftAtkfly"));
			ANIMATION->start("leftAtkfly");
		}
		else
		{
			pMon->setAni(ANIMATION->findAnimation("rightAtkfly"));
			ANIMATION->start("rightAtkfly");
		}
	}
	if (count == 65)
	{
		if (isleft(_pt.x))
		{
			pMon->setAni(ANIMATION->findAnimation("leftfly"));
			ANIMATION->start("leftfly");
		}
		else
		{
			pMon->setAni(ANIMATION->findAnimation("rightfly"));
			ANIMATION->start("rightfly");
		}
	}

	count++;

	if (count > delay)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}

void Fly_Atk::Exit()
{
}

bool Fly_Atk::isleft(float x)
{
	CObject* pMon = m_pFSM->GetMon();
	if (x - pMon->getPt().x <= 0)
	{
		return true;
	}
	else return false;
}

//=============================================공격상태=========================================================