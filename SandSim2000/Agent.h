#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include <string>

#include "SpriteManager.h"

class Agent {
protected:
    int posX, posY;
    int health;
    int armour;
    int speed;
    int ballisticSkill;

    std::string unitType;
    int spriteIndex = 0;

    bool directionalSprite = false;
    sf::Vector2i currentDirection = sf::Vector2i(0,0);

public:
    Agent(int initialPosX, int initialPosY, int initialHealth, int initialArmour, int initialSpeed, int initialBallisticSkill, bool directional, sf::String basicUnitType);
    virtual ~Agent();

    void takeDamage(int damage);

    int getPosX() const;
    int getPosY() const;
    int getHealth() const;
    int getArmour() const;
    int getSpeed() const;
    int getBallisticSkill() const;
    std::string getUnitType() const;

    bool isDirectionalSprite() const;
    sf::Vector2i getCurrentDirection() const;

    void setHealth(int newHealth);
    void setArmour(int newArmour);
    void setSpeed(int newSpeed);
    void setBallisticSkill(int newBallisticSkill);
    void setUnitType(std::string unit);


    std::string getSpriteString() { return unitType; }
    int getSpriteIndex() { return spriteIndex; }
};
