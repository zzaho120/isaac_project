#pragma once
#include "CObject.h"
class CObstacle : public CObject
{
private:
	OBJECT objType;
	int strength;
	Vec2 frame;
	
	bool isUnmovable;
	bool isDestroyByBomb;
	bool isDestroyByBullet;

	int test;
public:
	CObstacle();
	CObstacle(Vec2 _pos, RECT _rc, OBJECT _type);
	~CObstacle();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObjectValue();

	bool getUnmovalbe() { return isUnmovable; }
	bool getDestroyBomb() { return isDestroyByBomb; }
	bool getDestroyBullet() { return isDestroyByBullet; }

	Vec2 getFrame() { return frame; }
	int gettest() { return test; }
};

