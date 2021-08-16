#pragma once
#include "CItem.h"
class CUseItem : public CItem
{
protected:
	USE_ITEM usetype;
private:
public:
	CUseItem();
	CUseItem(vector2 _pt);
	~CUseItem();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
class CUseBomb : public CUseItem
{
private:
	int count;
public:
	CUseBomb();
	CUseBomb(vector2 _pt);
	~CUseBomb();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};