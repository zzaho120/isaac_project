#pragma once
#include"singleton.h"

class CMapSetting;
class TestMonsterScene;


class Window :public Singleton<Window>
{
private:
	HWND hWnd;
	static POINT ptMouse;

	image* m_backBuffer;
	gameNode* currentScene;

	HWND _btnDraw;
	HWND _btnInit;

	HWND _btnSave;
	HWND _btnLoad;

	HWND _btnExit;
	HWND _editStr;

	HWND _btnSetRoom;

	HWND _listFile;
	HWND _btnRemoveFile;



	static CTRL _currentCTRL;
	POINT objFrame;
	POINT monsterFrame;

	int clickIndex;
	int fileCnt;

	bool isActive;

	CMapSetting* map;
	TestMonsterScene* test;
public:
	Window();
	~Window();

	void init();
	void release();
	void update();
	void render();

	void SetScene(gameNode* scene);

	static LRESULT CALLBACK WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetHwnd() { return hWnd; }

	static POINT GetMousePos() { return ptMouse; }

	static CTRL GetCTRL() { return _currentCTRL; }
	void SetCTRL(CTRL ctrl) { _currentCTRL = ctrl; }

	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }

	void SetMonsterFrame(POINT frame) { monsterFrame = frame; }
	POINT GetMonsterFrame() { return monsterFrame; }

	void SetObjFrame(POINT frame) { objFrame = frame; }
	POINT GetObjFrame() { return objFrame; }

	void SetFrameIndex(int index) { clickIndex = index; }
	int GetFrameIndex() { return clickIndex; }

	void SetMapLink(CMapSetting* _map) { map = _map; }
	void SetTestLink(TestMonsterScene* _test) { test = _test; }

	CMapSetting* getMap() { return map; }
	TestMonsterScene* getTest() { return test; }

	HWND getListHandle() { return _listFile; }

	void CreateSubWindow();

	void FileListSet();
};