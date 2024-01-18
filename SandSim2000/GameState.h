#pragma once
#include "MapInfo.h"
#include "QuadTree.h"

class GameState
{
public:
	GameState();
	~GameState();

	QuadTree* getMapData() { return map; }
	void clearAndInitializeMap();

	static const int mapSize = 4;
private:
	QuadTree* map = nullptr;
};

