#pragma once
#include "MapInfo.h"
#include "QuadTree.h"
#include <time.h>
#include <cmath>

class GameState
{
public:
	GameState();
	~GameState();

	QuadTree* getMapData() { return map; }
	void clearAndInitializeMap();

	static const int mapSize = 8;
private:
	void generateRandomHeightQuadTreeMap(QuadTreeInternal* node);

	QuadTree* map = nullptr;
};

