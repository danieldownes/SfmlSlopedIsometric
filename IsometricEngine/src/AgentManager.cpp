#include "AgentManager.h"

void AgentManager::Update(
    float deltaTime,
    InputState& state,
    std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
    GameStateManager& gameStateManager,
    Camera& camera,
    Scene& scene)
{
    if (pathfinderAgent != nullptr)
    {
        pathfinderAgent->Update();

        std::vector<Agent*> agents = std::vector<Agent*>();
        gameStateManager.getState().quadTree->getAgentsInRadius(gameStateManager.getState().quadTree, pathfinderAgent->getPosXIndex() * 100, pathfinderAgent->getPosYIndex() * 100, 200, 4, &agents);
    }
    if (mobileAgent != nullptr)
    {
        mobileAgent->Update(deltaTime, & gameStateManager);
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

void AgentManager::placeAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
							  Agent agent, GameStateManager& gameStateManager)
{
	Agent* newAgent = new Agent(agent);

	gameStateManager.getState().Units.push_back(newAgent);
	gameStateManager.getState().quadTree->insert(newAgent, constants.cellSize);
}

void AgentManager::placeScenery(sf::Vector2i isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
				  Scenery sceneObject, GameStateManager& gameStateManager)
{
	Scenery* s = new Scenery(isometricCell.x, isometricCell.y, sceneObject.getUnitType());

	gameStateManager.getState().Units.push_back(s);

	gameStateManager.getState().quadTree->insert(s, 100);
	gameStateManager.getState().quadTree->insert(s, 100);

	BattlefieldCell* cell = gameStateManager.getCell(isometricCell.x, isometricCell.y);

	if (cell != nullptr)
		cell->impassableTerrain = true;
}

void AgentManager::placeMobileAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
									MobileAgent agent, GameStateManager& gameStateManager)
{
	MobileAgent* newAgent = new MobileAgent(agent);

	gameStateManager.getState().Units.push_back(newAgent);
	gameStateManager.getState().quadTree->insert(newAgent, constants.cellSize);

	mobileAgent = newAgent;
}

void AgentManager::placePathfinderAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gamesScene,
										PathfinderAgent agent, GameStateManager& gameStateManager)
{
	BattlefieldCell* currentCell = gameStateManager.getCell(cell.x, cell.y);

	PathfinderAgent* newAgent = new PathfinderAgent(agent);
	newAgent->setStartingCell(
		gameStateManager.getState().quadTree->getCell(gameStateManager.getState().quadTree, cell.x * constants.cellSize,
													  cell.y * constants.cellSize, constants.quadTreeDepth));

    gameStateManager.getState().Units.push_back(newAgent);
    gameStateManager.getState().quadTree->insert(newAgent, constants.cellSize);

    pathfinderAgent = newAgent;
    pathfinderAgent->current = currentCell;
}