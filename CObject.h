#pragma once
#include"gameNode.h"
#include"CCollider.h"
class CObject : public gameNode
{
protected:
	vector2			pt;
	vector2			precPt;
	//vector2			shadowpt;
	RECT			rc;
	animation*		ani;
	CCollider*		collider;
	CCollider*		colliderShadow;

	animation anitest;

	float shadowdistance;
public:
	CObject();
	CObject(Vec2 _pos, RECT _rc);
	~CObject();

	virtual HRESULT init();
	virtual HRESULT init(vector2 _pt, RECT _rc, vector2 _objectPt, vector2 _objectSize, float _shadowdistance, vector2 _objectShadowPt, vector2 _objectShadowSize);
	virtual void release();
	virtual void update();
	virtual void render();

	vector2 getPt() { return pt; }
	void setPt(vector2 _pt) { pt = _pt; }

	RECT getRC() { return rc; }
	void setRC(RECT _rc) { rc = _rc; }

	void setAni(animation* ani) { this->ani = ani; }
	animation* getAni() { return ani; }

	CCollider* getcollider() { return collider; }
	CCollider* GetcolliderShadow() { return colliderShadow; }
	void setshadowdistance(float distance) { shadowdistance = distance; }
};

