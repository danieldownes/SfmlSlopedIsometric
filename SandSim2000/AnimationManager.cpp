#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
    initializeDefaultTerrainTexure();
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::initializeDefaultTerrainTexure()
{
    const std::string filePath = "../resources/images/Terrain/default.png";

    if (!defaultTerrainTexture.loadFromFile(filePath))
    {
        std::cerr << "Failed to load terrain texture from file: " << filePath << std::endl;
        return;
    }
}

void AnimationManager::initializeTerrainSpriteMap(GameState* gameState)
{
    GridGenerator gridGenerator;
    int centerXOffset = 725;

    for (int i = 0; i < gameState->mapSize; ++i)
    {
        for (int j = 0; j < gameState->mapSize; ++j)
        {
            /*  Code if the sprite map is just for the terrain
            sf::Sprite& sprite = spriteMap[i][j];
            sprite.setTexture(defaultTerrainTexture);
            MapInfo& mapInfo = gameState->getMapData()[i][j];
            sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(i, j));
            isometricPosition.y *= mapInfo.z;
            isometricPosition.x += centerXOffset;
            sprite.setPosition(isometricPosition);
            */

            // Assumes the sprite map only contains 
            sf::Sprite sprite = sf::Sprite();
            sprite.setTexture(defaultTerrainTexture);
            MapInfo& mapInfo = gameState->getMapData()[i][j];
            sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(i, j));
            isometricPosition.y *= mapInfo.z;
            isometricPosition.x += centerXOffset;
            sprite.setPosition(isometricPosition);

            spriteMap.push_back(sprite);
        }
    }
}

void AnimationManager::renderSpriteMap(sf::RenderWindow* window)
{
    for (const sf::Sprite& sprite : spriteMap) {
        std::cout << sprite.getPosition().x << ":" << sprite.getPosition().y << '\n';
        window->draw(sprite);
    }
}
