#pragma once
#include"CState.h"
class BulletManager;
class enemyManager;
class CPlayer;
class Hopper_Idle : public CState
{
private:
	int count;
	int movetime;
	int delay;

	int foward;
	float parabola;
	float distance;

	bool jumpstart;
	bool downstart;
	bool idlestart;

	bool idle;

	RECT shadow;

	void Jump();
	bool Inrange(int range, vector2 pt);
public:
	Hopper_Idle();
	virtual ~Hopper_Idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Hopper_Trace : public CState
{
private:
	int count;
	int movetime;
	int delay;

	float parabola;
	float angle;
	float distance;

	bool jumpstart;
	bool downstart;
	bool idlestart;

	bool idle;

	RECT shadow;

	void Jump();
public:
	Hopper_Trace();
	virtual ~Hopper_Trace();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Hopper_Atk :public CState
{
};
class Hopper_Die : public CState
{
};