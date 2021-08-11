#pragma once
#include "gameNode.h"


class CMapSetting : public gameNode
{
private:
	tagTile _tile[TILEX * TILEY];
	bool isDebug;
public:
	CMapSetting();
	~CMapSetting();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileInit();
	void mapToolSetup();
	void setMap();

	bool save(const char* fileName);
	bool load(const char* fileName);

	OBJECT objSelect(int frameX, int frameY);

	MONSTER_TYPE monsterSelect(int frameX, int frameY);

	tagTile* getTile() { return _tile; }
};