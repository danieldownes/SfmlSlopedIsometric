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

sf::Texture* BattlefieldMap::getTexture(Direction direction)
{
    std::string tilevalue = evaluateDirection(direction);
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
    return getTexture(direction);
}

std::string BattlefieldMap::evaluateDirection(Direction dir)
{
    switch (dir)
    {
    case F:
        return "F";
    case N:
        return "N";
    case NE:
        return "NE";
    case E:
        return "E";
    case SE:
        return "SE";
    case S:
        return "S";
    case SW:
        return "SW";
    case W:
        return "W";
    case NW:
        return "NW";
    default:
        return "Invalid Direction";
    }
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
}