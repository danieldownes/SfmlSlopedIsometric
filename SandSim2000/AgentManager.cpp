#include "AgentManager.h"
#include <typeinfo>

#define CELLSIZE 100

void AgentManager::onUpdate(
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
    else if (state.isRightMouseButtonPressed && rightClick == false)
    {
        sf::Vector2i mousepos = state.mousePosition;

        float x; float y;

        camera.ScreenToWorld(mousepos.x, mousepos.y, x, y);

        Agent baron(10, 10, -1, -1, -1, -1, "RedBaron");

        placeAgent(sf::Vector2f(x, y), &scene.gameScene, baron, gameStateManager);

        leftClick = true;
    }
    else if (state.isLeftMouseButtonPressed == false)
    {
        leftClick = false;
    }
    else if (state.isRightMouseButtonPressed == false)
    {
        rightClick = false;
    }
}


void AgentManager::placeScenery(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery sceneObject, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(mouseWorldPosition);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);

    if (sceneObject.getUnitType() == "Tree")
    {
        Tree tree = Tree(intEuclidianPos.x, intEuclidianPos.y);

        gameStateManager.getState().Units.push_back(tree);

        gameStateManager.getState().quadTree->insert(&tree, 100);
    }
}

void AgentManager::placeAgent(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Agent agent, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(mouseWorldPosition);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);

    if (agent.getUnitType() == "RedBaron")
    {
        Agent baron = Agent(intEuclidianPos.x, intEuclidianPos.y, -1, -1, -1, -1, "RedBaron");

        gameStateManager.getState().Units.push_back(baron);

        gameStateManager.getState().quadTree->insert(&baron, 100);
    }
}


