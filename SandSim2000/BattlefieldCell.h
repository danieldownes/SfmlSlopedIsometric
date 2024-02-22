#pragma once
#include <vector>

#include "Agent.h"

#include "SFML/Graphics.hpp"

class BattlefieldCell {
public:

    int x, y; 

    std::vector<Agent> Objects = std::vector<Agent>();
    sf::Sprite* terrainSprite;
    int YOffset;

};