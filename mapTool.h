#pragma once
#include"gameNode.h"

#define TILESIZE  32		//������ȭ�� Ÿ�� ������
#define TILEX     20		//����ȭ��Ÿ�� ������ X
#define TILEY     20		//����ȭ��Ÿ�� ������ Y

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ��  ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//�������� ����� �༮
enum class CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};
//����
enum class TERRAIN
{
	TR_CEMENT,TR_DESERT,TR_GRASS,TR_WATER,TR_END
};
//������Ʈ(ex : ���� ���ʿ�  ��ġ, �����̰ų� �μ����ų��ϴ� ��ȭ�� �ټ��ִ� ��ü)
enum class OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK3,
	OBJ_BLOCKS,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_NONE
};
//��ġ ��ǥ
enum class POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};
//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT  rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

};
//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
//���� Ÿ�� ����ü
struct tagCurrentTile
{
	int x;
	int y;
};
class mapTool : public gameNode
{
private:

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILESIZEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];

	int _ctrSelect;

	RECT _terrain;
	RECT _object;
	RECT _erase;
	RECT _save;
	RECT _load;



	int _pos[2];


public:
	mapTool();
	~mapTool();

	 HRESULT init();
	 void release();
	 void update();
	 void render(/*HDC hdc*/);

	 void maptoolSetup();
	 void setMap();


	 void save();
	 void load();


	 TERRAIN terrainSelect(int frameX, int frameY);
	 OBJECT objSelect(int frameX, int frameY);
};

