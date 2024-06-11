#pragma once

#include "Agent.h"
#include "BattlefieldCell.h"

class PathfinderAgent : public Agent
{
public:
	PathfinderAgent(int initialPosX, int initialPosY, sf::String unit) :Agent(initialPosX, initialPosY, -1, -1, -1, -1, unit) { };

	void setStartingCell(BattlefieldCell* startingCell) { current = startingCell; }
	void setPath(std::vector<BattlefieldCell*>* TargetPath);
	void update();

	std::vector<BattlefieldCell*> path = std::vector<BattlefieldCell*>();
	BattlefieldCell* current = nullptr;
	bool atDestination = true;

	float movementCooldown = 0.4f;
	sf::Clock timer;
};