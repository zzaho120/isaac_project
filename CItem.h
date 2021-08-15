#pragma once
#include "CObject.h"
class CItem : public CObject
{
protected:
	ITEM_TYPE type;
private:
public:
	CItem();
	~CItem();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	ITEM_TYPE getItemType() { return type; }
};
class CHeart : public CItem
{
private:
public:
	CHeart();
	CHeart(vector2 _pt);
	~CHeart();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};
class CCoin : public CItem
{
private:
public:
	CCoin();
	CCoin(vector2 _pt);
	~CCoin();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CBomb : public CItem
{
private:

public:
	CBomb();
	CBomb(vector2 _pt);
	~CBomb();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};

class CKey : public CItem
{
private:
public:
	CKey();
	~CKey();

	virtual HRESULT init();
	virtual void release();
	//virtual void update();
	virtual void render();
};
