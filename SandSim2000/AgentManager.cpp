#include "AgentManager.h"


#define CELLSIZE 100

void AgentManager::onUpdate(
    InputState& inputState, 
    std::set<std::vector<BattlefieldCell>::iterator>* gameScene, 
    GameStateManager& gameStateManager, 
    Camera& camera, 
    Scene& scene)
{
    if (inputState.isLeftMouseButtonPressed && leftClick == false)
    {

        Tree tree(0,0);

        placeScenery(inputState.selectedCell, &scene.gameScene, tree, gameStateManager);

        leftClick = true;
    }
    else if (inputState.isRightMouseButtonPressed && rightClick == false)
    {
        Agent baron(10, 10, -1, -1, -1, -1, "RedBaron");

        placeAgent(camera.selectedCell, &scene.gameScene, baron, gameStateManager);

        leftClick = true;
    }
    else if (inputState.isLeftMouseButtonPressed == false)
    {
        leftClick = false;
    }
    else if (inputState.isRightMouseButtonPressed == false)
    {
        rightClick = false;
    }
}


void AgentManager::placeScenery(sf::Vector2i selectedCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery sceneObject, GameStateManager& gameStateManager)
{
    if (sceneObject.getUnitType() == "Tree")
    {
        Tree tree = Tree(selectedCell.x, selectedCell.y);
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