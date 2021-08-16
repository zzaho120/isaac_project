#pragma once
#include"singleton.h"
class CCollider;
class CMap;
class collisionManager : public Singleton<collisionManager>
{
private:
public:
	collisionManager();
	~collisionManager();
	/*HRESULT init();
	void release();
	void update();
	void render();
	*/
	bool isCollision(CCollider* _left, CCollider* _right);
	bool isCollision(RECT _left, RECT _right);
	//bool isRectCollision(RECT smallRc, RECT bigRc);

	int whereAreYouGoing(float& _prevX, float& _prevY, float _x, float _y);
	int whereAreYouGoing(vector2& _prevPt, vector2 _Pt);
	
	vector2 tileCollision(CMap* _map, vector2 _pt, vector2& _prevPt, int _foward , int _type);
	void monsterCollision(RECT& _rc, RECT& _prevRc, int _foward);
	vector2 sliding(int _foward, vector2 _pt);
};