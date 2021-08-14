#pragma once
#include"gameNode.h"

class CObstacle;
class CMap : public gameNode
{
private:
	tagRoom room;
	vector<CObstacle*> vObstacle;
	vector<CObstacle*>::iterator viObstacle;
public:
	CMap();
	CMap(const char* fileName);
	~CMap();

	virtual HRESULT init();
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void load(const char* fileName);
	void tileSet();

	void setMonster(MONSTER_TYPE type, vector2 pt);

	tagTile* getMap() { return room.tile; }
};