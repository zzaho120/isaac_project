#pragma once
#include"image.h"
#include"AniAddList.h"
static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _minimapBuffer = IMAGE->addImage("minimap", MINIMAPSIZEX, MINIMAPSIZEY);
class gameNode
{

private:
	//image* _backBuffer;	//�����
	//void setBackBuffer();//����� ����
	
	HDC _hdc;
	bool  _managerInit;
	AniAddList* addAni;
public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	virtual void render();


	image* getBackBuffer()const { return _backBuffer; }
	HDC getHDC() const { return _hdc; }
	HDC getMemDC() const { return _backBuffer->getMemDC(); }
	HDC getMiniMapDC() const { return _minimapBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

