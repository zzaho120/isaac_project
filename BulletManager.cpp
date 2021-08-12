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
	// �Ѿ� Ŭ���� ��ü �ϳ��� �������� �����ؼ� �ʱ�ȭ�� ���� vector�� �߰�
	CBullet* tempBullet = new CBullet;
	tempBullet->init(angle, speed, pt, height);
	vBullet.push_back(tempBullet);
}

void BulletManager::move()
{
	for (viBullet = vBullet.begin(); viBullet != vBullet.end(); ++viBullet)
	{
		(*viBullet)->move();

		// �Ѿ� RECT�� �Ѿ��� �׸��� RECT�� �浹�� �ȴٸ�
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