#pragma once
#include <vector>
#include "Agent.h"
#include "TerrainTile.h"

class BattlefieldCell {
public:

    int x, y; // Coordinates of Iterator in QuadTree
    TerrainTile terrain;





    //Don't worry about these ones yet.
    //Scenery
    //std::vector<Agent> agents;
};