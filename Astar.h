#pragma once
#include"gameNode.h"
/*
�־��� ��������� ��ǥ������ ���� �ִ� ��θ� ã�Ƴ��� �׷��� �˰��� �� �ϳ�.
F=g+h
f = ���(���������� ���� �� ��� ������� �̵��ϴ� �ɸ� ���� �������� ��ħ)
g = �簢������ ���� ���ο� �簢�������� �̵����
h = �簢�� ���κ��� ���� ������������ �����̵� ���
(�밢�� �̵��� �ƴ� ���μ��� �̵��� ���� ������� ���, ��ֹ��� ���� ��Ҵ� ������� �ʴ´�.)

���ۿ��� : ���������� �̵��Ҽ� �ִ� ������ ���¸���Ʈ�� �߰�
��ġ�� �ٽ� Ȯ���� �ʿ䰡 ���� ������ Ŭ���� ����Ʈ�� �߰�
���� ����Ʈ���� ���� ����� ���� ��ġ�� ���� ��ġ�� ����
�� ������ �ݺ�
F���� �����ϴٸ� �ӵ����� �������� ���� ����Ʈ�� �� �ʰ� �߰� �Ȱ��� �����ϴ� ���� ������.
*/

#define TILE_X 20	//����Ÿ��
#define TILE_Y 20	//����Ÿ��
#define WIDTH  35	//Ÿ�� ���α���
#define HEIGHT 35	//Ÿ�� ���α���
#define BIGNUM 5000 

//Ÿ�� �Ӽ�
enum class TILE_TYPE
{
	TILE_TYPE_EMPTY,	//��Ÿ�� (�������� �ִ°�)
	TILE_TYPE_START,	//��������
	TILE_TYPE_END,		//������
	TILE_TYPE_WALL		//��
};
enum class ASTAR_STATE
{
	ASTAR_STATE_SEARCHING,//�˻���
	ASTAR_STATE_FOUND,	//�߰�!
	ASTAR_STATE_NOWAY,	//�����
	ASTAR_STATE_END

};
struct aStarTile
{
	RECT rc;
	COLORREF color;
	bool walkable;		//�������� �ֳ�	
	bool listOn;		//openList�� �߰��Ǿ����� ����
	int i, j;
	int F, G, H;
	char str[128];
	aStarTile* parent;	//�θ� Ÿ�� �ּ�
	TILE_TYPE type;		//Ÿ�ϼӼ�
};

class Astar : public gameNode
{
private:
	
	aStarTile _tile[TILE_X][TILE_Y];
	vector<aStarTile*> _openList;
	vector<aStarTile*> _closeList;

	ASTAR_STATE _astarState;
	TILE_TYPE _selectType;
	COLORREF _selectedTypeColor;

	int _startX, _startY;
	int _endX, _endY;
	int _lastIndex;	//���߿� �߰��� Ŭ���� ����Ʈ�� �ε���

	bool _startPointSet;
	bool _endPointSet;

	int Ci;
	int Cj;
	int Cg;


	RECT rc[6];
	HBRUSH newBrush, oldBrush;
	HFONT newFont, oldFont;


public:
	Astar();
	~Astar();

	 HRESULT init();
	 void release();
	 void update();
	 void render();

	 void tileComposition();//��ġ
	 void tileInitializing();//��ġ�� �Ӽ��� �°� �ʱ�ȭ
	 void addOpenList();	//���¸���Ʈ �߰�
	 void caculateH();		//���¸���Ʈ�� Ÿ�� H�� ���
	 void caculateF();		//���¸���Ʈ�� Ÿ�� F�� ���
	 void addCloseList();	//���� ���� F������ Ŭ���� ����Ʈ�� �߰�
	 void checkArrive();	//�����ߴ��� ���� üũ
	 void showWay(aStarTile* tile);//������ ���������� ���������� �մ� ��� ��������
	 void typeColor(TILE_TYPE type);

};

