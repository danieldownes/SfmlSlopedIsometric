#include "MobileAgent.h"

void MobileAgent::update(GameStateManager* gameStateManager)
{

	nearbyAgents = std::vector<Agent*>();

	gameStateManager->state.quadTree->getAgentsInRadius(gameStateManager->state.quadTree, getPosX() * constants.cellSize, getPosY() * constants.cellSize, constants.cellSize * 2, constants.quadTreeDepth, &nearbyAgents);
	
	if(pathfinderAgent == nullptr)
		pathfinderAgent = getPathfinderFromList();

	Coherence();

	posX += velocity.x; posY += velocity.y;

	updateCurrentSpriteDirection();
	updateCell(gameStateManager);
}

PathfinderAgent* MobileAgent::getPathfinderFromList()
{
	for (int i = 0; i < nearbyAgents.size(); i++)
	{
		if (nearbyAgents[i]->isPathfinderAgent)
			return dynamic_cast<PathfinderAgent*>(nearbyAgents[i]);
	}
	return nullptr;
}

void MobileAgent::Coherence()
{
	velocity.x = (pathfinderAgent->getPosX() - getPosX()) * 0.1f;
	velocity.y = (pathfinderAgent->getPosY() - getPosY()) * 0.1f;
}

void MobileAgent::updateCurrentSpriteDirection()
{
	float spriteBarrier = 0.01f;

	if (velocity.x > spriteBarrier) currentDirection.x = 1;
	if (velocity.x < -spriteBarrier) currentDirection.x = -1;

	if (velocity.y > spriteBarrier) currentDirection.y = 1;
	if (velocity.y < -spriteBarrier) currentDirection.y = -1;

	if (velocity.x > -spriteBarrier && velocity.x < spriteBarrier) { velocity.x = 0; }
	if (velocity.y > -spriteBarrier && velocity.y < spriteBarrier) { velocity.y = 0; }

	if (velocity.x == 0 && velocity.y != 0) currentDirection.x = 0;
	if (velocity.x != 0 && velocity.y == 0) currentDirection.y = 0;
}

void MobileAgent::updateCell(GameStateManager* gameStateManager)
{
	if (lastCellPosition != sf::Vector2i(getPosXIndex(), getPosYIndex()))
	{
		gameStateManager->getCell(lastCellPosition.x, lastCellPosition.y)->removeObject(this);
		gameStateManager->getCell(getPosXIndex(), getPosYIndex())->addObject(this);
	}
	lastCellPosition = sf::Vector2i(getPosXIndex(), getPosYIndex());
}