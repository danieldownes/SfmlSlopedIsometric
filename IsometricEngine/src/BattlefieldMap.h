#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SpriteManager.h"

enum Direction
{
	F, N, NE, E, SE, S, SW, W, NW
};

class BattlefieldMap
{
public:
	BattlefieldMap() {}
	~BattlefieldMap();

	sf::Sprite* getSpriteAtPosition(sf::Vector2i position) { return spriteMap[position.y][position.x]; }

	void initMap(unsigned int mapSize);
	int getHeightAtPosition(sf::Vector2i position) { return depthMap[position.y][position.x]; }
	std::vector<sf::Vector2i> getVertices(int x, int y);
	int size = 0;

private:
	int** depthMap = nullptr;
	Direction** directionMap = nullptr;
	sf::Sprite*** spriteMap = nullptr;

	SpriteSheet grass_spritesheet;

	void initDepthMap();
	void initDirectionMap();
	void initSpriteMap();

	int testLocation(int x, int y, int height);
};