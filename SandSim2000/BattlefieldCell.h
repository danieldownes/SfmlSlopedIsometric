#pragma once
#include <vector>
#include "Agent.h"
#include "TerrainTile.h"

#include "SFML/Graphics.hpp"

class BattlefieldCell {
public:

    int x, y; // Coordinates of Iterator in QuadTree
    TerrainTile terrain;
    sf::Texture* texture;
    int YOffset;





    //Don't worry about these ones yet.
    //Scenery
    //std::vector<Agent> agents;
};