#include "PathfinderAgent.h"

#include <iostream>

void PathfinderAgent::setPath(std::vector<BattlefieldCell*>* TargetPath)
{
	path = std::vector<BattlefieldCell*>();
	if(TargetPath->size() > 1)
	{
		for (int i = 1; i < TargetPath->size(); i++)
		{
			path.push_back(TargetPath->at(i));
		}
		atDestination = false;
	}
}

void PathfinderAgent::update()
{
	if (atDestination == false && clock.getElapsedTime().asSeconds())
	{
		BattlefieldCell* nextCell = path[0];
		auto v = getPosVector2i();
		currentDirection = sf::Vector2i(nextCell->x - v.x, nextCell->y - v.y);
		posX = static_cast<float>(nextCell->x); posY = static_cast<float>(nextCell->y);

		if (current != nullptr) 
		{
			current->removeObject(this);
		}


		path.erase(path.begin());

		current = nextCell;
		current->addObject(this);

		if (path.size() == 0)
			atDestination = true;
	}
}