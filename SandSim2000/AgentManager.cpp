#include "AgentManager.h"

/*                        +++++++++++++ Agent Manager +++++++++++++                             */
/* Method: UpdateImpassableTerrainNodes - Sets selected nodes as impassable terrain             */
/* Method: PropagateWaveFrontHeuristics - Sets heuristics for nodes in a wave out from target   */
/* Method: AStar - Performs main loop of AStar on a grid with heuristics preset from WFP        */
/* Method: ExploreNeighbours - Neighbours of current cell passed to it                          */
/* Method: ReconstructPath - Builds list of path nodes based on parent nodes in path            */
/*                        +++++++++++++ Debug Methods +++++++++++++                             */
/* Method: PrintGhostGrid - Prints the ghost grid, has commented out code to print the hScore   */
/*             +++++++++++++     +++++++++++++        +++++++++++++                             */

void AgentManager::onUpdate(
    InputState& state,
    std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
    GameStateManager& gameStateManager,
    Camera& camera,
    Scene& scene)
{

    if (pathfinderAgent != nullptr)
    {
        pathfinderAgent->update();
    }

    if (state.isLeftMouseButtonPressed && leftClick == false)
    {
        
        BattlefieldCell* targetCell = gameStateManager.getState().quadTree->getCell(gameStateManager.state.quadTree, state.selectedCell.x * 100, state.selectedCell.y * 100, 4);
        
        movementManager.SetUnitPath(pathfinderAgent, targetCell, &gameStateManager, state, scene, &camera);



        leftClick = true;
    }
    else if (state.isRightMouseButtonPressed && rightClick == false)
    {
        rightClick = true;
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


void AgentManager::placeScenery(sf::Vector2i isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery sceneObject, GameStateManager& gameStateManager)
{
    if (sceneObject.getUnitType() == "Tree")
    {
        Tree* tree = new Tree(isometricCell.x, isometricCell.y);

        gameStateManager.getState().Units.push_back(tree);
        gameStateManager.getState().quadTree->insert(tree, 100);

        BattlefieldCell* cell = gameStateManager.getCell(isometricCell.x, isometricCell.y);

        if (cell != nullptr)
            cell->impassableTerrain = true;
    }
}

void AgentManager::placeAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Agent agent, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(cell);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);


    Agent* newAgent = new Agent(agent);

    gameStateManager.getState().Units.push_back(newAgent);
    gameStateManager.getState().quadTree->insert(newAgent, 100);
}

void AgentManager::placePathfinderAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gamesScene, PathfinderAgent agent, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(cell);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);

    PathfinderAgent* newAgent = new PathfinderAgent(agent);
    newAgent->setStartingCell(gameStateManager.getState().quadTree->getCell(gameStateManager.getState().quadTree, intEuclidianPos.x * 100, intEuclidianPos.y * 100, 4));

    gameStateManager.getState().Units.push_back(newAgent);
    gameStateManager.getState().quadTree->insert(newAgent, 100);
    pathfinderAgent = newAgent;
}