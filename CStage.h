#pragma once
#include "gameNode.h"

class CMap;
class CPlayer;
class CStage : public gameNode
{
private:
	CMap* map;
	CPlayer* player;
public:
	virtual void update();
	virtual void render();

	void enter();
	void exit();

	void setPlayerLink(CPlayer* _player) { player = _player; }
	
	CPlayer* getPlayer() { return player; }
	CMap* getMap() { return map; }
};