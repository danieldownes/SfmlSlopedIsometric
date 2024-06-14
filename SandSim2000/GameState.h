#pragma once
#include <vector>
#include <List>

#include "BattlefieldCell.h"
#include "QuadTree.h"
#include "Agent.h"

class GameState {
public:
    std::vector<BattlefieldCell> BattlefieldVector;
    QuadTree* quadTree = nullptr;

    std::list<Agent*> Units;
};



