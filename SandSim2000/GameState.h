#pragma once
#include <time.h>
#include <cmath>
#include "QuadTree.h"
#include "BattlefieldCell.h"

class GameState
{
public:
	GameState();
	~GameState();


	// GameState is purely a storage header, no logic. A.k.a. a Singleton. 
	// Please move all logic to GameStateManager and delete GameState.cpp
	QuadTree* getMapData() { return map; }
	void clearAndInitializeMap(); 
	static const int mapSize = 256;

	std::vector<BattlefieldCell> BattlefieldVector;

private:


	void generateRandomHeightQuadTreeMap(QuadTreeInternal* node);
	
	// Quad Tree should be stored publically like BattlefieldCell
	// If possible, should also be a member property of GameState, 
	// not it's own class.
	QuadTree* map = nullptr;
};

