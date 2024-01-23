#pragma once
#include "GameState.h"
#include "BattlefieldCell.h"


class GameStateManager {
public:
    GameStateManager();

    //void initialiseQuadTree() etc

    void initializeBattlefieldVector(int numCells);
private:
    GameState state;
};
