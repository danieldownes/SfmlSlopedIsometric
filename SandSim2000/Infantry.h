#pragma once
#include "Agent.h"


class Infantry : public Agent {
public:
    Infantry(int initialPosX, int initialPosY, sf::String unitType, bool initialPinned = false);

    bool isPinned() const { return pinned; }          
    void setPinned(bool newPinned);                 

private:
    bool pinned;                                   

};