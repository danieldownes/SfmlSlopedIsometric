#pragma once

#include <string>
#include "SFML/System/Vector2.hpp"

struct TerrainTile {
    int     z;
    int     height;           
    int     facing;
    bool    fogOfWar;
    std::string     terrain;   
    sf::FloatRect   rect;
};