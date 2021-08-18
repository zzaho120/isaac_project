#include"framework.h"
#include "CMainMenu.h"
#include "CGameScene.h"
#include "CMapTool.h"
#include "mainGame.h"

mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	SCENE->addScene("mainMenu", new CMainMenu);
	SCENE->addScene("game", new CGameScene);
	SCENE->addScene("mapTool", new CMapTool);
	SCENE->changeScene("mainMenu");
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();
}

void mainGame::render(/*HDC hdc*/)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================
	gameNode::render();
	//==============================================
	//������� ������ HDC�׸���.(�ǵ帮�� ����.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

