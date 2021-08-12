#include "framework.h"
#include "BulletManager.h"
#include "CBullet.h"

HRESULT BulletManager::init()
{
	return S_OK;
}

void BulletManager::release()
{
	for (int i = 0; i < vBullet.size(); ++i)
	{
		SAFE_DELETE(vBullet[i]);
	}
	vBullet.clear();
}

void BulletManager::update()
{
	move();
}

void BulletManager::render()
{
	for (viBullet = vBullet.begin(); viBullet != vBullet.end(); ++viBullet)
	{
		(*viBullet)->render();
	}
}

void BulletManager::fire(float angle, float speed, vector2 pt, int height)
{
	// 총알 클래스 객체 하나를 동적으로 생성해서 초기화한 다음 vector에 추가
	CBullet* tempBullet = new CBullet;
	tempBullet->init(angle, speed, pt, height);
	vBullet.push_back(tempBullet);
}

void BulletManager::move()
{
	for (viBullet = vBullet.begin(); viBullet != vBullet.end(); ++viBullet)
	{
		(*viBullet)->move();

		// 총알 RECT가 총알의 그림자 RECT와 충돌이 된다면
		if(COLLISION->isCollision((*viBullet)->getRC(), (*viBullet)->getshadow()))
		{
			removeBullet(viBullet);
			break;
		}
	}
}

void BulletManager::removeBullet(vector<CBullet*>::iterator iter)
{
	vBullet.erase(iter);
}