#include "GameStateManager.h"

GameStateManager::GameStateManager() {}

/*
void GameStateManager::initialiseQuadTree() {
    
    Sam the quad tree should be a member property of 
    the GameState and the GameStateManager should be 
    where it's initialised. 
}
*/

void GameStateManager::initializeBattlefieldVector(int numCells) {
    state.BattlefieldVector.resize(numCells);
    for (int i = 0; i < numCells; ++i) {
        // Initialise the attributes of each BattlefieldCell 
        // then place them into the BattlefieldVector
    }

    //Update the GameState with the new BattlefieldVector
}

