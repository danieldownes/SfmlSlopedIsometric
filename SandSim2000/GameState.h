#pragma once
#include <time.h>
#include <cmath>
#include "QuadTree.h"
#include "BattlefieldCell.h"

class GameState
{
public:
	// GameState is purely a storage header, no logic. A.k.a. a Singleton. 
	// Please move all logic to GameStateManager and delete GameState.cpp

	std::vector<BattlefieldCell> BattlefieldVector;
	QuadTree* QuadTree = nullptr;
private:
	// Quad Tree should be stored publically like BattlefieldCell
	// If possible, should also be a member property of GameState, 
	// not it's own class.
};

