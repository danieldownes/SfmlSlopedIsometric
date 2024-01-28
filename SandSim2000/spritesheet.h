#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class spritesheet
{
public:
    spritesheet(const char* filepath, unsigned int columns, unsigned int rows);
    spritesheet() {}
    sf::Sprite* getSprite(unsigned int index);
    sf::Sprite* getSprite(sf::Vector2u position);
    sf::Texture texture;
private:
    int cell_height; int cell_width;
    sf::Vector2u sprite_dimensions;

    std::vector<sf::Sprite> sprites;

};