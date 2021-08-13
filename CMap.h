#pragma once
#include"gameNode.h"
class CMap : public gameNode
{
private:
	tagRoom room;
	tagOBJAttribute OBJattribute[TILEX * TILEY];
	DWORD attribute[TILEX * TILEY];
public:
	CMap();
	CMap(const char* fileName);
	~CMap();

	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void load(const char* fileName);
	void tileSet();

	DWORD* getAttribute() { return _attribute; }
	tagTile* getMap() { return room.tile; }
};