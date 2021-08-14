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

	/*CMapSetting* mapSet = new CMapSetting;
	TestMonsterScene* test = new TestMonsterScene;
	SCENE->addScene("main", mapSet);

	SCENE->addScene("test", test);
	SCENE->changeScene("main");

	SUBWIN->SetScene(new CMapSettingSub);
	SUBWIN->SetMapLink(mapSet);
	SUBWIN->SetTestLink(test);*/
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

