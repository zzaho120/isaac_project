#pragma once
#include "CObject.h"
#include"BulletManager.h"
class CCharacter : public CObject
{
private:
	int				hp;
public:
	CCharacter();
	CCharacter(Vec2 _pos, RECT _rc, int _hp);
	~CCharacter();

	virtual HRESULT init();
	virtual HRESULT init(vector2 _pt, RECT _rc, float _shadowdistance, int _hp);
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	int gethp() { return hp; }
	void sethp(int _hp) { hp = _hp; }
};