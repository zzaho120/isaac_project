#include"framework.h"
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

	CMapSetting* mapSet = new CMapSetting;
	SCENE->addScene("main", mapSet);

	SCENE->addScene("map1", new CMap);
	SCENE->addScene("test", new TestMonsterScene);
	SCENE->changeScene("test");

	SUBWIN->SetScene(new CMapSettingSub);
	SUBWIN->SetMapLink(mapSet);
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

