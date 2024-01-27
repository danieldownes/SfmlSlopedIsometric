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
    const std::string presetFilePath = "../resources/images/Terrain/Grass/";
    sf::Texture texture;
    std::cout << "Loading Texture: " << tilevalue << "\n";
    if (!texture.loadFromFile(presetFilePath + tilevalue + ".png"))
    {
        std::cout << "[TEXTURE MISSING][GRASS]-" << tilevalue << std::endl;
        texture.loadFromFile(presetFilePath + "Misc.png");
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