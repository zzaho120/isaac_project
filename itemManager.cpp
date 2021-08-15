#include "framework.h"
#include "itemManager.h"
#include "CItem.h"
itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
    return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{

}

void itemManager::render()
{
    iItem = item.begin();
    for (iItem; iItem < item.end(); ++iItem)
    {
        (*iItem)->render();
    }
}

void itemManager::respawnItem(ITEM_TYPE type, vector2 pos)
{
    CItem* _item;
    switch (type)
    {
    case ITEM_TYPE::ITEM_HEART:
        _item = new CHeart(pos);
        break;
    case ITEM_TYPE::ITEM_COIN:
        _item = new CCoin(pos);
        break;
    default:
        break;
    }
    item.push_back(_item);
}

viItem itemManager::getviItem(int number)
{
    iItem = item.begin() + number;
    return iItem;
}

void itemManager::itemRemove(int number)
{
    item.erase(item.begin() + number);
}
