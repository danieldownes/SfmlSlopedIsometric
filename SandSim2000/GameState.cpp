#include "GameState.h"

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

    map = new QuadTreeInternal(sf::FloatRect(0, 0, mapSize * 100, mapSize * 100), 0);
    generateRandomHeightQuadTreeMap((QuadTreeInternal*) map);
}

void GameState::generateRandomHeightQuadTreeMap(QuadTreeInternal* node) {
    int depth = node->getDepth();

    if (depth + 1 < (unsigned int) log2(mapSize)) {
        std::array<QuadTree*, 4> children = node->createChildren();

        for (int i = 0; i < 4; i++)
            generateRandomHeightQuadTreeMap((QuadTreeInternal*) children[i]);
    } else {
        std::array<QuadTree*, 4> children = node->createChildren({true, true, true, true});
    }
}
