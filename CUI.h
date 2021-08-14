#pragma once
#include "CObject.h"
class CUI : public CObject
{
private:

public:
	CUI();
	CUI(vector2 _pt, RECT _rc);

	~CUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

