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
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
class CPlayer : public CCharacter
{
private:
	bool isMove;																				
	float velocityX;																			
	float velocityY;
	float playerspeed;

	int playerfoward;
	int prevfoward;
	int headfoward;
	int prevhead;

	int movecount;
	int movenatual;
	int moveani;
	float PLAYERMAXSPEED;


	float totalTears;
	int tearDelay;

	animation* ani_body;
	int atkani;
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
public:
	CPlayer();
	CPlayer(Vec2 _pos, RECT _rc, int _hp);
	~CPlayer();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void _move();
	void _slide();
	void fire();										
	void setAnimation();
	void setAnimationbody();
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
};