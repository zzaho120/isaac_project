#include "framework.h"
#include "gameNode.h"
gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//Ÿ�̸Ӷ� ������ �ֱ⸶�� ������ �Լ��� �����Ѵ�.
	//1 : ������ �ڵ�
	//2 :  Ÿ�̸� ��ȣ
	//3 :  Ÿ�̸��ֱ� 1000=1��
	//4 :  �ֱ⸶�� ������ �Լ�
	//NULL�̸� WM_TIMER�� ����
	
	//setBackBuffer();
	_hdc = GetDC(m_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(m_hWnd, 1, 10, NULL);
		addAni = new AniAddList;
		//�Ŵ��� �ʱ�ȭ
		InputManager->init();
		IMAGE->init();
		TIME->init();
		SOUND->init();
		SUBWIN->init();
		ENEMY->init();
		STAGE->init();
	}
	

	return E_NOTIMPL;
}

//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//}

void gameNode::release()
{	//Ÿ�̸� ����

	if (_managerInit)
	{
		//������ ���ϸ� ���Ḧ �ص� �޸𸮰� ������~
		KillTimer(m_hWnd, 1);
		//�Ŵ��� ����
		InputManager->releaseSingleton();
		IMAGE->releaseSingleton();
		TIME->releaseSingleton();
		RND->releaseSingleton();
		TXT->releaseSingleton();
		SCENE->releaseSingleton();
		SOUND->releaseSingleton();
		ANIMATION->releaseSingleton();
		EFFECT->releaseSingleton();
		STAGE->releaseSingleton();
		BULLET->releaseSingleton();
		SUBWIN->releaseSingleton();
		ENEMY->releaseSingleton();
		COLLISION->releaseSingleton();
		

		SCENE->release();
		IMAGE->release();
		TIME->release();
		SOUND->release();
		ANIMATION->release();
		EFFECT->release();
		STAGE->release();
		BULLET->release();
		ENEMY->release();
	}

	ReleaseDC(m_hWnd, _hdc);
	//SAFE_DELETE(_backBuffer);
}

void gameNode::update()
{
	//������� ���� ������� �ʴ´� true->false
	/*if (InputManager->isOnceKeyDown(VK_F2))
		SCENE->changeScene("main");
	if (InputManager->isOnceKeyDown(VK_F3))
		SCENE->changeScene("test");*/

	SUBWIN->update();
	//SCENE->update();
	STAGE->update();
	BULLET->update();
	ANIMATION->update();
	ENEMY->update();
	EFFECT->update();
	InvalidateRect(m_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
}

void gameNode::render()
{
	SUBWIN->render();
	//SCENE->render();
	STAGE->render();
	BULLET->render();
	TIME->render(getMemDC());
	ENEMY->render();
	EFFECT->render();
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	//case WM_TIMER:
	//	this->update();
	//	break;
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	this->render(hdc);
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_MOUSEMOVE:
		SUBWIN->SetIsActive(false);
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}//end of switch

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
