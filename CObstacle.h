#pragma once
#include "CObject.h"
class CObstacle : public CObject
{
private:
	OBJECT objType;
	int strength;
	DWORD attribute;
	Vec2 frame;
public:
	CObstacle();
	CObstacle(Vec2 _pos, RECT _rc, OBJECT _type);
	~CObstacle();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setObjectValue();

	Vec2 getFrame() { return frame; }

	DWORD getAttribute() { return attribute; }
};

