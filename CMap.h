#pragma once
#include"gameNode.h"

class CObstacle;
class CMap : public gameNode
{
private:
	tagRoom room;
	vector<CObstacle*> vObstacle;
	vector<CObstacle*>::iterator viObstacle;

	ROOM_TYPE_ATTR roomAttr;
	ROOM_MARK_ATTR markAttr;
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
	
	ROOM_TYPE_ATTR getRoomAttr() { return roomAttr; }
	void setRoomAttr(ROOM_TYPE_ATTR attr) { roomAttr = attr; }

	ROOM_MARK_ATTR getMarkAttr() { return markAttr; }
	void setMarkAttr(ROOM_MARK_ATTR attr) { markAttr = attr; }

	vector<CObstacle*> getvObstacle() { return vObstacle; }
	vector<CObstacle*>::iterator getviObstacle(int number);
	tagTile* getTile() { return room.tile; }
	ROOM getRoomType() { return room.roomType; }
};