#include "framework.h"
#include "CPlayer.h"
#include "CFSM.h"
#include "PlayerState.h"
#include "CState.h"
#include "CStage.h"
#include "CMap.h"
CPlayer::CPlayer() :
	CCharacter(), isMove(false), totalTears(0)
{
	setAni(ANIMATION->findAnimation("down_head"));
}

CPlayer::CPlayer(Vec2 _pos, RECT _rc, int _hp) :
	CCharacter(_pos, _rc, _hp), isMove(false), totalTears(0)
{ 
	setAni(ANIMATION->findAnimation("down_head"));
}

CPlayer::~CPlayer()
{ }

HRESULT CPlayer::init()
{
	CCharacter::init({ WINSIZEX / 2, WINSIZEY / 2 }, // make pos
		RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, PLAYERWIDTH, PLAYERHEIGHT), //rc
		{ WINSIZEX / 2, WINSIZEY / 2 }, { PLAYERWIDTH,PLAYERWIDTH }, //collider
		IMAGE->findImage("isaac")->getFrameHeight()/2,	//collider -> shadow distance
		{ WINSIZEX / 2, WINSIZEY / 2 + shadowdistance }, { PLAYERWIDTH,PLAYERWIDTH / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowPlayer", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setAni(ANIMATION->findAnimation("playeridlehead"));
	ani_body = ANIMATION->findAnimation("playeridlebody");
	animation anitemp = *ANIMATION->findAnimation("playeridlebody");
	anitemp.start();
	ANIMATION->start("playeridlebody");
	ANIMATION->start("playeridlehead");
	isMove = false;
	totalTears = 0;

	//player item and hp
	maxHp = 10;
	hp = 9;

	//player speed
	PLAYERMAXSPEED = 4;
	playerspeed = 0;

	//bullet information
	bulletsize = 15; 
	distance = 100;
	height = 30;

	//player information
	coin = 10;
	bomb = 3;
	key = 0;

	AI_init(this,MONSTER_TYPE::NONE);
	return S_OK;
}

void CPlayer::release()
{
}

void CPlayer::update()
{
	if (getstate() == STATE_TYPE::IDLE || getstate() == STATE_TYPE::ATTACK)
	{
		Move();
		fire();
	}
	
	pt = COLLISION->tileCollision(STAGE->getCurStage()->getCurRoom(), pt, prevPt, playerfoward, 0);
	pt = COLLISION->wallCollision(pt, { MAPSTARTX+ TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX- TILEWIDTH*2, TILESIZEY - TILEHEIGHT*2);
	prevPt = pt;

	colliderShadow->setPos(pt);
	collider->setPos({ pt.x, pt.y -shadowdistance });
	rc = RectMakeCenter(collider->getPos(), PLAYERWIDTH, PLAYERHEIGHT);
	//colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	//collider->setPos({ RectX(rc), RectY(rc) });

	AI_update();
}

void CPlayer::render()
{
	Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
		collider->getPos().y - collider->getSize().y / 2,
		collider->getPos().x + collider->getSize().x / 2,
		collider->getPos().y + collider->getSize().y / 2);

	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowPlayer", getMemDC(), rec.left, rec.top);
	if (getstate() == STATE_TYPE::ATTACK)
	{
		if (count > 80)
		{
			count = 0;
		}
		if (count > 30)
		{
			setAnimation();
			setAnimationbody();
			IMAGE->findImage("playerbody")->aniRender(getMemDC(),
				getRC().left + IMAGE->findImage("isaac")->getFrameWidth() / 2 - IMAGE->findImage("playerbody")->getFrameWidth() / 2,
				getRC().top + 28, ani_body);
			IMAGE->findImage("isaac")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
		}
		else
		{
			IMAGE->findImage("isaacEvent")->aniRender(getMemDC(), getRC().left - 18, getRC().top - 18, getAni());
		}
		count++;
	}
	else if (getstate() == STATE_TYPE::IDLE)
	{
		count = 0;
		setAnimation();
		setAnimationbody();
		IMAGE->findImage("playerbody")->aniRender(getMemDC(),
			getRC().left + IMAGE->findImage("isaac")->getFrameWidth() / 2 - IMAGE->findImage("playerbody")->getFrameWidth() / 2,
			getRC().top + 28, ani_body);
		IMAGE->findImage("isaac")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
	}
	else
	{
		IMAGE->findImage("isaacEvent")->aniRender(getMemDC(), getRC().left - 18, getRC().top - 18, getAni());
	}
}

void CPlayer::Move()
{
	if (InputManager->isStayKeyDown('S') && InputManager->isStayKeyDown('A'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFTDOWN;
		playerspeed += PLAYERMAXSPEED / sqrtf(2) / 10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x - playerspeed, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('A') && InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFTTOP;
		playerspeed += PLAYERMAXSPEED / sqrtf(2) / 10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x - playerspeed, pt.y - playerspeed);
	}
	else if (InputManager->isStayKeyDown('D') && InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHTTOP;
		playerspeed += PLAYERMAXSPEED / sqrtf(2) / 10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x + playerspeed, pt.y - playerspeed);
	}

	else if (InputManager->isStayKeyDown('D') && InputManager->isStayKeyDown('S'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHTDOWN;
		playerspeed += PLAYERMAXSPEED / sqrtf(2) / 10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x + playerspeed, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('A'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFT;
		playerspeed += PLAYERMAXSPEED / 10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x - playerspeed, pt.y);
	}

	else if (InputManager->isStayKeyDown('S'))
	{
		movecount = 5;
		playerfoward = FOWARD::DOWN;
		playerspeed += PLAYERMAXSPEED / 10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('D'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHT;
		playerspeed += PLAYERMAXSPEED / 10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x + playerspeed, pt.y);
	}
	else if (InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::UP;
		playerspeed += PLAYERMAXSPEED / 10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x, pt.y - playerspeed);
	}
	else
	{
		_slide();
		playerspeed = 0;
	}
	if (prevfoward != playerfoward)
	{
		moveani = 0;
		atkani = 0;
		if (prevfoward < 4 && playerfoward < 4)
		{
			playerspeed = 0;
		}
		prevfoward = playerfoward;
	}

	/*STAGE->getCurStage()->getMap()->GetvObstacle();
	if (IntersectRect(&rec, &rc, &STAGE->getCurStage()->getMap()->getTile()[20].rcTile))*/

	rc = RectMakeCenter(pt.x, pt.y, PLAYERWIDTH, PLAYERHEIGHT);
	collider->setPos(pt);
}
	
		

void CPlayer::_slide()
{
	movenatual++;
	if (movecount > 0)
	{
		if (movenatual % 5 == 0)
		{
			switch (playerfoward)
			{
			case FOWARD::DOWN:
				movecount--;
				pt = Vec2(pt.x, pt.y + 2.1);
				break;
			case FOWARD::LEFT:
				movecount--;
				pt = Vec2(pt.x - 2.1, pt.y);
				break;
			case FOWARD::RIGHT:
				movecount--;
				pt = Vec2(pt.x + 2.1, pt.y);
				break;
			case FOWARD::UP:
				movecount--;
				pt = Vec2(pt.x, pt.y - 2.1);
				break;
			case FOWARD::LEFTDOWN:
				movecount--;
				pt = Vec2(pt.x - 2, pt.y + 2);
				break;
			case FOWARD::LEFTTOP:
				movecount--;
				pt = Vec2(pt.x - 2, pt.y - 2);
				break;
			case FOWARD::RIGHTDOWN:
				movecount--;
				pt = Vec2(pt.x + 2, pt.y + 2);
				break;
			case FOWARD::RIGHTTOP:
				movecount--;
				pt = Vec2(pt.x + 2, pt.y - 2);
				break;
			default:
				break;
			}
		}
	}

	else movenatual = 0;
}
//
////�÷��̾� ������
//void CPlayer::move()
//{
//	// �ƽ�Ű �ڵ带 �̿��� �̵� �ӵ� ����
//	if (InputManager->isStayKeyDown(65)) setMoveSpeed(65);
//	if (InputManager->isStayKeyDown(68)) setMoveSpeed(68);
//	if (InputManager->isStayKeyDown(87)) setMoveSpeed(87);
//	if (InputManager->isStayKeyDown(83)) setMoveSpeed(83);
//
//	// ���� Ű�� ���ٸ� �̵����� �ʴ� ����
//	if (InputManager->isOnceKeyUp('A') ||
//		InputManager->isOnceKeyUp('W') ||
//		InputManager->isOnceKeyUp('S') ||
//		InputManager->isOnceKeyUp('D'))
//	{
//		movecount = 0;
//	}
//
//	// �����̴� ���� �ƴϸ�
//	if(!isMove)
//	{
//		if (velocityX > 0)
//			velocityX -= PLAYERFRICTION;
//		else if (velocityX < 0)
//			velocityX += PLAYERFRICTION;
//
//		if (velocityY > 0)
//			velocityY -= PLAYERFRICTION;
//		else if (velocityY < 0)
//			velocityY += PLAYERFRICTION;
//	}
//
//	pt = Vec2(pt.x + velocityX, pt.y + velocityY);
//	rc = RectMakeCenter(pt, PLAYERWIDTH, PLAYERHEIGHT);
//}
//
//void CPlayer::setMoveSpeed(int key)
//{
//	isMove = true;
//	switch (key)
//	{
//	case 65:
//		// ����, aŰ
//		velocityX -= PLAYERACCEL;
//		if (velocityX < -PLAYERMAXSPEED)
//			velocityX = -PLAYERMAXSPEED;
//		break;
//	case 68:
//		// ������, dŰ
//		velocityX += PLAYERACCEL;
//		if (velocityX > PLAYERMAXSPEED)
//			velocityX = PLAYERMAXSPEED;
//		break;
//	case 87:
//		// ��, wŰ
//		velocityY -= PLAYERACCEL;
//		if (velocityY < -PLAYERMAXSPEED)
//			velocityY = -PLAYERMAXSPEED;
//		break;
//	case 83: 
//		// �Ʒ�, sŰ
//		velocityY += PLAYERACCEL;
//		if (velocityY > PLAYERMAXSPEED)
//			velocityY = PLAYERMAXSPEED;
//		break;
//	}
//}

void CPlayer::fire()
{
	static int fireCnt = 0;
	static vector2 firePt = { 0, 0 };
	float fireAngle = PI;

	
	if (totalTears * 1.3 + 1 > 0)
		tearDelay = 16 - 6 * sqrtf(totalTears * 1.3 + 1);
	else if (totalTears * 1.3 + 1 < 0)
		tearDelay = 16 - 6 * totalTears;

	
	if (InputManager->isStayKeyDown(VK_UP))
	{
		headfoward = FOWARD::UP;
		fireAngle = PI_2;
		firePt = { pt.x, static_cast<float>(rc.top + 20) };
		fireCnt++;
	}
	if (InputManager->isStayKeyDown(VK_DOWN))
	{
		headfoward = FOWARD::DOWN;
		fireAngle = PI + PI_2;
		firePt = { pt.x, static_cast<float>(rc.top + 20) };
		fireCnt++;
	}
	if (InputManager->isStayKeyDown(VK_LEFT))
	{
		headfoward = FOWARD::LEFT;
		fireAngle = PI;
		firePt = { static_cast<float>(rc.left), static_cast<float>(rc.top + 20) };
		fireCnt++;
	}
	if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		headfoward = FOWARD::RIGHT;
		fireAngle = PI2;
		firePt = { static_cast<float>(rc.right), static_cast<float>(rc.top) };
		fireCnt++;
	}

	
	if (fireCnt > tearDelay)
	{
		fireCnt = 0;
		IMAGE->addImage("playerBullet", "images/playerbullet.bmp", bulletsize * 13, bulletsize, true, RGB(255, 0, 255));
		IMAGE->addImage("playerBulletShadow", "images/shadow.bmp", bulletsize, bulletsize/3, true, RGB(255, 0, 255));
		BULLET->fire(fireAngle, 6, firePt, height, distance,CHARACTER::PLAYER, bulletsize, "playerBullet");
	}
}

void CPlayer::setAnimation()
{
	if (headfoward != prevhead)
	{
		atkani = 0;
		prevhead = headfoward;
	}
	if (InputManager->isStayKeyDown(VK_UP))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("up_head");
			ANIMATION->start("up_head");
		}
	}
	else if (InputManager->isStayKeyDown(VK_DOWN))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("down_head");
			ANIMATION->start("down_head");
		}
	}
	else if (InputManager->isStayKeyDown(VK_LEFT))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("left_head");
			ANIMATION->start("left_head");
		}
	}
	else if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("right_head");
			ANIMATION->start("right_head");
		}
	}
	else
	{
		if (atkani % 30 == 0)
		{
			atkani = 0;
			ani = ANIMATION->findAnimation("playeridlehead");
			ANIMATION->start("playeridlehead");
		}
		if (atkani == 0) atkani = -1;
	}
	atkani++;
}

void CPlayer::setAnimationbody()
{

	if (InputManager->isStayKeyDown('W'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerupbody");
			ANIMATION->start("playerupbody");
		}
	}
	else if (InputManager->isStayKeyDown('S'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerdownbody");
			ANIMATION->start("playerdownbody");
		}
	}
	else if (InputManager->isStayKeyDown('A'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerleftbody");
			ANIMATION->start("playerleftbody");
		}
	}
	else if (InputManager->isStayKeyDown('D'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerrightbody");
			ANIMATION->start("playerrightbody");
		}
	}
	else
	{
		moveani = 0;
		ani_body = ANIMATION->findAnimation("playeridlebody");
		ANIMATION->start("playeridlebody");
		moveani--;
		
	}
	moveani++;
}

bool CPlayer::isFullHp()
{
	if (maxHp == hp)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPlayer::cantHpOver()
{
	if (hp > maxHp)
	{
		hp = maxHp;
	}
}

