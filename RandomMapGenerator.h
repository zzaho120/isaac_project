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
	int floorplan[100];
	int floorplanCount;
	int maxRooms;
	int minRooms;
public:
	RandomMapGenerator();
	~RandomMapGenerator();

	void init();
	void start();
	void update();
	bool visit(int roomNumber);
	int neighbourCount(int roomNumber);
	int popRandomEndRoom();

	CMap* getRNDGenMap() { return map; }
};