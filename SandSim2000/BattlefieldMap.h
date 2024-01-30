#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "spritesheet.h"

enum Direction
{
	//Liam: The way you had the direction sequence was correct, I've just swapped W/E because it was faster to test than changing the sprite sheet.
	//I'll put it back once we're ready to PR this task. 
	F, N, NE, W, SE, S, SW, E, NW
};

class BattlefieldMap
{
public:
	BattlefieldMap() {}
	~BattlefieldMap();

	void initMap(unsigned int mapSize);

	sf::Sprite* getSpriteAtPosition(sf::Vector2i position) {
		return spriteMap[position.y][position.x]; 
	}

	int getHeightAtPosition(sf::Vector2i position) { return depthMap[position.y][position.x]; }
private:
	int size = 0;

	int** depthMap = nullptr;
	Direction** directionMap = nullptr;
	sf::Sprite*** spriteMap = nullptr;

	std::list<std::pair<sf::Texture, std::string>> grassTextures;

	spritesheet grass_spritesheet;

	void initDepthMap();
	void initDirectionMap();
	void initSpriteMap();

	int testLocation(int x, int y, int height);
};