#pragma once
#include <vector>

#include "Agent.h"

#include "SFML/Graphics.hpp"

class BattlefieldCell {
public:

    int x, y; 

    // Alpha Team Suggestions: Please change the name "sprite" to "terrainSprite" so the distinction between an 
    // Agent Sprite and a Terrain Sprite becomes much more clear. Please ensure you track down all 
    // instances throughout the rest of the codebase of sprite and change it to terrainSprite.
    
    std::vector<Agent> Objects = std::vector<Agent>();
    sf::Sprite* sprite;
    int YOffset;





    //Don't worry about this yet.
    //Scenery
};