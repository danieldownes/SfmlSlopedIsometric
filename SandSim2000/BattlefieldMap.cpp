#include "BattlefieldMap.h"

#include <cmath>
#include <iostream>

void BattlefieldMap::initMap(unsigned int mapSize)
{
    size = static_cast<int>(mapSize);
    grass_spritesheet = spritesheet("../resources/images/Terrain/grass/grass_spritesheet.png", 8, 2);
        
    initDepthMap();
    initDirectionMap();
    initSpriteMap();
}

void BattlefieldMap::initDepthMap()
{
    depthMap = new int* [size];
    for (int y = 0; y < size; y++)
    {
        depthMap[y] = new int[size];

        for (int x = 0; x < size; x++)
        {
            depthMap[y][x] = 0;
        }
    }
    // use this for the hill in the middle of the map
    int middle = static_cast<int>(size / 2);
    depthMap[middle][middle] = 2;
    for (int i = middle - 1; i <= middle + 1; i++)
    {
        depthMap[i][middle - 1] = 1;
        depthMap[i][middle + 1] = 1;
    }
    depthMap[middle - 1][middle] = 1;
    depthMap[middle + 1][middle] = 1;
}

void BattlefieldMap::initDirectionMap()
{
    directionMap = new Direction * [size];

    for (int y = 0; y < size; y++)
    {
        directionMap[y] = new Direction[size];

        for (int x = 0; x < size; x++)
        {
            directionMap[y][x] = F;  // Initialize all directions to F by default

            int height = depthMap[y][x];

            // West
            if (x > 0 && testLocation(x - 1, y, height) > 0)
            {
                directionMap[y][x] = W;
            }
            // North
            else if (y > 0 && testLocation(x, y - 1, height) > 0)
            {
                directionMap[y][x] = N;
            }
            // East
            else if (x < size - 1 && testLocation(x + 1, y, height) > 0)
            {
                directionMap[y][x] = E;
            }
            // South
            else if (y < size - 1 && testLocation(x, y + 1, height) > 0)
            {
                directionMap[y][x] = S;
            }
            // Northwest
            else if (x > 0 && y > 0 && testLocation(x - 1, y - 1, height) > 0)
            {
                directionMap[y][x] = NW;
            }
            // Northeast
            else if (x < size - 1 && y > 0 && testLocation(x + 1, y - 1, height) > 0)
            {
                directionMap[y][x] = NE;
            }
            // Southwest
            else if (x > 0 && y < size - 1 && testLocation(x - 1, y + 1, height) > 0)
            {
                directionMap[y][x] = SW;
            }
            // Southeast
            else if (x < size - 1 && y < size - 1 && testLocation(x + 1, y + 1, height) > 0)
            {
                directionMap[y][x] = SE;
            }
        }
    }
}

int BattlefieldMap::testLocation(int x, int y, int height)
{
    if (x > 0 && x < size - 1 && y > 0 && y < size - 1)
        return depthMap[y][x] - height;
    return 0;
}

void BattlefieldMap::initSpriteMap()
{
    spriteMap = new sf::Sprite ** [size];
    for (int y = 0; y < size; y++)
    {
        spriteMap[y] = new sf::Sprite * [size];

        for (int x = 0; x < size; x++)
        {
            spriteMap[y][x] = grass_spritesheet.getSprite(directionMap[y][x]);
            //KEEP THIS HERE, dont know why but without this the texture pointer fails
            //and all textures appear white. dont touch
            spriteMap[y][x]->setTexture(grass_spritesheet.texture);
        }
    }
}


BattlefieldMap::~BattlefieldMap()
{
    //Cleanup maps
    for (int i = 0; i < size; i++) {
        delete[] depthMap[i];
        delete[] directionMap[i];
        delete[] spriteMap[i];
    }

    delete[] depthMap;
    delete[] directionMap;
    delete[] spriteMap;
}
