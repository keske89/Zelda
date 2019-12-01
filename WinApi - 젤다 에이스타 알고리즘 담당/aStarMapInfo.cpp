#include "stdafx.h"
#include "aStarMapInfo.h"


aStarMapInfo::aStarMapInfo()
{
}


aStarMapInfo::~aStarMapInfo()
{
}

HRESULT aStarMapInfo::init(string key,int xSize, int ySize, vector<tile_inGame*>* vtile)
{
	tagAStarMap tempAstarMap;

	tempAstarMap.tileX = xSize*2;
	tempAstarMap.tileY = ySize*2;
	
	POINT _index;
	_index.x = xSize;
	_index.y = ySize;
	for (int i = 0; i < _index.y*2; i++)
	{
		for (int j = 0; j < _index.x*2; j++)
		{
			aStarTile* tempAstar = new aStarTile;

			tile_inGame* temp = (*vtile)[i/2*_index.x + j/2];
			
			tempAstar->setIdX(j);
			tempAstar->setIdY(i);
			tempAstar->setIsOpen(true);

			if (temp->getiGOBJ().OBJ_INDEX != OBJECT_NONE)
			{
				tempAstar->setIsOpen(false);
				tempAstar->setAttribute("wall");
				tempAstarMap.vAstarTiles.push_back(tempAstar);
				continue;
			}
			if (temp->getWeight() != 0)
			{
				if (j % 2 == 0 && i % 2 == 0)   
				{
					if (temp->getWeight() % 2 == 1)
					{
						tempAstar->setIsOpen(false);
						tempAstar->setAttribute("wall");
					}
				}
				if (j % 2 == 1 && i % 2 == 0)
				{
					if((temp->getWeight()- temp->getWeight()%2)%4/2 ==1)
					{
						tempAstar->setIsOpen(false);
						tempAstar->setAttribute("wall");
					}
				}
				if (j % 2 == 0 && i % 2 == 1)
				{
					if ((temp->getWeight() - temp->getWeight() % 4) % 8 / 4 == 1)
					{
						tempAstar->setIsOpen(false);
						tempAstar->setAttribute("wall");
					}
				}
				if (j % 2 == 1 && i % 2 == 1)
				{
					if ((temp->getWeight() - temp->getWeight() % 8) % 16 / 8 == 1)
					{
						tempAstar->setIsOpen(false);
						tempAstar->setAttribute("wall");
					}
				}
			}
			tempAstarMap.vAstarTiles.push_back(tempAstar);
		}
	}

	

	_mAStarInfo.insert(make_pair(key, tempAstarMap));


	return S_OK;
}
void aStarMapInfo::update()		 
{
}
void aStarMapInfo::loadMapInfo() 
{
}

void aStarMapInfo::render(HDC hdc)
{
	for (int i = 0; i < (*_currentAstar).size(); ++i)
	{
		HBRUSH hob, hb;
		HPEN hp, hop;
		hb = (HBRUSH)GetStockObject(NULL_BRUSH);
		hob = (HBRUSH)SelectObject(hdc, hb);
		if ((*_currentAstar)[i]->getIsOpen())
			hp = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		else
			hp = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hop = (HPEN)SelectObject(hdc, hp);

		RectangleMake(hdc, (*_currentAstar)[i]->getIdX() * 25- CAMERAMANAGER->getCameraPoint().x, (*_currentAstar)[i]->getIdY() * 25 - CAMERAMANAGER->getCameraPoint().y, 25, 25);

		SelectObject(hdc, hop);
		SelectObject(hdc, hob);
		DeleteObject(hp);
		DeleteObject(hb);

	}
}
