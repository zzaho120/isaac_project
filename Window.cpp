#include "framework.h"
#include "Window.h"
#include "gameNode.h"
#include "CMapSetting.h"

POINT Window::ptMouse = POINT{ 0,0 };
CTRL Window::_currentCTRL = CTRL::CTRL_DRAW;
Window::Window()
{
	m_backBuffer = new image();
	m_backBuffer->init(SUBWINSIZEX, SUBWINSIZEY);
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

	_btnDraw = CreateWindow("button", "그리기",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY, btnWidth, btnHeight, hWnd, HMENU(0), m_hInstance, NULL);
	_btnInit = CreateWindow("button", "초기화",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY + 30, btnWidth, btnHeight, hWnd, HMENU(1), m_hInstance, NULL);
	_btnSave = CreateWindow("button", "저장",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 115, startY, btnWidth, btnHeight, hWnd, HMENU(2), m_hInstance, NULL);
	_btnLoad = CreateWindow("button", "불러오기",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 115, startY + 30, btnWidth, btnHeight, hWnd, HMENU(3), m_hInstance, NULL);
	_btnExit = CreateWindow("button", "그리기 종료",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 115, startY + 60, btnWidth, btnHeight, hWnd, HMENU(4), m_hInstance, NULL);
	_editStr = CreateWindow("edit", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
		startX, startY + 90, 200, 25, hWnd, HMENU(5), m_hInstance, NULL);
	SetDlgItemText(hWnd, (int)HMENU(5), "저장 파일 이름 입력");
	_listFile = CreateWindow("listbox", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		startX + 230, startY, 100, 200, hWnd, HMENU(6), m_hInstance, NULL);
	FileListSet(fileNames);
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
				if (SUBWIN->getMap()->save(saveFileName))
				{
					MessageBox(hWnd, "저장 성공", "알림", MB_OK);
					SUBWIN->getFileList().clear();
					SUBWIN->FileListSet(SUBWIN->getFileList());
				}
				else
					MessageBox(hWnd, "저장 실패", "알림", MB_OK);
				break;
			case CTRL::CTRL_LOAD:
				GetDlgItemText(hWnd, (int)HMENU(6), saveFileName, strlen(saveFileName));
				if (SUBWIN->getMap()->load(saveFileName))
					MessageBox(hWnd, "불러오기 성공", "알림", MB_OK);
				else
					MessageBox(hWnd, "불러오기 실패", "알림", MB_OK);
				break;
			case CTRL::CTRL_EXIT:
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
	//로그 윈도우 생성
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
	wc.lpszClassName = "그리기 툴";
	RegisterClass(&wc);
	//부모 윈도우 오른쪽에 위치 하자.
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

	hWnd = CreateWindow("그리기 툴", "그리기 툴",
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL, hInst, NULL);

	AdjustWindowRect(&rc, WINSTYLE, FALSE);

	SetWindowPos(hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER);

	ShowWindow(hWnd, SW_SHOW);
}

void Window::GetFiles(vector<char*>& vec)
{

	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile("save/*.map", &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			vec.push_back(fd.cFileName);
		} while (FindNextFile(hFind, &fd));
	}
	FindClose(hFind);
}

void Window::FileListSet(vector<char*>& vec)
{
	GetFiles(vec);
	for (int i = 0; i < vec.size(); i++) 
	{
		SendMessage(_listFile, LB_DELETESTRING, 0, 0);
	}
	for (int i = 0; i < vec.size(); i++)
	{
		SendMessage(_listFile, LB_ADDSTRING, 0, (LPARAM)vec[i]);
	}
}
