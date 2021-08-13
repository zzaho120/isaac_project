#pragma once
#include "CObject.h"



class CBullet : public CObject
{
private:
	float angle;				// �߻� ����
	float speed;				// �߻� �ӵ�
	float fallingHeight;		// �߻� �� �������� ����
	float distance;				// �߻� �� �������� ����
	int BULLETSIZE;				// �Ѿ� ũ��
	vector2 firePt;				// �߻� ���� ��

	RECT shadow;
	vector2 shadowPt;

	CHARACTER type;
public:
	CBullet();
	CBullet(Vec2 _pos, RECT _rc, float _angle, float _speed,float _distance, int _height, CHARACTER _type, int size);
	~CBullet();

	virtual HRESULT init(float _angle, float _speed, vector2 _pt, float _height, float _distance, CHARACTER _type, float size);
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

	RECT getshadow() { return shadow; }

	CHARACTER gettype() { return type; }
};