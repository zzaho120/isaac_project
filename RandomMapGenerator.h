#pragma once
#include "CMap.h"
#include <queue>
#include <stack>
class RandomMapGenerator
{
private:
	CMap map[100];

	bool started;
	bool placedSpecial;

	queue<int> cellQueue;
	vector<int> endRoom;

	bool floorplan[100];
	int floorplanCount;

	int maxRooms;
	int minRooms;

	int bossRoomNum;
	int shopRoomNum;
	int rewardRoomNum;
public:
	RandomMapGenerator();
	~RandomMapGenerator();

	void init();
	void start();
	void update();
	bool visit(int roomNumber);
	int neighbourCount(int roomNumber);
	int popRandomEndRoom();
	void roomSetting();

	CMap* getRNDGenMap() { return map; }
	vector<int> getEndRoom() { return endRoom; }
	int getFloorplanCount() { return floorplanCount; }
	bool* getFloorplan() { return floorplan; }
};