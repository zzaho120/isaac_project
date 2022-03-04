#pragma once
#include"CCharacter.h"
const int PLAYERWIDTH = 65;
const int PLAYERHEIGHT = 65;
const int PLAYERACCEL = 1;
const int PLAYERFRICTION = 1;

class CMap;
class CPlayer : public CCharacter
{
private:
	int count;

	int bomb;
	int key;
	int maxHp;
	int coin;

	// bullet infomation
	int bulletsize; 			
	float bulletdistance;
	float height;
	float bulletDamage;
	float bulletSpeed;
	float addAngle;

	// player move 
	bool isMove;		
	float playerspeed;
	float playerMaxSpeed;
	int playerfoward;	
	int prevfoward;
	float moveDistance;

	int headfoward;
	int prevhead;
	int movecount;
	int movenatual;
	int moveani;
	

	float totalTears;
	int tearDelay;

	animation* ani_body;
	int atkani;

	bool theInnerEye;
public:
	CPlayer();
	CPlayer(Vec2 _pos, RECT _rc, int _hp);
	~CPlayer();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//player Act
	void move();
	void slide();
	void fire();
	void UseBomb();

	//player animation
	void setAnimation();
	void setAnimationbody();


	//void setRoomLink(CMap* _room) { room = _room; }
	int getFoward() { return playerfoward; }
	
	// player get Item
	void playerGetItem();
	int getMaxHp() { return maxHp; }
	int getCoin() { return coin; }
	int getBomb() { return bomb; }
	int getKey() { return key; }

	// player get item but cant over maximum
	void cantHpOver();
	void cantCoinOver() { if (coin >= 99)  coin = 99; }
	void cantBombOver() { if (bomb >= 99)  bomb = 99; }
	void cantKeyOver() { if (key >= 99)  key = 99; }
	void cantBulletSizeOver() { if (bulletsize >= 99) bulletsize = 99;}
	void cantBulletDistanceOver() { if (bulletdistance >= 400) bulletdistance = 400; }
	void cantBulletDamageOver() { if (bulletDamage >= 5) bulletDamage = 5; }
	void cantBulletSpeedOver() { if (bulletSpeed >= 10)bulletSpeed = 10; }
	void cantSpeedOver() { if (playerMaxSpeed >= 10) playerMaxSpeed = 10; }

	bool isFullHp();
	
	//Item
	void setInnerEye(bool _istrue) { theInnerEye = _istrue; }
};