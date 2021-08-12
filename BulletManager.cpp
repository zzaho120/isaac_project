#include "framework.h"
#include "BulletManager.h"
#include "CBullet.h"
#include "CCollider.h"

HRESULT BulletManager::init()
{
	return S_OK;
}

void BulletManager::release()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		SAFE_DELETE(_vBullet[i]);
	}
	_vBullet.clear();
}

void BulletManager::update()
{
	move();
}

void BulletManager::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->render();
	}
}

void BulletManager::fire(float _angle, float _speed, vector2 _pt, float _height, float _distance, CHARACTER _type, int size)
{
	// �Ѿ� Ŭ���� ��ü �ϳ��� �������� �����ؼ� �ʱ�ȭ�� ���� vector�� �߰�
	CBullet* tempBullet = new CBullet;
	tempBullet->init(_angle, _speed, _pt, _height, _distance, _type, size);
	_vBullet.push_back(tempBullet);
}

void BulletManager::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->move();

		// �Ѿ� RECT�� �Ѿ��� �׸��� RECT�� �浹�� �ȴٸ�
		if(COLLISION->isCollision((*_viBullet)->getRC(), (*_viBullet)->getshadow()))
		{
			removeBullet(_viBullet);
			break;
		}
	}
}

void BulletManager::removeBullet(viBullet iter)
{
	_vBullet.erase(iter);
}

viBullet BulletManager::getviBullet(int number)
{
	_viBullet = _vBullet.begin() + number;
	return _viBullet;
}


