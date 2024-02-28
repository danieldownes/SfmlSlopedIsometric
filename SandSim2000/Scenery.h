#pragma once
#include "Agent.h"

class Scenery : public Agent {
public:
    Scenery(int initialPosX, int initialPosY, sf::String sceneryType) :Agent(initialPosX, initialPosY, -1, -1, -1, -1, sceneryType) {};

private:


};
