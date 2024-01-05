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

void AnimationManager::renderSpriteMap(sf::RenderWindow* window)
{
    for (const sf::Sprite& sprite : spriteMap) {
        std::cout << sprite.getPosition().x << ":" << sprite.getPosition().y << '\n';
        window->draw(sprite);
    }
}

void AnimationManager::renderTerrainMap(sf::RenderWindow* window, GameState* gameState)
{
    sf::FloatRect viewBounds(0, 0, window->getSize().x, window->getSize().y);

    sf::Sprite sprite = sf::Sprite();
    GridGenerator gridGenerator;
    int centerOffsetX = 725;

    for (int i = 0; i < gameState->mapSize; i++)
    {
        for (int j = 0; j < gameState->mapSize; j++)
        {
            // update texture -- height for future
            switch (gameState->getMapData()[i][j].height)
            {
            case (1):
                sprite.setTexture(defaultTerrainTexture);
            }

            // Set the sprite position
            sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(i, j));
            isometricPosition.y *= gameState->getMapData()[i][j].z;
            isometricPosition.x += centerOffsetX;
            sprite.setPosition(isometricPosition);
            if(viewBounds.intersects(sprite.getGlobalBounds()))
                window->draw(sprite);
        }
    }
}