#include "SceneryManager.h"
#include <typeinfo>

#define CELLSIZE 100

// Josh: please "listen" to the inputState in this class. It's important to handle events based on the InputState and not Event due to storing input
// states across frames. So please "listen" to the input state in this class and place scenery (Tree in this case) based on the bool isLeftMouseButtonPressed;
// and bool isRightMouseButtonPressed; properties of the InputState.

void SceneryManager::placeScenery(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(mouseWorldPosition);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);

    if (scenObject.getUnitType() == "Tree")
    {
        Tree tree = Tree(intEuclidianPos.x, intEuclidianPos.y);

        gameStateManager.getState().Units.push_back(tree);

        gameStateManager.getState().quadTree->insert(&tree, 100);
    }
}


