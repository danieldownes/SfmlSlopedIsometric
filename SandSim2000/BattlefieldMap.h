#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <list>
#include <string>

#include <iostream>

enum Direction
{
	F, N, NE, E, SE, S, SW, W, NW
};

class BattlefieldMap
{
public:
	BattlefieldMap() {}
	~BattlefieldMap();

	void initMap(unsigned int mapSize);

	sf::Texture*** getMap() { return textureMap; }
	sf::Texture* getTextureAtPosition(sf::Vector2i position) { return textureMap[position.y][position.x]; std::cout << position.x << ":" << position.y << "\n"; }

	int getHeightAtPosition(sf::Vector2i position) { return depthMap[position.y][position.x]; }
private:
	int size = 0;

	int** depthMap = nullptr;
	Direction** directionMap = nullptr;
	sf::Texture*** textureMap = nullptr;

	std::list<std::pair<sf::Texture, std::string>> grassTextures;

	sf::Texture* getTexture(Direction direction);
	std::string evaluateDirection(Direction dir);

	void initDepthMap();
	void initDirectionMap();
	void initTextureMap();

	int testLocation(int x, int y, int height);

	//testing, will print all the maps
	void DebugOutputMap();
};