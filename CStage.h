#pragma once
#include "gameNode.h"
//#include "CPlayerUI.h"

class CMap;

class CPlayer;
class RandomMapGenerator;
class CStage : public gameNode
{
private:
	CMap* room[100];
	CMap* curRoom;
	//CMinimap* minimap;
	CPlayer* player;
	RandomMapGenerator* rnd;

	int curRoomIdx;
	//CPlayerUI* playerUI;

	vector2 testPt;
	vector2 testPrevPt;
	vector2 testSize;
	RECT testRc;
	int testWidth;
	int testHeight;
	int testFoward;


	RECT prec;
public:
	virtual void update();
	virtual void render();

	void enter();
	void exit();

	void randomMapSetting();
	void setPlayerLink(CPlayer* _player) { player = _player; }
	
	void changeRoom(int roomNum);
	CPlayer* getPlayer() { return player; }
	int getCurRoomIdx() { return curRoomIdx; }
	CMap* getCurRoom() { return curRoom; }

	void playerGetItem();


};