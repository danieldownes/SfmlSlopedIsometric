#pragma once
#include "SpriteManager.h"
#include <SFML/Graphics/Sprite.hpp>

class Agent {
protected:
    int posX, posY;
    int health;
    int armour;
    int speed;
    int ballisticSkill;

    sf::String unitType;
    int spriteIndex = 0;
    

public:
    Agent(int initialPosX, int initialPosY, int initialHealth, int initialArmour, int initialSpeed, int initialBallisticSkill, sf::String basicUnitType);
    ~Agent();

    void takeDamage(int damage);

    int getPosX() const;
    int getPosY() const;
    int getHealth() const;
    int getArmour() const;
    int getSpeed() const;
    int getBallisticSkill() const;

    void setHealth(int newHealth);
    void setArmour(int newArmour);
    void setSpeed(int newSpeed);
    void setBallisticSkill(int newBallisticSkill);

    std::string getSpriteString() { return unitType; }
    int getSpriteIndex() { return spriteIndex; }
};
