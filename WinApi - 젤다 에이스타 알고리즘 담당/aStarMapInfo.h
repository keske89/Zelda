#pragma once
#include "singletonBase.h"
#include "aStarTile.h"
#include "tile_inGame.h"
#include <map>	
#include <vector>

struct tagAStarMap
{
	int tileX;
	int tileY;
	vector<aStarTile*> vAstarTiles;
};

typedef map < string, tagAStarMap> mAStarInfo;

class aStarMapInfo	:public singletonBase<aStarMapInfo>
{

private:
	mAStarInfo _mAStarInfo;
	vector<aStarTile*>* _currentAstar;
	int _currentAStarTileX;
	int _currentAStarTileY;
	
public:
	aStarMapInfo();
	~aStarMapInfo();

	HRESULT init(string key, int xSize, int ySize, vector<tile_inGame*>* vtile);
	void update();
	void loadMapInfo();

	void changeAstar(string key) {
		auto aStar = _mAStarInfo.find(key);
		if (aStar == _mAStarInfo.end()) return;

		_currentAstar = &aStar->second.vAstarTiles;
		_currentAStarTileX = aStar->second.tileX;
		_currentAStarTileY = aStar->second.tileY;
	}

	bool canGo(int x, int y) { 
		int indexX = x / 25; 
		int indexY = y / 25; 
		if ((*_currentAstar)[indexX + indexY*_currentAStarTileX]->getIsOpen()) return true; else return false; }
	vector<aStarTile*>* getcurrentAStar() { return _currentAstar; }
	POINT getcurrentSize() { return { _currentAStarTileX,_currentAStarTileY }; }

	void settoOpen(int tileX, int tileY)
	{
		(*_currentAstar)[tileX * 2 + tileY * 2 * _currentAStarTileX]->setIsOpen(true);
		(*_currentAstar)[tileX * 2 + tileY * 2 * _currentAStarTileX +1]->setIsOpen(true);
		(*_currentAstar)[tileX * 2 + tileY * 2 * _currentAStarTileX + _currentAStarTileX]->setIsOpen(true);
		(*_currentAstar)[tileX * 2 + tileY * 2 * _currentAStarTileX + _currentAStarTileX + 1]->setIsOpen(true);
	}

	void render(HDC hdc);
};
