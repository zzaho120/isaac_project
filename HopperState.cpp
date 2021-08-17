#include "framework.h"
#include "HopperState.h"
#include "BulletManager.h"
#include "enemyManager.h"
#include "CPlayer.h"
#include "CStage.h"
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
	objective = new CCollider;
	CCharacter* pMon = m_pFSM->GetMon();
	count = 0;
	movetime = 32;

	delay = 50;

	jumpstart = 1;
	downstart = 1;
	idlestart = 1;
	idle = 0;

	parabola = 0;
	shadow = pMon->getRC();
	
	foward = RND->getFromIntTo(0, 7);
	distance = RND->getFromIntTo(50, 100);
	
	//RECT objectiveRc = RectMakeCenter(
	//	RectX(shadow) + cosf(PI - foward * PI_4) * distance,
	//	RectY(shadow) - sinf(PI - foward * PI_4) * distance,
	//	RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
	//vector2 objectPrevPt;
	//vector2 objectivePt;
	//objectivePt.x = RectX(objectiveRc);
	//objectivePt.y = RectY(objectiveRc);
	//objective->setPos(objectivePt);
	//objective->setSize({ 30,30 });

	//bool wall = COLLISION->wallCollision(objectivePt, { MAPCOLLISIONSTARTX ,MAPCOLLISIONSTARTY }, MAPCOLLISIONX, MAPCOLLISIONX);
	//bool unable = COLLISION->tileCollision(STAGE->getCurStage()->getCurRoom(), objectivePt, objectPrevPt, 1, 0);
	//int hereIndex = (objectiveRc.left / TILEWIDTH - 1) + (objectiveRc.top / TILEHEIGHT - 1) * TILEX;

	//if (wall) { foward, distance = 0; }//continue;
	//if (hereIndex < 130 && hereIndex > 0)
	//{
	//	if (unable) { foward, distance = 0; }
	//}

}

void Hopper_Idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	Jump();
	
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (Inrange(300, ENEMY->GetPlayer()->getPt()) && idle)
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
	
}



void Hopper_Idle::Exit()
{
	SAFE_DELETE(objective);
}
void Hopper_Idle::Jump()
{
	CObject* pMon = m_pFSM->GetMon();

	if (count > delay)
	{
		count = 0;
		parabola = 0.0f;
		shadow = pMon->getRC();
		foward = RND->getFromIntTo(0, 7);
		distance = RND->getFromIntTo(50, 100);
		
		//RECT objectiveRc = RectMakeCenter(
		//	RectX(shadow) + cosf(PI - foward * PI_4) * distance,
		//	RectY(shadow) - sinf(PI - foward * PI_4) * distance,
		//	RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		//vector2 objectPrevPt;
		//vector2 objectivePt;
		//objectivePt.x = RectX(objectiveRc);
		//objectivePt.y = RectY(objectiveRc);
		//objective->setPos(objectivePt);
		//objective->setSize({ 30,30 });

		//bool wall = COLLISION->wallCollision(objectivePt, { MAPCOLLISIONSTARTX ,MAPCOLLISIONSTARTY }, MAPCOLLISIONX, MAPCOLLISIONX);
		//bool unable = COLLISION->tileCollision(STAGE->getCurStage()->getCurRoom(), objectivePt, objectPrevPt, 1, 0);
		//int hereIndex = (objectiveRc.left / TILEWIDTH - 1) + (objectiveRc.top / TILEHEIGHT - 1) * TILEX;

		//if (wall) { foward, distance = 0; }//continue;
		//if (hereIndex < 130 && hereIndex > 0)
		//{
		//	if (unable) { foward, distance = 0; }
		//}
		jumpstart = 1;
		downstart = 1;
		idlestart = 1;
		
	}
	RECT rec = pMon->getRC();
	if (count <= movetime && count % 2 == 0)
	{
		shadow = RectMakeCenter(
			RectX(shadow) + cosf(PI - foward * PI_4) * distance / 16,
			RectY(shadow) - sinf(PI - foward * PI_4) * distance / 16,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		rec = RectMakeCenter(
			RectX(shadow),
			RectY(shadow) - sinf(parabola) * 50 + 10,
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
	objective = new CCollider;
	CObject* pMon = m_pFSM->GetMon();
	shadow = pMon->getRC();
}

void Hopper_Trace::update()
{
	
	CCharacter* pMon = m_pFSM->GetMon();
	if (count == 0)
	{
		angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);
		distance = UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);
	}
	/*RECT objectiveRc = RectMakeCenter(
		RectX(shadow) + cosf(angle) * distance,
		RectY(shadow) - sinf(angle) * distance,
		RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
	vector2 objectPrevPt;
	vector2 objectivePt;
	objectivePt.x = RectX(objectiveRc);
	objectivePt.y = RectY(objectiveRc);
	objective->setPos(objectivePt);
	objective->setSize({ 30,30 });
	if ( COLLISION->wallCollision(objectivePt, { MAPCOLLISIONSTARTX ,MAPCOLLISIONSTARTY }, MAPCOLLISIONX, MAPCOLLISIONX))
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}*/

	Jump();

	
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (idle)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}



void Hopper_Trace::Exit()
{
	SAFE_DELETE(objective);
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
			RectY(shadow) - sinf(parabola) * 50 + 10,
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

Hopper_Atk::Hopper_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Hopper_Atk::~Hopper_Atk()
{
}

void Hopper_Atk::Enter()
{
}

void Hopper_Atk::update()
{
}

void Hopper_Atk::Exit()
{
}

Hopper_Die::Hopper_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Hopper_Die::~Hopper_Die()
{
}

void Hopper_Die::Enter()
{
	m_pFSM->GetMon()->release();
}

void Hopper_Die::update()
{
}

void Hopper_Die::Exit()
{
}
