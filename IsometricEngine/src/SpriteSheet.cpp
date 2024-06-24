#include "SpriteSheet.h"
#include <iostream>

SpriteSheet::SpriteSheet(const char* filepath, unsigned int columns, unsigned int rows)
{
    texture.loadFromFile(filepath);
    texture.setSmooth(true);

    cell_width = texture.getSize().x / columns; cell_height = texture.getSize().y / rows;
    sprite_dimensions = sf::Vector2u({ columns, rows });
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            sf::IntRect texture_rect = { x * cell_width, y * cell_height, cell_width, cell_height };

            sf::Sprite sprite;
            sprite.setTexture(texture); sprite.setTextureRect(texture_rect);

            sprites.push_back(sprite);
        }
    }
}
sf::Sprite* SpriteSheet::getSprite(unsigned int index)
{
    if (index < sprites.size())
        return &sprites[index];
    std::cerr << "[INVALID SPRITE POSITION]" << std::endl;
}
sf::Sprite* SpriteSheet::getSprite(sf::Vector2u position)
{
    unsigned int index = position.y * sprite_dimensions.y + position.x;
    return getSprite(index);
}