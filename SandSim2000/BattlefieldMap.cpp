#include "BattlefieldMap.h"

#include <cmath>
#include <iostream>

void BattlefieldMap::initMap(int mapSize)
{
    size = mapSize;

    initDepthMap();
    initDirectionMap();
    initSpriteMap();

    DebugOutputMap();
}

void BattlefieldMap::initDepthMap()
{
    depthMap = new int* [size];
    //in its current state will just make a 2d sin wave
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
    directionMap = new BattlefielTileHeights * [size];
    for (int y = 0; y < size; y++)
    {
        directionMap[y] = new BattlefielTileHeights[size];
        for (int x = 0; x < size; x++)
        {
            int thisTileHeight = depthMap[y][x];
            directionMap[y][x] = BattlefielTileHeights(thisTileHeight);

            if (y > 0)
                directionMap[y][x].north = depthMap[y - 1][x];
            if (y < size - 1)
                directionMap[y][x].south = depthMap[y + 1][x];
            if (x > 0)
                directionMap[y][x].east = depthMap[y][x - 1];
            if (x < size - 1)
                directionMap[y][x].west = depthMap[y][x + 1];
        }
    }
}

void BattlefieldMap::initSpriteMap()
{
    SpriteMap = new sf::Sprite * [size];
    for (int y = 0; y < size; y++)
    {
        SpriteMap[y] = new sf::Sprite[size];

        for (int x = 0; x < size; x++)
        {

        }
    }
}

BattlefieldMap::~BattlefieldMap()
{
    //Cleanup maps
    for (int i = 0; i < size; i++) {
        delete[] depthMap[i];
        delete[] directionMap[i];
        delete[] SpriteMap[i];
    }

    delete[] depthMap;
    delete[] directionMap;
    delete[] SpriteMap;
}

void BattlefieldMap::DebugOutputMap()
{
    std::cout << "DEPTH MAP" << "\n\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            std::cout << depthMap[i][j] << " : ";
        std::cout << "\n";
    }
    std::cout << "DIRECTION MAP" << "\n\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            std::cout << directionMap[i][j].height << "," << directionMap[i][j].north << "," << directionMap[i][j].south << "," << directionMap[i][j].east << "," << directionMap[i][j].west << " : ";
        std::cout << "\n";
    }
}