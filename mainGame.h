#pragma once
#include"gameNode.h"
#include "CMapSetting.h"
#include "CMapSettingSub.h"
#include "CMap.h"
#include "TestMonsterScene.h"
#include "CMinimap.h"

#define SUBWINOPEN 1
class mainGame : public gameNode
{
private:
	CMinimap* minimap;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);
};

