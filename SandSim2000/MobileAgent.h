#pragma once

#include <vector>

#include "SFML/System.hpp"

#include "GlobalConstants.h"
#include "Agent.h"
#include "GameStateManager.h"
#include "PathfinderAgent.h"

class MobileAgent : public Agent
{
public:
	MobileAgent(int initialPosX, int initialPosY, int initialHealth, int initialArmour, int initialSpeed, int initialBallisticSkill, bool directional, sf::String basicUnitType) : Agent(initialPosX, initialPosY, initialHealth, initialArmour, initialSpeed, initialBallisticSkill, directional, basicUnitType) {}

	void update(GameStateManager* gameStateManager);
private:
	std::vector<Agent*> nearbyAgents;
	sf::Vector2f velocity;
	PathfinderAgent* pathfinderAgent;

	void Coherence();
	void seperation();
	void Alignment();

	PathfinderAgent* getPathfinderFromList();
	GlobalConstants constants;
};

