#include "framework.h"
#include "SmallflyState.h"



Smallfly_Idle::Smallfly_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Smallfly_Idle::~Smallfly_Idle()
{
}

void Smallfly_Idle::Enter()
{
	count = 0;
	movetime = 32;
	delay = 35;
	atkcount = 0;

	idle = 0;

	foward = RND->getFromIntTo(0, 7);
	distance = 0.0f;
	angle = 0.0f;
}

void Smallfly_Idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;

	Move();

	if (Inrange(300, _pt))
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}

void Smallfly_Idle::Exit()
{
}

void Smallfly_Idle::Move()
{
	CObject* pMon = m_pFSM->GetMon();
	RECT rec = pMon->getRC();

	/*if (count % 3 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) - cosf(-parabola) * 10,
			RectY(rec) + sinf(-parabola) * 10,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		parabola += PI_16;
	}*/

	/*if (count > delay)
	{
		count = 0;
		parabola = 0.0f;
		foward = RND->getFromIntTo(0, 7);
		distance = RND->getFromIntTo(0, 2);
	}
	if (count <= movetime && count % 2 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) + cosf(PI - foward * PI_4) * (distance - parabola),
			RectY(rec) - sinf(PI - foward * PI_4) * (distance - parabola),
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		parabola += PI_16;
	}*/

	if (count > delay)
	{
		count = 0;
		foward = RND->getFromIntTo(0, 7);
		distance = RND->getFromIntTo(0, 3);
	}
	if (count <= movetime && count % 2 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) + cosf(PI - foward * PI_4) * (distance ),
			RectY(rec) - sinf(PI - foward * PI_4) * (distance ),
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
	}

	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	count++;
}

bool Smallfly_Idle::Inrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) <= range)
	{
		return true;
	}
	else return false;
}


Smallfly_Trace::Smallfly_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Smallfly_Trace::~Smallfly_Trace()
{
}

void Smallfly_Trace::Enter()
{
	count = 0;
	CObject* pMon = m_pFSM->GetMon();
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;

	angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, _pt.x, _pt.y);
}

void Smallfly_Trace::update()
{
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;

	MovetoPlayer();
	
	if (!Inrange(300, _pt) || count >=100)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}


void Smallfly_Trace::Exit()
{
}

void Smallfly_Trace::MovetoPlayer()
{
	CObject* pMon = m_pFSM->GetMon();

	RECT rec = pMon->getRC();

	if (count % 2 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) + cosf(angle) * 6,
			RectY(rec) - sinf(angle) * 6,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
	}

	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	count++;
}

bool Smallfly_Trace::Inrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) <= range)
	{
		return true;
	}
	else return false;
}


Smallfly_Atk::Smallfly_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Smallfly_Atk::~Smallfly_Atk()
{
}

void Smallfly_Atk::update()
{
}

void Smallfly_Atk::Enter()
{
}

void Smallfly_Atk::Exit()
{
}

Smallfly_Die::Smallfly_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Smallfly_Die::~Smallfly_Die()
{
}

void Smallfly_Die::update()
{
}

void Smallfly_Die::Enter()
{
}

void Smallfly_Die::Exit()
{
}
