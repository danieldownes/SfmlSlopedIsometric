#pragma once
#include <cmath>
#include <set>

#include "GameState.h"
#include "BattlefieldMap.h"
#include "BattlefieldCell.h"
#include "Agent.h"
#include "InputStateManager.h"
#include "GridGenerator.h"


class GameStateManager {
public:
    GameStateManager(unsigned int numCells);

    void initialiseQuadTree(unsigned int battlefieldSize, unsigned int& index);
    void initializeBattlefieldVector(unsigned int numCells);
    void placeUnit(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, sf::String unitType);

    GameState& getState() { return state; }
private:
    void generateQuadTree(QuadTree* root, unsigned int& index);
    BattlefieldCell generateCell(int x, int y);

    BattlefieldMap battlefieldMap;
    GameState state;
};
  