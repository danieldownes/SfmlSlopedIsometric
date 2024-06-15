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


        std::vector<Agent*> agents = std::vector<Agent*>();
        sf::Clock timer;
        gameStateManager.getState().quadTree->getAgentsInRadius(gameStateManager.getState().quadTree, pathfinderAgent->getPosX() * 100, pathfinderAgent->getPosY() * 100, 300, 5, &agents);
        std::cout << timer.getElapsedTime().asMicroseconds() << std::endl;

        for (int i = 0; i < agents.size(); i++)
            std::cout << agents[i]->getUnitType() << "\n";
    }

    if (state.isLeftMouseButtonPressed && leftClick == false)
    {
        
        BattlefieldCell* targetCell = gameStateManager.getState().quadTree->getCell(gameStateManager.state.quadTree, state.selectedCell.x * 100, state.selectedCell.y * 100, 4);
        
        movementManager.SetUnitPath(pathfinderAgent, targetCell, &gameStateManager, state, scene);


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
        gameStateManager.getState().quadTree->insert(tree, constants.cellSize);

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
    gameStateManager.getState().quadTree->insert(newAgent, constants.cellSize);
}

void AgentManager::placePathfinderAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gamesScene, PathfinderAgent agent, GameStateManager& gameStateManager)
{
    BattlefieldCell* currentCell = gameStateManager.getCell(cell.x, cell.y);

    PathfinderAgent* newAgent = new PathfinderAgent(agent);
    newAgent->setStartingCell(gameStateManager.getState().quadTree->getCell(gameStateManager.getState().quadTree, cell.x * constants.cellSize, cell.y * constants.cellSize, constants.quadTreeDepth));


    gameStateManager.getState().Units.push_back(newAgent);
    gameStateManager.getState().quadTree->insert(newAgent, constants.cellSize);

    pathfinderAgent = newAgent;
    pathfinderAgent->current = currentCell;
}