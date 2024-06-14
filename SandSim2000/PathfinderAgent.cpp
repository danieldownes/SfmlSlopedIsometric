#include "PathfinderAgent.h"

#include <iostream>

void PathfinderAgent::setPath(std::vector<BattlefieldCell*>* TargetPath)
{
	path = std::vector<BattlefieldCell*>();
	for (int i = 0; i < TargetPath->size(); i++)
	{
		path.push_back(TargetPath->at(i));
	}
	atDestination = false;
}

void PathfinderAgent::update()
{
	if (atDestination == false && clock.getElapsedTime().asSeconds() >= 1 / movesPerSecond)
	{
		BattlefieldCell* nextCell = path[0];

		currentDirection = sf::Vector2i(nextCell->x - posX, nextCell->y - posY);
		posX = nextCell->x; posY = nextCell->y;

		if (current != nullptr) 
		{
			current->removeObject(this);
			std::cout << current->Objects.size() << " - removed from this" << std::endl;
		}


		path.erase(path.begin());

		current = nextCell;
		current->addObject(this);

		if (path.size() == 0)
			atDestination = true;

		clock.restart();
	}
}