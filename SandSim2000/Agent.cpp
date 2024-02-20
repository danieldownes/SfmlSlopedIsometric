#include "Agent.h"

Agent::Agent(int initialPosX, int initialPosY, int initialHealth, int initialArmour, int initialSpeed, int initialBallisticSkill, sf::String basicUnitType)
    : posX(initialPosX), posY(initialPosY), health(initialHealth), armour(initialArmour), speed(initialSpeed), ballisticSkill(initialBallisticSkill), unitType(basicUnitType), agentSprites("RedBaron") {
}


Agent::~Agent() {}

void Agent::takeDamage(int damage) {
    int damageTaken = damage - armour;
    if (damageTaken > 0) {
        health -= damageTaken;
        if (health < 0) {
            health = 0;
        }
    }
}

int Agent::getPosX() const {
    return posX;
}

int Agent::getPosY() const {
    return posY;
}

int Agent::getHealth() const {
    return health;
}

int Agent::getArmour() const {
    return armour;
}

int Agent::getSpeed() const {
    return speed;
}

int Agent::getBallisticSkill() const {
    return ballisticSkill;
}

void Agent::setHealth(int newHealth) {
    health = newHealth;
}

void Agent::setArmour(int newArmour) {
    armour = newArmour;
}

void Agent::setSpeed(int newSpeed) {
    speed = newSpeed;
}

void Agent::setBallisticSkill(int newBallisticSkill) {
    ballisticSkill = newBallisticSkill;
}

//gets a new sprite to be used in the program
sf::Sprite* Agent::getNewSprite(int spriteIndex)
{
    sf::Sprite* selectedSprite = agentSprites.GetSprite("RedBaron", 0);
    return selectedSprite;
}

//sets the sprite
void Agent::setAgentSprite(sf::Sprite* newSprite)
{
    currentSprite = newSprite;
}

//sends back the sprite to be used in the program
sf::Sprite* Agent::getSprite()
{
    return currentSprite;
}
