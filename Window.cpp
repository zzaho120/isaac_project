#include "framework.h"
#include "Window.h"
#include "gameNode.h"
#include "CMapSetting.h"
#include "TestMonsterScene.h"

POINT Window::ptMouse = POINT{ 0,0 };
CTRL Window::_currentCTRL = CTRL::CTRL_DRAW;
Window::Window()
{
	m_backBuffer = new image();
	m_backBuffer->init(SUBWINSIZEX, SUBWINSIZEY);
	fileCnt = 0;
}

Window::~Window()
{
	SAFE_DELETE(m_backBuffer);
}

void Window::init()
{
	CreateSubWindow();

	isActive = false;

	int startX = 10;
	int startY = 10;
	int btnWidth = 100;
	int btnHeight = 25;

	_btnDraw = CreateWindow("button", "�׸���",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY, btnWidth, btnHeight, hWnd, HMENU(0), m_hInstance, NULL);
	_btnInit = CreateWindow("button", "�ʱ�ȭ",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY + 30, btnWidth, btnHeight, hWnd, HMENU(1), m_hInstance, NULL);
	_btnSave = CreateWindow("button", "����",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 115, startY, btnWidth, btnHeight, hWnd, HMENU(2), m_hInstance, NULL);
	_btnLoad = CreateWindow("button", "�ҷ�����",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 115, startY + 30, btnWidth, btnHeight, hWnd, HMENU(3), m_hInstance, NULL);
	_btnExit = CreateWindow("button", "�׸��� ����",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 115, startY + 60, btnWidth, btnHeight, hWnd, HMENU(4), m_hInstance, NULL);
	_editStr = CreateWindow("edit", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
		startX, startY + 90, 200, 25, hWnd, HMENU(5), m_hInstance, NULL);
	SetDlgItemText(hWnd, (int)HMENU(5), "���� ���� �̸� �Է�");
	_btnRemoveFile = CreateWindow("button", "���� ����",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		startX + 230, startY + 200, btnWidth, btnHeight, hWnd, HMENU(8), m_hInstance, NULL);

	_listFile = CreateWindow("listbox", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		startX + 230, startY, 100, 200, hWnd, HMENU(6), m_hInstance, NULL);
	FileListSet();

	_btnSetRoom = CreateWindow("button", "�� ����",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		startX, startY + 60, btnWidth, btnHeight, hWnd, HMENU(7), m_hInstance, NULL);

	objFrame = { 0,0 };
	monsterFrame = { 0,0 };
	clickIndex = 0;
}

void Window::release()
{
}

void Window::update()
{
	if (currentScene != NULL)
	{
		currentScene->update();
	}
}

void Window::render()
{
	HDC hdc = GetDC(hWnd);
	PatBlt(m_backBuffer->getMemDC(), 0, 0, SUBWINSIZEX, SUBWINSIZEY, WHITENESS);

	if (currentScene != NULL)
	{
		currentScene->render(m_backBuffer->getMemDC());
	}
	m_backBuffer->render(hdc);
	ReleaseDC(hWnd, hdc);
}

void Window::SetScene(gameNode* scene)
{
	currentScene = scene;
	currentScene->init();
}

LRESULT Window::WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char saveFileName[100];
	int idx = -1;
	char removeStr[64] = "���õ� �׸��� �����ϴ�.";
	char folderPath[64] = "save/";
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		SUBWIN->SetIsActive(true);
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		break;
	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			switch ((CTRL)LOWORD(wParam))
			{
			case CTRL::CTRL_DRAW:
				_currentCTRL = (CTRL)(LOWORD(wParam));
				break;
			case CTRL::CTRL_INIT:
				SUBWIN->getMap()->tileInit();
				break;
			case CTRL::CTRL_SAVE:
				GetDlgItemText(hWnd, (int)HMENU(5), saveFileName, strlen(saveFileName));
				strcat(folderPath, saveFileName);
				if (SUBWIN->getMap()->save(folderPath))
				{
					MessageBox(hWnd, "���� ����", "�˸�", MB_OK);
					SUBWIN->FileListSet();
				}
				else
					MessageBox(hWnd, "���� ����", "�˸�", MB_OK);
				break;
			case CTRL::CTRL_LOAD:
				idx = SendMessage(SUBWIN->getListHandle(), LB_GETCURSEL, 0, 0);
				SendMessage(SUBWIN->getListHandle(), LB_GETTEXT, idx, (LPARAM)saveFileName);
				strcat(folderPath, saveFileName);
				if (SUBWIN->getMap()->load(folderPath))
					MessageBox(hWnd, "�ҷ����� ����", "�˸�", MB_OK);
				else
					MessageBox(hWnd, "�ҷ����� ����", "�˸�", MB_OK);
				break;
			case CTRL::CTRL_SETROOM:
				idx = SendMessage(SUBWIN->getListHandle(), LB_GETCURSEL, 0, 0);
				if (idx != -1)
				{
					SendMessage(SUBWIN->getListHandle(), LB_GETTEXT, idx, (LPARAM)saveFileName);
					strcat(folderPath, saveFileName);
					SUBWIN->getTest()->init(folderPath);
				}
				else MessageBox(hWnd, "������ ������ ��, �� ���� Ŭ��", "�˸�", MB_OK);
				break;
			case CTRL::CTRL_REMOVE:
				idx = SendMessage(SUBWIN->getListHandle(), LB_GETCURSEL, 0, 0);
				SendMessage(SUBWIN->getListHandle(), LB_GETTEXT, idx, (LPARAM)removeStr);
				if (idx != -1)
				{
					if (IDOK == MessageBox(SUBWIN->GetHwnd(), removeStr, 
						"�Ʒ��� �׸��� �����ϰڽ��ϱ�?",
						MB_ICONQUESTION | MB_OKCANCEL))
					{
						SendMessage(SUBWIN->getListHandle(), LB_DELETESTRING, idx, 0);
						strcat(folderPath, removeStr);
						DeleteFile(folderPath);
					}
				}
				break;
			case CTRL::CTRL_EXIT:
				SCENE->changeScene("test");
				DestroyWindow(hWnd);
				break;
			}
			break;
		}
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::CreateSubWindow()
{
	//�α� ������ ����
	int x, y, cx, cy;
	WNDCLASS wc;
	RECT rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)Window::WndLogProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "�׸��� ��";
	RegisterClass(&wc);
	//�θ� ������ �����ʿ� ��ġ ����.
	RECT rcWin;
	GetWindowRect(m_hWnd, &rcWin);

	cx = SUBWINSIZEX;
	cy = SUBWINSIZEY;
	x = rcWin.right;
	y = rcWin.top;

	rc.left = 0;
	rc.top = 0;
	rc.right = cx;
	rc.bottom = cy;

	HWND hParenthWnd = NULL;
	HINSTANCE hInst = NULL;

	hParenthWnd = m_hWnd;
	hInst = GetModuleHandle(NULL);

	hWnd = CreateWindow("�׸��� ��", "�׸��� ��",
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL, hInst, NULL);

	AdjustWindowRect(&rc, WINSTYLE, FALSE);

	SetWindowPos(hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER);

	ShowWindow(hWnd, SW_SHOW);
}

void Window::FileListSet()
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile("save/*.map", &fd);

	for(int i = 0; i < fileCnt; i++)
		SendMessage(_listFile, LB_DELETESTRING, 0, 0);
	fileCnt = 0;

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			fileCnt++;
			SendMessage(_listFile, LB_ADDSTRING, 0, (LPARAM)fd.cFileName);
		} while (FindNextFile(hFind, &fd));
	}
	FindClose(hFind);
}