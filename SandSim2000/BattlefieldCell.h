#pragma once
#include <vector>
#include "TerrainTile.h"

#include "SFML/Graphics.hpp"

class BattlefieldCell {
public:

    int x, y; // Coordinates of Iterator in QuadTree

    // Alpha Team Suggestions: Rather than store a single sprite, store a vector that can have at least 1 object,
    // which would be the terrain tile, or more, which could be scenery, ground unit, flyer unit, area effect, 
    // artillery shell etc. This will allow for many objects to be stored in 1 battlefield cell. Don't store the sprite 
    // directly in the battlefield cell, the Scene class will interface with the SpriteManager to get sprites.

    sf::Sprite* sprite;
    int YOffset;





    //Don't worry about these ones yet.
    //Scenery
    //std::vector<Agent> agents;
};