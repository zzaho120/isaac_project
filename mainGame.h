#pragma once
#include"gameNode.h"
#include "CMapSetting.h"
#include "CMapSettingSub.h"
#include "CMap.h"
#include "TestMonsterScene.h"

#define SUBWINOPEN 1
class mainGame : public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

