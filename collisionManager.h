#pragma once
#include"singleton.h"

class CCollider;
class collisionManager : public Singleton<collisionManager>
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	bool isCollision(CCollider* _left, CCollider* _right);
	bool isCollision(RECT _left, RECT _right);
};