#include "MobileAgent.h"

void MobileAgent::update(GameStateManager* gameStateManager)
{
	nearbyAgents = std::vector<Agent*>();

	gameStateManager->state.quadTree->getAgentsInRadius(gameStateManager->state.quadTree, getPosX() * constants.cellSize, getPosY() * constants.cellSize, constants.cellSize * 2, constants.quadTreeDepth, &nearbyAgents);

	std::cout << nearbyAgents.size() << "\n";

	pathfinderAgent = getPathfinderFromList();
	if (pathfinderAgent != nullptr)
		std::cout << "Found Pathfinder\n";
	else
		std::cout << "found nothing\n";
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