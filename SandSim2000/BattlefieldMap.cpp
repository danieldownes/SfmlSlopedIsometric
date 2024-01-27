#include "BattlefieldMap.h"

#include <cmath>
#include <iostream>

void BattlefieldMap::initMap(unsigned int mapSize)
{
    size = static_cast<int>(mapSize);

    initDepthMap();
    initDirectionMap();
    initTextureMap();

    //DebugOutputMap();
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
    directionMap = new BattlefieldTileHeights * [size];
    for (int y = 0; y < size; y++)
    {
        directionMap[y] = new BattlefieldTileHeights[size];
        for (int x = 0; x < size; x++)
        {
            int thisTileHeight = depthMap[y][x];
            directionMap[y][x] = BattlefieldTileHeights(thisTileHeight);

            // NORTH
            directionMap[y][x].north = (y > 0) ? depthMap[y - 1][x] : thisTileHeight;

            // SOUTH
            directionMap[y][x].south = (y < size - 1) ? depthMap[y + 1][x] : thisTileHeight;

            // EAST
            directionMap[y][x].west = (x > 0) ? depthMap[y][x - 1] : thisTileHeight;

            // WEST
            directionMap[y][x].east = (x < size - 1) ? depthMap[y][x + 1] : thisTileHeight;

            // NORTHWEST
            directionMap[y][x].northwest = (y > 0 && x > 0) ? depthMap[y - 1][x - 1] : thisTileHeight;

            // NORTHEAST
            directionMap[y][x].northeast = (y > 0 && x < size - 1) ? depthMap[y - 1][x + 1] : thisTileHeight;

            // SOUTHWEST
            directionMap[y][x].southwest = (y < size - 1 && x > 0) ? depthMap[y + 1][x - 1] : thisTileHeight;

            // SOUTHEAST
            directionMap[y][x].southeast = (y < size - 1 && x < size - 1) ? depthMap[y + 1][x + 1] : thisTileHeight;

            // Adjust diagonal directions based on neighboring heights
            if (y > 0 && x < size - 1 && depthMap[y - 1][x] != depthMap[y][x + 1])
                directionMap[y][x].northeast = std::max(depthMap[y - 1][x], depthMap[y][x + 1]);

            if (y > 0 && x > 0 && depthMap[y - 1][x] != depthMap[y][x - 1])
                directionMap[y][x].northwest = std::max(depthMap[y - 1][x], depthMap[y][x - 1]);

            if (y < size - 1 && x < size - 1 && depthMap[y + 1][x] != depthMap[y][x + 1])
                directionMap[y][x].southeast = std::max(depthMap[y + 1][x], depthMap[y][x + 1]);

            if (y < size - 1 && x > 0 && depthMap[y + 1][x] != depthMap[y][x - 1])
                directionMap[y][x].southwest = std::max(depthMap[y + 1][x], depthMap[y][x - 1]);
        }
    }
}

void BattlefieldMap::initTextureMap()
{
    textureMap = new sf::Texture ** [size];
    for (int y = 0; y < size; y++)
    {
        textureMap[y] = new sf::Texture*[size];

        for (int x = 0; x < size; x++)
        {
            textureMap[y][x] = getTexture(directionMap[y][x]);
        }
    }
}

sf::Texture* BattlefieldMap::getTexture(BattlefieldTileHeights heights)
{
    std::string tilevalue = heights.evaluate();
    for (auto it = grassTextures.begin(); it != grassTextures.end(); ++it)
    {
        if (it->second == tilevalue)
            return &(it->first);
    }
    // if code has reached here, the grass texture for this type hasnt been initialised yet.
    const std::string presetFilePath = "../resources/images/Terrain/";
    sf::Texture texture;
    std::cout << "Loading Texture: " << tilevalue << "\n";
    if (!texture.loadFromFile(presetFilePath + "grass/" + tilevalue + ".png"))
    {
        std::cout << "[TEXTURE MISSING][GRASS]-" << tilevalue << std::endl;
        texture.loadFromFile(presetFilePath + "NULLTERRAIN.png");
    }
    texture.setSmooth(true);
    grassTextures.push_back(std::make_pair(texture, tilevalue));
    return getTexture(heights);
}

BattlefieldMap::~BattlefieldMap()
{
    //Cleanup maps
    for (int i = 0; i < size; i++) {
        delete[] depthMap[i];
        delete[] directionMap[i];
        delete[] textureMap[i];
    }

    delete[] depthMap;
    delete[] directionMap;
    delete[] textureMap;
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
            std::cout << directionMap[i][j].evaluate() << ":";
        std::cout << "\n";
    }
}