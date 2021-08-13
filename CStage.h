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
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerLink(CPlayer* _player) { player = _player; }
};