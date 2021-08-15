#include "framework.h"
#include "RandomMapGenerator.h"

RandomMapGenerator::RandomMapGenerator() :
	started(false), placedSpecial(false), isMapCompleted(false),
	floorplanCount(0),
	maxRooms(9), minRooms(6), bossRoomNum(-1), rewardRoomNum(-1),
	shopRoomNum(-1)
{
	ZeroMemory(map, sizeof(map));
	ZeroMemory(floorplan, sizeof(floorplan));
	endRoom.clear();
}

RandomMapGenerator::~RandomMapGenerator()
{
}

void RandomMapGenerator::init()
{
	ZeroMemory(map, sizeof(map));
	ZeroMemory(floorplan, sizeof(floorplan));

	memset(floorplan, 0, sizeof(floorplan));
	endRoom.clear();

	placedSpecial = false;
	isMapCompleted = false;
	floorplanCount = 0;
}

void RandomMapGenerator::start()
{
	started = true;
	placedSpecial = false;
	visit(45);
}

void RandomMapGenerator::update()
{
	while (!isMapCompleted)
	{
		bool created = false;
		if (started)
		{
			if (cellQueue.size() > 0)
			{
				int roomNumber = cellQueue.front();
				cellQueue.pop();
				int roomLine = roomNumber % 10;

				if (roomLine > 1) created = created | visit(roomNumber - 1);
				if (roomLine < 9) created = created | visit(roomNumber + 1);
				if (roomNumber > 20) created = created | visit(roomNumber - 10);
				if (roomNumber < 70) created = created | visit(roomNumber + 10);
				if (!created)
					endRoom.push_back(roomNumber);
			}
			else if (!placedSpecial)
			{
				if (floorplanCount <= minRooms)
				{
					init();
					visit(45);
				}
				else if (endRoom.size() >= 3)
				{
					bossRoomNum = endRoom.back();
					endRoom.pop_back();

					rewardRoomNum = popRandomEndRoom();
					shopRoomNum = popRandomEndRoom();
					isMapCompleted = true;
				}
				else
				{
					init();
					visit(45);
				}
			}
		}
	}
}

bool RandomMapGenerator::visit(int roomNumber)
{
	if (floorplan[roomNumber])
		return false;

	int neighbours = neighbourCount(roomNumber);

	if (neighbours > 1)
		return false;

	if (floorplanCount >= maxRooms)
		return false;

	if ((float)RND->getInt(10) / 10.0 < 0.5 && roomNumber != 45)
		return false;

	cellQueue.push(roomNumber);
	floorplan[roomNumber] = true;
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

void RandomMapGenerator::roomSetting()
{
	for (int i = 0; i < 100; i++)
	{
		if (floorplan[i])
			map[i].setRoomAttr(ROOM_TYPE_ATTR::NONCHECK);
		else if (!floorplan[i])
			map[i].setRoomAttr(ROOM_TYPE_ATTR::NONEROOM);

		map[bossRoomNum].setMarkAttr(ROOM_MARK_ATTR::BOSS);
		map[shopRoomNum].setMarkAttr(ROOM_MARK_ATTR::SHOP);
		map[rewardRoomNum].setMarkAttr(ROOM_MARK_ATTR::REWARD);
	}
}

void RandomMapGenerator::mapGenerate()
{
	start();
	update();
	roomSetting();
}
