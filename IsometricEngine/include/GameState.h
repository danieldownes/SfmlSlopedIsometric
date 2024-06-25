#pragma once
#include <List>
#include <vector>

#include "Agent.h"
#include "BattlefieldCell.h"
#include "QuadTree.h"

class GameState
{
   public:
	std::vector<BattlefieldCell> BattlefieldVector;
	QuadTree* quadTree = nullptr;

	std::list<Agent*> Units;
};
