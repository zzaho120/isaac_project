#pragma once
#include"gameNode.h"
class CMap : public gameNode
{
private:
	tagCurrentTile _curTile;
	tagTile _obj[TILEX * TILEY];
	tagOBJAttribute _OBJattribute[TILEX * TILEY];
	DWORD _attribute[TILEX * TILEY];
public:
	CMap();
	CMap(const char* fileName);
	~CMap();

	virtual HRESULT init();	
	virtual void release();
	virtual void update();
	virtual void render();

	void load();
	void load(const char* fileName);
	void tileSet();

	DWORD* getAttribute() { return _attribute; }
	tagTile* getMap() { return _obj; }
};