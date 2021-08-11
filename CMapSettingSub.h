#pragma once
#include"gameNode.h"
class CMapSettingSub : public gameNode
{
private:
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	struct tagMonsterTile _monsterTile[MONSTERTILEX * MONSTERTILEY];
	bool isDebug;
public:
	CMapSettingSub();
	~CMapSettingSub();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void mapToolSetup();
	void setMap();
};