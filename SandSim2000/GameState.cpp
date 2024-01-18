#include "GameState.h"
#include <time.h>

GameState::GameState()
{
    clearAndInitializeMap();
}

GameState::~GameState()
{
}

void GameState::clearAndInitializeMap()
{
    delete map;

    srand(time(NULL));

    std::array<TerrainTile, 4> terrain;

    int depth = 0;

    map = new QuadTreeInternal(sf::FloatRect(0, 0, mapSize * 100, mapSize * 100), depth);

    ((QuadTreeInternal*)map)->createChildren();
    std::array<QuadTree*, 4> children = ((QuadTreeInternal*)map)->getChildren();

    for (QuadTree* child : children) {
        for (int i = 0; i < 4; i++) {
            terrain[i].z = 1;
            terrain[i].height = rand() % 3;
            terrain[i].facing = 0.0f;
            terrain[i].terrain = "default";
        }
        ((QuadTreeInternal*)child)->createChildren(terrain);
    }
}
