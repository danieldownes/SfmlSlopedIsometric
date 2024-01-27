#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <list>
#include <string>

#include <iostream>

struct BattlefieldTileHeights
{
	BattlefieldTileHeights(int h, int n, int s, int e, int w, int ne, int se, int sw, int nw) : height(h), north(n), south(s), east(e), west(w), northeast(ne), southeast(se), southwest(sw), northwest(nw) {}
	BattlefieldTileHeights() : height(0), north(0), south(0), east(0), west(0), northeast(0), southeast(0), southwest(0), northwest(0) {}
	BattlefieldTileHeights(int h) : height(h), north(h), south(h), east(h), west(h), northeast(h), southeast(h), southwest(h), northwest(h) {}

	std::string evaluate() 
	{
		return std::to_string(height) + "-" + std::to_string(north) + "-" + std::to_string(northeast) + "-" + std::to_string(east) + "-" + std::to_string(southeast) + "-" + std::to_string(south) + "-" + std::to_string(southwest) + "-" + std::to_string(west) + "-" + std::to_string(northwest);
	}

	int height;
	int north; int south; int east; int west;
	int northeast; int southeast; int southwest; int northwest;
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
	BattlefieldTileHeights** directionMap = nullptr;
	sf::Texture*** textureMap = nullptr;

	std::list<std::pair<sf::Texture, std::string>> grassTextures;

	sf::Texture* getTexture(BattlefieldTileHeights heights);

	void initDepthMap();
	void initDirectionMap();
	void initTextureMap();

	//testing, will print all the maps
	void DebugOutputMap();
};