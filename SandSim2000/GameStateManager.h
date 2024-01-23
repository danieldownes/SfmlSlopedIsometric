#pragma once
#include "GameState.h"
#include "BattlefieldCell.h"


class GameStateManager {
public:
    GameStateManager(unsigned int mapSize);

    void initialiseQuadTree(unsigned int battlefieldSize);
    void initializeBattlefieldVector(unsigned int numCells);

    GameState& getState() { return state; }
private:
    void generateQuadTree(QuadTreeInternal* root);

    GameState state;
};
