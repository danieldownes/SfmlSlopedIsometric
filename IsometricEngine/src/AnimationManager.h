#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "SpriteManager.h"
#include "Agent.h"

class AnimationManager
{
public:
	AnimationManager() {}
	~AnimationManager() {}

	sf::Sprite getAgentSpriteFromDirection(Agent* agent);
private:
	sf::Vector2i directions[9] = {
		sf::Vector2i(-1, 0),
		sf::Vector2i(-1, -1),
		sf::Vector2i(0, -1),
		sf::Vector2i(-1, 1),
		sf::Vector2i(-1, 1),
		sf::Vector2i(1, -1),
		sf::Vector2i(0, 1),
		sf::Vector2i(1, 1),
		sf::Vector2i(1, 0)
	};

	int getIndexFromDirection(sf::Vector2i direction);
};

