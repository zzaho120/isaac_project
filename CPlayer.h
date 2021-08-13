#pragma once
#include"CCharacter.h"
const int PLAYERWIDTH = 65;
const int PLAYERHEIGHT = 65;
const int PLAYERACCEL = 1;
const int PLAYERFRICTION = 1;

enum FOWARD
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTTOP,
	RIGHTTOP,
	LEFTDOWN,
	RIGHTDOWN
};

class CMap;
class CPlayer : public CCharacter
{
private:
	int count;

	int bomb;
	int key;
	int maxHp;
	int coin;

	bool isMove;
	/*float velocityX;
	float velocityY;*/
	float playerspeed;
	float PLAYERMAXSPEED;

	int bulletsize; // bullet infomation
	float distance;
	float height;

	int playerfoward; // player move 
	int prevfoward;
	
	int headfoward;
	int prevhead;
	int movecount;
	int movenatual;
	int moveani;
	

	float totalTears;
	int tearDelay;

	animation* ani_body;
	int atkani;

	CMap* room;
public:
	CPlayer();
	CPlayer(Vec2 _pos, RECT _rc, int _hp);
	~CPlayer();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void Move();
	void _slide();
	void fire();
	void UseBomb();
	void setAnimation();
	void setAnimationbody();

	void setRoomLink(CMap* _room) { room = _room; }
};