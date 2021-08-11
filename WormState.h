#pragma once
#include"CState.h"
class enemyManager;
//worm state
class Worm_idle : public CState
{
private:
	int count;
	int atk_count;
	int movetime;
	int foward;
	bool anistart;

	void Move();
	bool Inrange(int range, vector2 pt);
	bool Crossrange(int range, vector2 pt);
public:
	Worm_idle();
	virtual ~Worm_idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Worm_trace : public CState
{
private:
	int count;
	int movetime;
	int foward;
	bool anistart;

	void Move();
	int setfoward(int range, vector2 pt);

public:
	Worm_trace();
	virtual ~Worm_trace();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Worm_Atk : public CState
{
};
class Worm_Die : public CState
{
};