#pragma once
#include <vector>
#include "BattlefieldCell.h"
#include "QuadTree.h"

class GameState {
public:
    std::vector<BattlefieldCell> BattlefieldVector;
    QuadTree* quadTree = nullptr;
};



