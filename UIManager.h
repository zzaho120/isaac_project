#pragma once
#include"singleton.h"
class CUI;
class CPlayerUI;
class CMinimap;
//typedef vector <CUI*> vUI;
//typedef vector <CUI*>::iterator viUI;
class CPlayer;
class RandomMapGenerator;
class UIManager : public Singleton<UIManager>
{
private:
	/*vUI UI;
	viUI iUI;*/
	CPlayerUI* playerUI;
	CMinimap* minimap;

	CPlayer* player;
	RandomMapGenerator* randomMap;
public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayer(CPlayer* _player) { player = _player; }
	void setrandomMap(RandomMapGenerator* _randomMap) { randomMap = _randomMap; }
	CMinimap* getMinimap() { return minimap; }
};

