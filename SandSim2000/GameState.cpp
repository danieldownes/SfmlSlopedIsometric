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

    map = new QuadTreeInternal(sf::FloatRect(0, 0, mapSize * 100, mapSize * 100), 0);

    ((QuadTreeInternal*)map)->createChildren();
    std::array<QuadTree*, 4> children = ((QuadTreeInternal*)map)->getChildren();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            terrain[j].z = 1;
            terrain[j].height = rand() % 3;
            terrain[j].facing = 0.0f;
            terrain[j].terrain = "default";
        }
        ((QuadTreeInternal*)children[i])->createChildren(terrain);
    }
}
