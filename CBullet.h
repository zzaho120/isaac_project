#pragma once
#include "CObject.h"

const int BULLETSIZE = 20;

class CBullet : public CObject
{
private:
	float angle;				// 발사 각도
	float speed;				// 발사 속도
	float fallingHeight;		// 발사 후 떨어지는 높이

	vector2 firePt;				// 발사 시작 점
public:
	CBullet();
	CBullet(Vec2 _pos, RECT _rc, float _angle, float _speed, int _height);
	~CBullet();

	virtual HRESULT init(float _angle, float _speed, vector2 _pt, float _height);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();

	float getAngle() { return angle; }
	void setAngle(float _angle) { angle = _angle; }

	float getSpeed() { return speed; }
	void setSpeed(float _speed) { speed = _speed; }

	vector2 getFirePt() { return firePt; }
	void setFirePt(vector2 pt) { firePt = pt; }

};