#include "AgentManager.h"
#include <typeinfo>

#define CELLSIZE 100

void AgentManager::onUpdate(
    InputState& state, 
    std::set<std::vector<BattlefieldCell>::iterator>* gameScene, 
    GameStateManager& gameStateManager, 
    Camera& camera, 
    Scene& scene)
{
    if (state.isLeftMouseButtonPressed && leftClick == false)
    {

        Tree tree(0,0);

        placeScenery(camera.selectedCell, &scene.gameScene, tree, gameStateManager);

        leftClick = true;
    }
    else if (state.isRightMouseButtonPressed && rightClick == false) 
    {
        Agent baron(10, 10, -1, -1, -1, -1, "RedBaron");

        placeAgent(camera.selectedCell, &scene.gameScene, baron, gameStateManager);

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


void AgentManager::placeScenery(sf::Vector2f isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery sceneObject, GameStateManager& gameStateManager)
{
    if (sceneObject.getUnitType() == "Tree")
    {
        Tree tree = Tree(isometricCell.x, isometricCell.y);
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