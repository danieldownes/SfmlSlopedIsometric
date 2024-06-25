#pragma once

#include <vector>
#include <cmath>

#include "SFML/System.hpp"

#include "GlobalConstants.h"
#include "Agent.h"
#include "GameStateManager.h"
#include "PathfinderAgent.h"

class MobileAgent : public Agent
{
public:
	MobileAgent(int initialPosX, int initialPosY, int initialHealth, int initialArmour, float initialSpeed, int initialBallisticSkill, sf::String basicUnitType) : Agent(initialPosX, initialPosY, initialHealth, initialArmour, initialSpeed, initialBallisticSkill, true, basicUnitType) { lastCellPosition = sf::Vector2i(initialPosX, initialPosY); }

	void update(GameStateManager* gameStateManager);
private:
	std::vector<Agent*> nearbyAgents;
	sf::Vector2f velocity;
	PathfinderAgent* pathfinderAgent = nullptr;

	void Coherence();
	void seperation();
	void Alignment();

	void ClampVelocity();

	void updateCurrentSpriteDirection();
	void updateCell(GameStateManager* gameStateManager);

	sf::Vector2f normalize(sf::Vector2f value);
	PathfinderAgent* getPathfinderFromList();
	GlobalConstants constants;

	sf::Vector2i lastCellPosition;
};

