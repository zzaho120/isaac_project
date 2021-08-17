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

public:
	CObstacle();
	CObstacle(Vec2 _pos, RECT _rc, OBJECT _type);
	CObstacle(CObstacle* copy);
	~CObstacle();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObjectValue();

	bool getUnmovalbe() { return isUnmovable; }
	void setUnmovalbe(bool move) { isUnmovable = move; }
	bool getDestroyBomb() { return isDestroyByBomb; }
	bool getDestroyBullet() { return isDestroyByBullet; }

	Vec2 getFrame() { return frame; }
	OBJECT getObjType() { return objType; }

	void setObjType(OBJECT obj) { objType = obj; }
	void setDoorFrame(Vec2 doorFrame) { frame = doorFrame; }

	int getStrength() { return strength; }
	void setStrength(int number) { strength = number; }
};

