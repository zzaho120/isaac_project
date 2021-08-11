#pragma once
#include"singleton.h"

#define SUBWINSIZEX 420
#define SUBWINSIZEY 500

class CMapSetting;

enum class CTRL
{
	CTRL_DRAW,
	CTRL_INIT,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_EXIT,
	CTRL_EDIT,
	CTRL_LIST,
	CTRL_END
};

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

	HWND _listFile;

	static CTRL _currentCTRL;
	POINT objFrame;
	POINT monsterFrame;

	int clickIndex;

	bool isActive;

	vector<char*> fileNames;

	CMapSetting* map;
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
	CMapSetting* getMap() { return map; }

	vector<char*>& getFileList() { return fileNames; }

	void CreateSubWindow();

	void GetFiles(vector<char*>& vec);

	void FileListSet(vector<char*>& vec);
};