#include "framework.h"
#include "HopperState.h"
#include "BulletManager.h"
#include "enemyManager.h"
//=============================================대기상태=========================================================
Hopper_Idle::Hopper_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Hopper_Idle::~Hopper_Idle()
{
}

void Hopper_Idle::Enter()
{
	count = 0;
	movetime = 32;

	delay = 50;

	jumpstart = 1;
	downstart = 1;
	idlestart = 1;
	idle = 0;

	parabola = 0;
	foward = RND->getFromIntTo(0, 7);
	distance = RND->getFromIntTo(2, 6);

	CObject* pMon = m_pFSM->GetMon();
	shadow = pMon->getRC();
}

void Hopper_Idle::update()
{
	Jump();
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;

	if (Inrange(300, _pt) && idle)
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}



void Hopper_Idle::Exit()
{
}
void Hopper_Idle::Jump()
{
	CObject* pMon = m_pFSM->GetMon();

	if (count > delay)
	{
		count = 0;
		parabola = 0.0f;
		foward = RND->getFromIntTo(0, 7);
		distance = RND->getFromIntTo(2, 6);
		jumpstart = 1;
		downstart = 1;
		idlestart = 1;
		
	}
		RECT rec = pMon->getRC();
	if (count <= movetime && count % 2 == 0)
	{

		shadow = RectMakeCenter(
			RectX(shadow) + cosf(PI - foward * PI_4) * distance,
			RectY(shadow) - sinf(PI - foward * PI_4) * distance,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		rec = RectMakeCenter(
			RectX(shadow),
			RectY(shadow) - sinf(parabola) * 50 + 5,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		parabola += PI_16;
	}
	if (count <= movetime / 2)
	{
		pMon->setAni(ANIMATION->findAnimation("jumphopper"));
		if (jumpstart)
		{
			ANIMATION->start("jumphopper");
			jumpstart = 0;
		}
	}
	else if (count <= movetime)
	{
		pMon->setAni(ANIMATION->findAnimation("downhopper"));
		if (downstart)
		{
			ANIMATION->start("downhopper");
			downstart = 0;
		}
	}
	else
	{
		pMon->setAni(ANIMATION->findAnimation("idlehopper"));
		if (idlestart)
		{
			ANIMATION->start("idlehopper");
			idlestart = 0;
		}
	}
	if (count > 40)
	{
		idle = true;
	}
	else idle = false;

	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	//Vec2 p_shadow;
	//p_shadow.x = RectX(shadow);
	//p_shadow.y = RectY(shadow);
	//pMon->setshadowpt(p_shadow);

	float shadowdistance;
	
	shadowdistance = RectY(shadow) - RectY(rec) + IMAGE->findImage("hopper")->getFrameHeight() / 2 -3;
	pMon->setshadowdistance(shadowdistance);
	count++;
}

bool Hopper_Idle::Inrange(int range, vector2 pt)
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
Hopper_Trace::Hopper_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Hopper_Trace::~Hopper_Trace()
{
}

void Hopper_Trace::Enter()
{
	count = 0;
	movetime = 32;
	delay = 50;

	jumpstart = 1;
	downstart = 1;
	idlestart = 1;
	idle = 0;

	parabola = 0;
	angle = 0.0f;
	distance = 0.0f;

	CObject* pMon = m_pFSM->GetMon();
	shadow = pMon->getRC();
}

void Hopper_Trace::update()
{
	CObject* pMon = m_pFSM->GetMon();
	vector2 _pt;
	_pt.x = m_ptMouse.x;
	_pt.y = m_ptMouse.y;
	if (count == 0)
	{
		angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, _pt.x, _pt.y);
		distance = UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, _pt.x, _pt.y);
	}
	Jump();

	if (idle)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}



void Hopper_Trace::Exit()
{
}
void Hopper_Trace::Jump()
{
	CObject* pMon = m_pFSM->GetMon();

	if (count > delay)
	{
		count = 0;
		idle = true;
		parabola = 0;

	}
	RECT rec = pMon->getRC();

	if (count <= movetime && count % 2 == 0)
	{
		shadow = RectMakeCenter(
			RectX(shadow) + cosf(angle) * distance / 16,
			RectY(shadow) - sinf(angle) * distance / 16,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		rec = RectMakeCenter(
			RectX(shadow),
			RectY(shadow) - sinf(parabola) * 50 + 5,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		parabola += PI_16;
	}
	if (count <= movetime / 2)
	{
		pMon->setAni(ANIMATION->findAnimation("jumphopper"));
		if (jumpstart)
		{
			ANIMATION->start("jumphopper");
			jumpstart = 0;
		}
	}
	else if (count <= movetime)
	{
		pMon->setAni(ANIMATION->findAnimation("downhopper"));
		if (downstart)
		{
			ANIMATION->start("downhopper");
			downstart = 0;
		}
	}
	else
	{
		pMon->setAni(ANIMATION->findAnimation("idlehopper"));
		if (idlestart)
		{
			ANIMATION->start("idlehopper");
			idlestart = 0;
		}
	}
	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	float shadowdistance;

	shadowdistance = RectY(shadow) - RectY(rec) + IMAGE->findImage("hopper")->getFrameHeight() / 2;
	pMon->setshadowdistance(shadowdistance);
	count++;
}
//=============================================감지상태=========================================================