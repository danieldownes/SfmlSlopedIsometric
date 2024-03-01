#include "SceneryManager.h"
#include <typeinfo>

#define CELLSIZE 100

void SceneryManager::onUpdate(std::set<std::vector<BattlefieldCell>::iterator>* gameScene, GameStateManager& gameStateManager, Camera& camera, Scene& scene)
{
    InputState state2 = InputStateManager::getInstance().getInputState();
    if (state2.isLeftMouseButtonPressed && leftClick == false)
    {
        sf::Vector2i mousepos = InputStateManager::getInstance().getInputState().mousePosition;

        float x; float y;

        camera.ScreenToWorld(mousepos.x, mousepos.y, x, y);

        Tree tree(10, 10);

        placeScenery(sf::Vector2f(x, y), &scene.gameScene, tree, gameStateManager);

        leftClick = true;
    }
    else if (state2.isLeftMouseButtonPressed == false)
    {
        leftClick = false;
    }
}

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


