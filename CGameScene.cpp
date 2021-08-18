#include "framework.h"
#include "CGameScene.h"

CGameScene::CGameScene() :
	isPause(false)
{
}

CGameScene::~CGameScene()
{
}

HRESULT CGameScene::init()
{
	ENEMY->init();
	ITEM->init();
	MAP->init();
	STAGE->init();
	ALLUI->init();

	isPause = false;
    return S_OK;
}

void CGameScene::release()
{
}

void CGameScene::update()
{
	if (!isPause)
	{
		STAGE->update();
		BULLET->update();
		ENEMY->update();
		ITEM->update();
		ALLUI->update();
	}

	if (InputManager->isOnceKeyDown('P'))
		isPause = !isPause;
}

void CGameScene::render()
{
	STAGE->render();
	BULLET->render();
	ENEMY->render();
	ITEM->render();
	MAP->render();
	ALLUI->render();
}
