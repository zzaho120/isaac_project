#pragma once
#include "gameNode.h"
class CGameScene : public gameNode
{
private:
	bool isPause;
public:
	CGameScene();
	~CGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

