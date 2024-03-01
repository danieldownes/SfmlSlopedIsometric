#include "SceneryManager.h"
#include <typeinfo>

#define CELLSIZE 100

// Josh: I've changed this so it reads directly from the InputState, the InputStateManager is only 
// for write/update/delete actions, reading should happen directly. Please check the InputStateManager.cpp
// for another comment. 
void SceneryManager::onUpdate(
    const InputState& state, 
    std::set<std::vector<BattlefieldCell>::iterator>* gameScene, 
    GameStateManager& gameStateManager, 
    Camera& camera, 
    Scene& scene)
{
    if (state.isLeftMouseButtonPressed && leftClick == false)
    {
        sf::Vector2i mousepos = state.mousePosition;

        float x; float y;

        camera.ScreenToWorld(mousepos.x, mousepos.y, x, y);

        Tree tree(10, 10);

        placeScenery(sf::Vector2f(x, y), &scene.gameScene, tree, gameStateManager);

        leftClick = true;
    }
    else if (state.isLeftMouseButtonPressed == false)
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


