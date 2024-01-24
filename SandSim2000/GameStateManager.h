#pragma once
#include <cmath>
#include "GameState.h"
#include "BattlefieldCell.h"


class GameStateManager {
public:
    GameStateManager(unsigned int numCells);

    void initialiseQuadTree(unsigned int battlefieldSize);
    void initializeBattlefieldVector(unsigned int numCells);

    GameState& getState() { return state; }
private:
    void generateQuadTree(QuadTree* root);

    GameState state;
};
  