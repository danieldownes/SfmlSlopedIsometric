#pragma once
#include <vector>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "GridGenerator.h"
#include "GameState.h"
#include "MapInfo.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	void renderSpriteMap(sf::RenderWindow* window);
	void renderTerrainMap(sf::RenderWindow* window, GameState* gameState);
private:
	void initializeDefaultTerrainTexure();

	std::vector<sf::Sprite> spriteMap;
	sf::Texture defaultTerrainTexture;
};

