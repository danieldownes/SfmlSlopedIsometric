#pragma once
#include <cmath>
#include "GameState.h"
#include "BattlefieldMap.h"
#include "BattlefieldCell.h"


class GameStateManager {
public:
    GameStateManager(unsigned int numCells);

    void initialiseQuadTree(unsigned int battlefieldSize, unsigned int& index);
    void initializeBattlefieldVector(unsigned int numCells);

    GameState& getState() { return state; }
private:
    void generateQuadTree(QuadTree* root, unsigned int& index);
    BattlefieldCell generateCell(int x, int y);

    BattlefieldMap battlefieldMap;
    GameState state;
};
  