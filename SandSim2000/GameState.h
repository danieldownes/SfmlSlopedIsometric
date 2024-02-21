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

    // Alpha Team Suggestion: Move this list of Agent objects to the BattlefieldCell. 
    // This will allow multiple Agent Objects to be stored within the same leaf node in the 
    // quad tree at the same time.
    std::list<Agent> Units;
};



