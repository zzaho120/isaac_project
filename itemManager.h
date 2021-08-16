#pragma once

#include "singleton.h"

class CItem;
typedef vector <CItem*> vItem;
typedef vector <CItem*>::iterator viItem;
class itemManager : public Singleton<itemManager>
{
private :
	vItem item;
	viItem iItem;
public :
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void respawnItem(ITEM_TYPE type, vector2 pos);
	vItem getItem() { return item; }
	viItem getviItem(int number);
	void itemRemove(int number);
	void respawnRandomBasicItem(vector2 pos);
};

