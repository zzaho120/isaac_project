#pragma once
#include"singleton.h"
class CCollider;
class CMap;
class CPlayer;
class CFSM;
class collisionManager : public Singleton<collisionManager>
{
private:
public:
	collisionManager();
	~collisionManager();

	bool isCollision(CCollider* _left, CCollider* _right);
	bool isCollision(RECT _left, RECT _right);
	//bool isRectCollision(RECT smallRc, RECT bigRc);

	int whereAreYouGoing(float& _prevX, float& _prevY, float _x, float _y);
	int whereAreYouGoing(vector2& _prevPt, vector2 _Pt);
	
	vector2 tileCollision(CMap* _map, vector2 _pt, vector2& _prevPt, int _foward , int _type);
	void monsterCollision(RECT& _rc, RECT& _prevRc, int _foward);
	vector2 sliding(int _foward, vector2 _pt);
	vector2 wallCollision(vector2 _objectPt, vector2 _startPt, float _sizeX, float _sizeY);
	void stageCollision(CPlayer* _player);
	void isMonsterDie();
};