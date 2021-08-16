#pragma once
#include "singleton.h"

class CMap;
class mapManager : public Singleton<mapManager>
{
private:
	vector<CMap*> vNormalRoom;
	vector<CMap*>::iterator viNormalRoom;

	vector<CMap*> vBossRoom;
	vector<CMap*>::iterator viBossRoom;

	vector<CMap*> vShopRoom;
	vector<CMap*>::iterator viShopRoom;

	int maxRoomNum[3];
public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void render();

	vector<CMap*> getNormalRoom() { return vNormalRoom; }
	vector<CMap*> getBossRoom() { return vBossRoom; }
	vector<CMap*> getShopRoom() { return vShopRoom; }
	int getMaxRoomNum(int type) { return maxRoomNum[type]; }
};