#pragma once
#include "gameNode.h"
class CPlayer;
class CPlayerUI : public gameNode
{
private:
public:
	CPlayerUI();
	~CPlayerUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(CPlayer* _player);
};

