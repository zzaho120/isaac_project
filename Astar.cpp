#include "framework.h"
#include "Astar.h"

Astar::Astar()
{
}

Astar::~Astar()
{
}

HRESULT Astar::init()
{
	_astarState = ASTAR_STATE::ASTAR_STATE_END;//�ʱ���� = Ÿ�Ϲ�ġ �Ϸ���
	_selectType = TILE_TYPE::TILE_TYPE_EMPTY;//��ġ�� Ÿ�� �Ӽ� = ��Ÿ��
	_selectedTypeColor = RGB(255, 255, 255);//��ġ�� Ÿ�� ���� = �Ͼ�


	_startPointSet = false;
	_endPointSet = false;


	for (size_t i = 0; i < TILE_Y; i++)
	{
		for (size_t j = 0; j < TILE_X; j++)
		{
			_tile[i][j].type = TILE_TYPE::TILE_TYPE_EMPTY;
			_tile[i][j].color = RGB(255, 255, 255);
			_tile[i][j].parent = NULL;
			_tile[i][j].F = BIGNUM;
			_tile[i][j].H = 0;
			_tile[i][j].i = i;
			_tile[i][j].j = j;
			_tile[i][j].rc = RectMake(WINSIZEX - (TILE_X + 1) * WIDTH + WIDTH * j,
				WINSIZEX / 3 - (TILE_Y) / 2 * HEIGHT + HEIGHT * i, WIDTH, HEIGHT);
		}
	}
	for (size_t i = 0; i < 5; i++)
	{
		rc[i] = RectMake(15, 300 + i * 50, 25, 25);
	}
	return S_OK;
}

void Astar::release()
{
}

void Astar::update()
{
	if (_astarState == ASTAR_STATE::ASTAR_STATE_END)
	{
		tileComposition();
	}
	if(InputManager->isOnceKeyDown(VK_SPACE)&&_startPointSet&&_endPointSet&&_astarState== ASTAR_STATE::ASTAR_STATE_END)
	{
		tileInitializing();
	}
	if (InputManager->isOnceKeyDown('5'))
	{
		_openList.clear();
		_closeList.clear();
		init();
	}
	if (_astarState == ASTAR_STATE::ASTAR_STATE_END || _astarState == ASTAR_STATE::ASTAR_STATE_FOUND || _astarState == ASTAR_STATE::ASTAR_STATE_NOWAY)return;

	addOpenList();
	caculateH();
	caculateF();
	addCloseList();
	checkArrive();
}

void Astar::render()
{
	TextOut(getMemDC(), 15, 75, "1 :���찳", strlen("1 :���찳"));
	TextOut(getMemDC(), 15, 95, "2 :����", strlen("2 :����"));
	TextOut(getMemDC(), 15, 115, "3 :��", strlen("3 :��"));
	TextOut(getMemDC(), 15, 135, "4 :��ֹ�", strlen("4 :��ֹ�"));
	TextOut(getMemDC(), 15, 155, "5 :�ʱ�ȭ", strlen("5 :�ʱ�ȭ"));

	char str[128];

	switch (_astarState)
	{
		case ASTAR_STATE::ASTAR_STATE_END: sprintf_s(str, "�����̽� ����"); break;
		case ASTAR_STATE::ASTAR_STATE_FOUND: sprintf_s(str, "ã��"); break;
		case ASTAR_STATE::ASTAR_STATE_NOWAY: sprintf_s(str, "�����"); break;
		case ASTAR_STATE::ASTAR_STATE_SEARCHING: sprintf_s(str, "ã����..."); break;
	}
	TextOut(getMemDC(), 15, 200, str, strlen(str));


	newFont = CreateFont(9, 0, 0, 0, FW_NORMAL, false, false, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, "����");
	oldFont = (HFONT)SelectObject(getMemDC(), newFont);

	for (size_t i = 0; i < TILE_Y; i++)
	{
		for (size_t j = 0; j < TILE_X; j++)
		{
			newBrush = CreateSolidBrush(_tile[i][j].color);
			oldBrush = (HBRUSH)SelectObject(getMemDC(), newBrush);
			RectangleMake(getMemDC(), _tile[i][j].rc);
			SelectObject(getMemDC(), oldBrush);
			DeleteObject(newBrush);

			if (_tile[i][j].parent == NULL)continue;
		}
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(newFont);


	for (size_t i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(0, 255, 0));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "������");
			DeleteObject(newBrush);
		}
		if (i == 1)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(255,0, 0));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "����");
			DeleteObject(newBrush);
		}
		if (i == 2)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(220, 255, 220));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "openList");
			DeleteObject(newBrush);
		}
		if (i == 3)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(255,0, 255));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "closeList");
			DeleteObject(newBrush);
		}
		if (i == 4)
		{
			BeginSolidColor(getMemDC(), &newBrush, RGB(255, 100, 100));
			RectangleMake(getMemDC(), rc[i]);
			sprintf_s(str, "path");
			DeleteObject(newBrush);
		}
		TextOut(getMemDC(), rc[i].right + 15, rc[i].top + 5, str, strlen(str));
	}
}

void Astar::tileComposition()
{
	if (InputManager->isOnceKeyDown('1'))_selectType = TILE_TYPE::TILE_TYPE_EMPTY;
	else if (InputManager->isOnceKeyDown('2'))_selectType = TILE_TYPE::TILE_TYPE_START;
	else if (InputManager->isOnceKeyDown('3'))_selectType = TILE_TYPE::TILE_TYPE_END;
	else if (InputManager->isOnceKeyDown('4'))_selectType = TILE_TYPE::TILE_TYPE_WALL;
	typeColor(_selectType);


	if (InputManager->isStayKeyDown(VK_LBUTTON))
	{
		for (size_t i = 0; i < TILE_Y; i++)
		{
			for (size_t j = 0; j < TILE_X; j++)
			{
				if (PtInRect(&_tile[i][j].rc, m_ptMouse))
				{
					if (_tile[i][j].type == TILE_TYPE::TILE_TYPE_START)_startPointSet = false;
					if (_tile[i][j].type == TILE_TYPE::TILE_TYPE_END)_endPointSet = false;

					_tile[i][j].type = _selectType;
					_tile[i][j].color = _selectedTypeColor;

					if (_selectType == TILE_TYPE::TILE_TYPE_START)
					{
						if (_startPointSet)
						{
							_tile[_startY][_startX].color = RGB(255, 255, 255);
							_tile[_startY][_startX].type = TILE_TYPE::TILE_TYPE_EMPTY;
						}
						_startPointSet = true;
						_startX = j;
						_startY = i;
					}
					if (_selectType == TILE_TYPE::TILE_TYPE_END)
					{
						if (_endPointSet)
						{
							_tile[_endY][_endX].color = RGB(255, 255, 255);
							_tile[_endY][_endX].type = TILE_TYPE::TILE_TYPE_EMPTY;
						}
						_endPointSet = true;
						_endX = j;
						_endY = i;
					}

				}
			}
		}
	}
}

void Astar::tileInitializing()
{
	for (size_t i = 0; i < TILE_Y; i++)
	{
		for (size_t j = 0; j < TILE_X; j++)
		{
			switch (_tile[i][j].type)
			{
			case TILE_TYPE::TILE_TYPE_EMPTY:
			{
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
			break;
			case TILE_TYPE::TILE_TYPE_WALL:
			{
				_tile[i][j].walkable = false;
				_tile[i][j].listOn = false;
			}
			break;
			case TILE_TYPE::TILE_TYPE_START:
			{
				_tile[i][j].walkable = false;
				_tile[i][j].listOn = false;
				_closeList.push_back(&_tile[i][j]);
			}
			break;
			case TILE_TYPE::TILE_TYPE_END:
			{
				_endX = j;
				_endY = i;
				_tile[i][j].walkable = true;
				_tile[i][j].listOn = false;
			}
			break;
			}
		}
	}
	_astarState = ASTAR_STATE::ASTAR_STATE_SEARCHING;
	_lastIndex = 0;
}

void Astar::addOpenList()
{
	Ci = _closeList[_lastIndex]->i;
	Cj = _closeList[_lastIndex]->j;
	Cg = _closeList[_lastIndex]->G;


	if (Ci != 0)//0��° ���̾ƴϸ� ��ܶ��� ���
	{
		if (_tile[Ci - 1][Cj].walkable)//��� ��� Ÿ���� �������� �ִٸ�
		{
			if (!_tile[Ci - 1][Cj].listOn)//���¸���Ʈ�� ������ �ȵǾ� �ִ� Ÿ���̶��
			{
				_tile[Ci - 1][Cj].listOn = true;//���¸���Ʈ�� ���ԵǾ���.
				_tile[Ci - 1][Cj].color = RGB(220, 255, 220);
				_tile[Ci - 1][Cj].G = Cg + 10;//Ÿ����G���� Ŭ���� ����Ʈ�� ���� G+10
				_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];//Ÿ���� �θ� Ŭ���� ����Ʈ�� ���������� �߰�
				_openList.push_back(&_tile[Ci - 1][Cj]);//���� ����Ʈ�� �߰�
			}
			else//���¸���Ʈ�� ������ �Ǿ� �ִ� Ÿ���̶��
			{
				if (Cg + 10 < _tile[Ci - 1][Cj].G)//����G������ ���� ����� G���� �۴ٸ�
				{
					_tile[Ci - 1][Cj].G = Cg + 10;//G�� ���Ӱ� ���
					_tile[Ci - 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj!=0)//�»�� : 0��° ���� �ƴ϶��
		{
			//�»�� Ÿ���� �����̳� �Ʒ��� ���� ���ٸ�
			if (_tile[Ci - 1][Cj - 1].walkable && _tile[Ci][Cj].walkable && _tile[Ci][Cj - 1].walkable)
			{
				if (!_tile[Ci - 1][Cj - 1].listOn)
				{
					_tile[Ci - 1][Cj - 1].listOn = true;
					_tile[Ci - 1][Cj - 1].color = RGB(220, 255, 220);
					_tile[Ci - 1][Cj - 1].G = Cg + 14;//�밢�� �̹Ƿ�
					_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj - 1].G)
					{
						_tile[Ci - 1][Cj - 1].G = Cg + 14;
						_tile[Ci - 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		if (Cj != TILE_X - 1)//���� :  ���������� �ƴ϶��
		{
			//���� Ÿ���� �����̳� �Ʒ��� ���� ���ٸ�
			if (_tile[Ci - 1][Cj + 1].walkable && _tile[Ci - 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)
			{
				if (!_tile[Ci - 1][Cj + 1].listOn)
				{
					_tile[Ci - 1][Cj + 1].listOn = true;
					_tile[Ci - 1][Cj + 1].color = RGB(220, 255, 220);
					_tile[Ci - 1][Cj + 1].G = Cg + 14;
					_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci - 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci - 1][Cj + 1].G)
					{
						_tile[Ci - 1][Cj + 1].G = Cg + 14;
						_tile[Ci - 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
	if (Cj != 0)//���� : 0��° ���� �ƴ϶��
	{
		//����Ÿ���� �̵������ϴٸ�
		if (_tile[Ci][Cj - 1].walkable)
		{
			if (!_tile[Ci][Cj - 1].listOn)
			{
				_tile[Ci][Cj - 1].listOn = true;
				_tile[Ci][Cj - 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj - 1].G = Cg + 10;
				_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj - 1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj - 1].G)
				{
					_tile[Ci][Cj - 1].G = Cg + 10;
					_tile[Ci][Cj - 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Cj != TILE_X - 1)//���� :���������� �ƴ϶��
	{
		if (_tile[Ci][Cj + 1].walkable)//����Ÿ���� �̵������ϴٸ�
		{
			if (!_tile[Ci][Cj + 1].listOn)
			{
				_tile[Ci][Cj + 1].listOn = true;
				_tile[Ci][Cj + 1].color = RGB(220, 255, 220);
				_tile[Ci][Cj + 1].G = Cg + 10;
				_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci][Cj + 1]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci][Cj + 1].G)
				{
					_tile[Ci][Cj + 1].G = Cg + 10;
					_tile[Ci][Cj + 1].parent = _closeList[_lastIndex];
				}
			}
		}
	}
	if (Ci != TILE_Y - 1)//������ ���� �ƴ϶�� �ϴ� ���� ���
	{
		if (_tile[Ci + 1][Cj].walkable)//�ϴ� ��� Ÿ���� �̵������ϴٸ�
		{
			if (!_tile[Ci + 1][Cj].listOn)
			{
				_tile[Ci + 1][Cj].listOn = true;
				_tile[Ci + 1][Cj].color = RGB(220, 255, 220);
				_tile[Ci + 1][Cj].G = Cg + 10;
				_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				_openList.push_back(&_tile[Ci + 1][Cj]);
			}
			else
			{
				if (Cg + 10 < _tile[Ci + 1][Cj].G)
				{
					_tile[Ci + 1][Cj].G = Cg + 10;
					_tile[Ci + 1][Cj].parent = _closeList[_lastIndex];
				}
			}
		}
		if (Cj != 0)//���ϴ� : 0��° ���� �ƴ϶��
		{
			//���ϴ� Ÿ���� �������̳� ���� ���� ���ٸ�
			if (_tile[Ci + 1][Cj - 1].walkable && _tile[Ci + 1][Cj].walkable && _tile[Ci][Cj - 1].walkable)
			{
				if (!_tile[Ci + 1][Cj - 1].listOn)
				{
					_tile[Ci + 1][Cj - 1].listOn = true;
					_tile[Ci + 1][Cj - 1].color = RGB(220, 255, 220);
					_tile[Ci + 1][Cj - 1].G = Cg + 14;
					_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj - 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj - 1].G)
					{
						_tile[Ci + 1][Cj - 1].G = Cg + 14;
						_tile[Ci + 1][Cj - 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
		if (Cj != TILE_X - 1)//���ϴ� :������ ���� �ƴ϶��
		{
			//���ϴ� Ÿ���� �������̳� ���� �̵������ϴٸ�
			if (_tile[Ci + 1][Cj + 1].walkable && _tile[Ci + 1][Cj].walkable && _tile[Ci][Cj + 1].walkable)
			{
				if (!_tile[Ci + 1][Cj + 1].listOn)
				{
					_tile[Ci + 1][Cj + 1].listOn = true;
					_tile[Ci + 1][Cj + 1].color = RGB(220, 255, 220);
					_tile[Ci + 1][Cj + 1].G = Cg + 14;
					_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					_openList.push_back(&_tile[Ci + 1][Cj + 1]);
				}
				else
				{
					if (Cg + 14 < _tile[Ci + 1][Cj + 1].G)
					{
						_tile[Ci + 1][Cj + 1].G = Cg + 14;
						_tile[Ci + 1][Cj + 1].parent = _closeList[_lastIndex];
					}
				}
			}
		}
	}
}

void Astar::caculateH()
{
	for (size_t i = 0; i < _openList.size(); i++)
	{
		int vertical = (_endX - _openList[i]->j) * 10;//����H
		int horizontal = (_endY - _openList[i]->i) * 10;//����H

		if (vertical < 0)vertical *= -1;
		if (horizontal < 0)horizontal *= -1;

		_openList[i]->H = vertical + horizontal;
	}
}

void Astar::caculateF()
{
	for (size_t i = 0; i < _openList.size(); i++)
	{
		_openList[i]->F = _openList[i]->G + _openList[i]->H;
	}
}

void Astar::addCloseList()
{
	if (_openList.size() == 0)
	{
		_astarState = ASTAR_STATE::ASTAR_STATE_NOWAY;
		return;
	}
	int index = 0;
	int lowest = BIGNUM;

	for (size_t i = 0; i < _openList.size(); i++)
	{
		if (_openList[i]->F < lowest)
		{
			lowest = _openList[i]->F;
			index = i;
		}
	}


	_openList[index]->color = RGB(180, 180, 255);
	_closeList.push_back(_openList[index]);
	_openList.erase(_openList.begin() + index);//���� ����Ʈ�� �߰��� Ÿ���� ���¸���Ʈ���� ����
	_lastIndex++;//���� ���߿� �߰��� Ŭ������ �ε���

}

void Astar::checkArrive()
{
	//Ŭ���� ����Ʈ�� i,j�� ���������� ���ٸ�
	if (_closeList[_lastIndex]->i == _endY && _closeList[_lastIndex]->j == _endX)
	{
		_astarState = ASTAR_STATE::ASTAR_STATE_FOUND;
		_closeList[_lastIndex]->color = RGB(255, 100, 100);
		showWay(_closeList[_lastIndex]);
	}
}

void Astar::showWay(aStarTile* tile)
{
	if (!(tile->i == _endY && tile->j == _endX))//���������� �ƴ϶��
		tile->color = RGB(255, 180, 180);
	tile = tile->parent;	//Ÿ���� �θ� �����ؼ� showWay�Լ��� �ٽ� �ִ´�.

	if (tile->parent == NULL)
		return;
	else
		showWay(tile);


}

void Astar::typeColor(TILE_TYPE type)
{
	switch (type)
	{
		case TILE_TYPE::TILE_TYPE_EMPTY:_selectedTypeColor = RGB(255, 255, 255);break;
		case TILE_TYPE::TILE_TYPE_START:_selectedTypeColor = RGB(100, 255, 100);break;
		case TILE_TYPE::TILE_TYPE_END:_selectedTypeColor = RGB(255, 0, 0);break;
		case TILE_TYPE::TILE_TYPE_WALL:_selectedTypeColor = RGB(255, 255, 0);break;
	}
}
