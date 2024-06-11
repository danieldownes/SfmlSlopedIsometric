#include "PathfinderAgent.h"

#include <iostream>

void PathfinderAgent::setPath(std::vector<BattlefieldCell*>* TargetPath)
{
	path = std::vector<BattlefieldCell*>();
	for (int i = 0; i < TargetPath->size(); i++)
	{
		BattlefieldCell* next = TargetPath->at(i);
		path.push_back(TargetPath->at(i));
	}
	atDestination = false;
}

void PathfinderAgent::update()
{
	if (atDestination == false && timer.getElapsedTime().asSeconds() > movementCooldown)
	{
		BattlefieldCell* nextCell = path[0];
		posX = nextCell->x; posY = nextCell->y;

		if (current != nullptr)
			current->removeObject(this);

		path.erase(path.begin());

		current = nextCell;
		current->addObject(this);

		if (path.size() == 0)
			atDestination = true;
		std::cout << "Agent Position: " << getUnitType() << "\n";

		timer.restart();
	}
}