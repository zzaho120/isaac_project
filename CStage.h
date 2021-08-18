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
	CPlayer* player;
	RandomMapGenerator* rnd;

	int curRoomIdx;
public:
	virtual void update();
	virtual void render();

	void enter();
	void exit();

	void randomMapSetting();
	void playerEnterDoor();
	void nextStage();

	void setPlayerLink(CPlayer* _player) { player = _player; }
	
	void changeRoom(int roomNum);
	CPlayer* getPlayer() { return player; }
	int getCurRoomIdx() { return curRoomIdx; }
	CMap* getCurRoom() { return curRoom; }
};