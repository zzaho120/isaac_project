#include "framework.h"
#include "CPlayer.h"
#include "CFSM.h"
#include "PlayerState.h"
#include "CState.h"
CPlayer::CPlayer() :
	CCharacter(), isMove(false),
	velocityX(0), velocityY(0), totalTears(0)
{
	setAni(ANIMATION->findAnimation("down_head"));
}

CPlayer::CPlayer(Vec2 _pos, RECT _rc, int _hp) :
	CCharacter(_pos, _rc, _hp), isMove(false),
	velocityX(0), velocityY(0), totalTears(0)
{ 
	setAni(ANIMATION->findAnimation("down_head"));
}

CPlayer::~CPlayer()
{ }

HRESULT CPlayer::init()
{
	CCharacter::init({ WINSIZEX / 2, WINSIZEY / 2 },
		RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, PLAYERWIDTH, PLAYERHEIGHT),
		PLAYERHEIGHT / 4 , 10);

	setAni(ANIMATION->findAnimation("playeridlehead"));
	ani_body = ANIMATION->findAnimation("playeridlebody");
	ANIMATION->start("playeridlebody");
	ANIMATION->start("playeridlehead");
	isMove = false;
	velocityX = 0;
	velocityY = 0;
	totalTears = 0;
	PLAYERMAXSPEED = 4;
	bulletsize = 30;
	distance = 100;
	height = 50;


	vector2 colliderpt = { WINSIZEX / 2, WINSIZEY / 2 + shadowdistance};
	vector2 collidersize = { PLAYERWIDTH,PLAYERHEIGHT };
	collider = new CCollider(colliderpt, collidersize);


	AI_init(this,MONSTER_TYPE::NONE);

	return S_OK;
}

void CPlayer::release()
{
}

void CPlayer::update()
{
	_move();
	fire();
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc) + shadowdistance });
}

void CPlayer::render()
{
	setAnimation(); 
	setAnimationbody();
	Rectangle(getMemDC(), getRC().left, getRC().top, getRC().right, getRC().bottom);
	RECT rec = RectMakeCenter(collider->getPos().x, collider->getPos().y, collider->getSize().x, collider->getSize().y);
	Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);
	IMAGE->findImage("mulliganbody")->aniRender(getMemDC(), 
		getRC().left + IMAGE->findImage("isaac")->getFrameWidth()/2 - IMAGE->findImage("mulliganbody")->getFrameWidth() / 2,
		getRC().top+35, ani_body);
	IMAGE->findImage("isaac")->aniRender(getMemDC(), getRC().left, getRC().top, getAni()); 
	
}

void CPlayer::_move()
{
	if (InputManager->isStayKeyDown('S') && InputManager->isStayKeyDown('A'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFTDOWN;
		playerspeed += PLAYERMAXSPEED / sqrtf(2)/10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x - playerspeed, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('A') && InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFTTOP;
		playerspeed += PLAYERMAXSPEED / sqrtf(2)/10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x - playerspeed, pt.y - playerspeed);
	}
	else if (InputManager->isStayKeyDown('D') && InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHTTOP;
		playerspeed += PLAYERMAXSPEED / sqrtf(2) /10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x + playerspeed, pt.y - playerspeed);
	}

	else if (InputManager->isStayKeyDown('D') && InputManager->isStayKeyDown('S'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHTDOWN;
		playerspeed += PLAYERMAXSPEED / sqrtf(2) /10;
		if (playerspeed >= PLAYERMAXSPEED / sqrtf(2)) playerspeed = PLAYERMAXSPEED / sqrtf(2);
		pt = Vec2(pt.x + playerspeed, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('A'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFT;
		playerspeed += PLAYERMAXSPEED  /10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x - playerspeed, pt.y);
	}

	else if (InputManager->isStayKeyDown('S'))
	{
		movecount = 5;
		playerfoward = FOWARD::DOWN;
		playerspeed += PLAYERMAXSPEED  /10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('D'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHT;
		playerspeed += PLAYERMAXSPEED  /10;
		if (playerspeed >= PLAYERMAXSPEED) playerspeed = PLAYERMAXSPEED;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x + playerspeed, pt.y);
	}
	else if (InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::UP;
		playerspeed += PLAYERMAXSPEED  /10;
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
	rc = RectMakeCenter(pt.x, pt.y, PLAYERWIDTH, PLAYERHEIGHT);
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
		BULLET->fire(fireAngle, 10, firePt, height, distance,CHARACTER::PLAYER, bulletsize);
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
			ani->start();
		}
	}
	else if (InputManager->isStayKeyDown(VK_DOWN))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("down_head");
			ani->start();
		}
	}
	else if (InputManager->isStayKeyDown(VK_LEFT))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("left_head");
			ani->start();
		}
	}
	else if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("right_head");
			ani->start();
		}
	}
	else
	{
		if (atkani % 30 == 0)
		{
			atkani = 0;
			ani = ANIMATION->findAnimation("playeridlehead");
			ani->start();
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
			ani_body->start();
		}
	}
	else if (InputManager->isStayKeyDown('S'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerdownbody");
			ani_body->start();
		}
	}
	else if (InputManager->isStayKeyDown('A'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerleftbody");
			ani_body->start();
		}
	}
	else if (InputManager->isStayKeyDown('D'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerrightbody");
			ani_body->start();
		}
	}
	else
	{
		moveani = 0;
		ani_body = ANIMATION->findAnimation("playeridlebody");
		ani_body->start();
		moveani--;
		
	}
	moveani++;
}

