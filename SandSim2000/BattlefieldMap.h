#pragma once

#include "GameState.h"
#include "SFML/Graphics.hpp"

struct BattlefielTileHeights
{
	BattlefielTileHeights(int h, int n, int s, int e, int w) : height(h), north(n), south(s), east(e), west(w) {}
	BattlefielTileHeights() : height(0), north(0), south(0), east(0), west(0) {}
	BattlefielTileHeights(int h) : height(h), north(h), south(h), east(h), west(h) {}
	int height;
	int north; int south; int east; int west;
};

class BattlefieldMap
{
public:
	BattlefieldMap(GameState* Gamestate) : gamestate(Gamestate) {}
	~BattlefieldMap();

	void initMap(int mapSize);

	sf::Sprite** getMap() { return SpriteMap; }
private:
	GameState* gamestate;

	int size = 0;

	int** depthMap = nullptr;
	BattlefielTileHeights** directionMap = nullptr;
	sf::Sprite** SpriteMap = nullptr;

	void initDepthMap();
	void initDirectionMap();
	void initSpriteMap();

	//testing, will print all the maps
	void DebugOutputMap();
};