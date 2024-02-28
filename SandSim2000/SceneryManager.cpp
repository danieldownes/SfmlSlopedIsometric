#include "SceneryManager.h"

#define CELLSIZE 100

void SceneryManager::placeScenery(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(mouseWorldPosition);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);

    Tree tree(intEuclidianPos.x, intEuclidianPos.y);

    gameStateManager.getState().Units.push_back(tree);

    gameStateManager.getState().quadTree->insert(&tree, 100);
}


