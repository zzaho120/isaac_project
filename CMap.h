#pragma once
#include"gameNode.h"

class CObstacle;
class CMap : public gameNode
{
private:
	tagRoom room;
	vector<CObstacle*> vObstacle;
	vector<CObstacle*>::iterator viObstacle;
	DWORD attribute[2];
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
	
	DWORD getRoomAttr() { return attribute[(UINT)MINIMAP_ATTR::ROOM]; }
	void setRoomAttr(DWORD attr) { attribute[(UINT)MINIMAP_ATTR::ROOM] = attr; }

	DWORD getMarkAttr() { return attribute[(UINT)MINIMAP_ATTR::MARK]; }
	void setMarkAttr(DWORD attr) { attribute[(UINT)MINIMAP_ATTR::MARK] = attr; }

	vector<CObstacle*> getvObstacle() { return vObstacle; }
	vector<CObstacle*>::iterator CMap::GetviObstacle(int number)
	{
		viObstacle = vObstacle.begin() + number;
		return viObstacle;
	}
};