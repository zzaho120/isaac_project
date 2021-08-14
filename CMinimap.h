#pragma once
#include "CUI.h"

class RandomMapGenerator;
class CMinimap : public CUI
{
private:
	tagMinimap map[100];
	RandomMapGenerator* rnd;
public:
	CMinimap();
	~CMinimap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};