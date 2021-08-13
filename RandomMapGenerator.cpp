#include "framework.h"
#include "RandomMapGenerator.h"

RandomMapGenerator::RandomMapGenerator() :
	started(false), placedSpecial(false), floorplanCount(0),
	maxRooms(15), minRooms(7)
{
	ZeroMemory(map, sizeof(map));
	ZeroMemory(floorplan, sizeof(floorplan));

	start();
	while(floorplanCount < maxRooms) update();
}

RandomMapGenerator::~RandomMapGenerator()
{
	
}

void RandomMapGenerator::init()
{
	ZeroMemory(map, sizeof(map));
	ZeroMemory(floorplan, sizeof(floorplan));

	start();
}

void RandomMapGenerator::start()
{
	started = true;
	visit(45);
}

void RandomMapGenerator::update()
{
	bool created = false;
	if (started)
	{
		if (cellQueue.size() > 0)
		{
			int i = cellQueue.front();
			int x = i % 10;

			if (x > 1) created = created | visit(i - 1);
			if (x < 1) created = created | visit(i + 1);
			if (i > 20) created = created | visit(i - 10);
			if (i < 70) created = created | visit(i + 10);
			if (!created)
				endRoom.push_back(i);
		}
	}
	else if (!placedSpecial)
	{
		if (floorplanCount < minRooms)
		{
			start();
			return;
		}

		placedSpecial = true;

	}
}

bool RandomMapGenerator::visit(int roomNumber)
{
	if (floorplan[roomNumber])
		return false;

	int neighbours = neighbourCount(roomNumber);

	if (neighbours > 1)
		return false;

	if (RND->getFloat() < 0.5 && roomNumber != 45)
		return false;

	cellQueue.push(roomNumber);
	floorplan[roomNumber] = 1;
	floorplanCount += 1;

	return true;
}

int RandomMapGenerator::neighbourCount(int roomNumber)
{
	return floorplan[roomNumber - 10] + 
		floorplan[roomNumber - 1] + 
		floorplan[roomNumber + 1] + 
		floorplan[roomNumber + 10];
}

int RandomMapGenerator::popRandomEndRoom()
{
	int idx = floor(RND->getFloat() * endRoom.size());
	int roomNum = endRoom[idx];
	endRoom.erase(endRoom.begin() + idx);
	return roomNum;
}
