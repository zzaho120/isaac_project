#include "framework.h"
#include "CGameScene.h"

CGameScene::CGameScene() :
	isPause(false), selectMenu(0),
	isKeyDown(0)
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
	selectMenu = 0;
	isKeyDown = 0;
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
	{
		isPause = true;
	}

	if (isPause)
	{
		if (InputManager->isOnceKeyDown(VK_UP))
		{
			if (selectMenu > 0)
				selectMenu--;
		}
		if (InputManager->isOnceKeyDown(VK_DOWN))
		{
			if (selectMenu < 1)
				selectMenu++;
		}
		if (InputManager->isOnceKeyDown(VK_SPACE))
			isKeyDown = true;
	}

	if (isKeyDown)
	{
		switch (selectMenu)
		{
		case 0:
			isPause = false;
			isKeyDown = false;
			break;
		case 1:
			SCENE->changeScene("mainMenu");
			break;
		}
	}
}

void CGameScene::render()
{
	STAGE->render();
	BULLET->render();
	ENEMY->render();
	ITEM->render();
	MAP->render();
	ALLUI->render();

	if (isPause)
	{
		IMAGE->alphaRender("black", getMemDC(), 0);
		IMAGE->render("pause_menu", getMemDC(), 180, 100);
		IMAGE->render("menu_arrow", getMemDC(), 325, 510 + selectMenu * 60);
	}
}