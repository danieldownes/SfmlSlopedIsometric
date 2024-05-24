#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Agent.h"


class BattlefieldCell {
public:

    int x, y; 
    int windowX, windowY;
    std::vector<sf::Vector2i> vertices;
 
    std::vector<Agent> Objects = std::vector<Agent>();
    sf::Sprite* terrainSprite;
    int YOffset;

};