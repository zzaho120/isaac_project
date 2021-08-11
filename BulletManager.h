#pragma once
#include"singleton.h"

class CBullet;
class BulletManager : public Singleton<BulletManager>
{
private:
	vector<CBullet*> vBullet;
	vector<CBullet*>::iterator viBullet;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float angle, float speed, vector2 pt, int height);
	void move();
	void removeBullet(vector<CBullet*>::iterator iter);
};