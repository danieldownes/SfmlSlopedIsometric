#include "Agent.h"

Agent::Agent(float initialPosX, float initialPosY, int initialHealth, int initialArmour, float initialSpeed,
			 int initialBallisticSkill, bool directional, std::string basicUnitType)
	: posX(initialPosX),
	  posY(initialPosY),
	  health(initialHealth),
	  armour(initialArmour),
	  speed(initialSpeed),
	  ballisticSkill(initialBallisticSkill),
	  directionalSprite(directional),
	  unitType(basicUnitType)
{
}

Agent::~Agent() {}

void Agent::takeDamage(int damage)
{
	int damageTaken = damage - armour;
	if (damageTaken > 0)
	{
		health -= damageTaken;
		if (health < 0)
		{
			health = 0;
		}
	}
}

sf::Vector2i Agent::getPosVector2i() const
{
	return sf::Vector2i(static_cast<int>(posX), static_cast<int>(posY));
}

sf::Vector2f Agent::getPosVector2f() const
{
	return sf::Vector2f(posX, posY);
}

float Agent::getPosX() const
{
	return posX;
}

float Agent::getPosY() const
{
	return posY;
}

sf::Vector2i Agent::getPosIndex() const
{
	return sf::Vector2i(getPosXIndex(), getPosYIndex());
}


int Agent::getPosXIndex() const
{
	return static_cast<int>(std::floor(posX));
}

int Agent::getPosYIndex() const
{
	return static_cast<int>(std::floor(posY));
}

int Agent::getHealth() const
{
	return health;
}

int Agent::getArmour() const
{
	return armour;
}

float Agent::getSpeed() const
{
	return speed;
}

int Agent::getBallisticSkill() const
{
	return ballisticSkill;
}

bool Agent::isDirectionalSprite() const
{
	return directionalSprite;
}

sf::Vector2i Agent::getCurrentDirection() const
{
	return currentDirection;
}

std::string Agent::getUnitType() const
{
	return std::string(unitType);
}

void Agent::setHealth(int newHealth)
{
	health = newHealth;
}

void Agent::setArmour(int newArmour)
{
	armour = newArmour;
}

void Agent::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Agent::setBallisticSkill(int newBallisticSkill)
{
	ballisticSkill = newBallisticSkill;
}

void Agent::setUnitType(std::string unit)
{
	unitType = unit;
}