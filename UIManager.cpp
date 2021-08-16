#include "framework.h"
#include "UIManager.h"
#include "CUI.h"
#include "CPlayerUI.h"
#include "CMinimap.h"
#include "CPlayer.h"
#include "CMap.h"
UIManager::UIManager()
{
	playerUI = new CPlayerUI;
	minimap = new CMinimap;
}

UIManager::~UIManager()
{

}

HRESULT UIManager::init()
{
	playerUI->init();
	minimap->init();
	minimap->setRND(randomMap);
	minimap->mapAttrSetting();
	return S_OK;
}

void UIManager::release()
{
	playerUI->release();
	minimap->release();
}

void UIManager::update()
{
	minimap->update();
}

void UIManager::render()
{
	playerUI->render(player);
	minimap->render();
}
