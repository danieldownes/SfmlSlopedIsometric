#pragma once
#include <math.h>

#include <string>

#include "SFML/Graphics/Sprite.hpp"
#include "SpriteManager.h"

class Agent
{
   protected:
	float posX, posY;
	int health;
	int armour;
	float speed;
	int ballisticSkill;

	std::string unitType;
	int spriteIndex = 0;

	bool directionalSprite = false;
	sf::Vector2i currentDirection = sf::Vector2i(-1, 0);

   public:
	Agent(float initialPosX, float initialPosY, int initialHealth, int initialArmour, float initialSpeed,
		  int initialBallisticSkill, bool directional, std::string basicUnitType);
	virtual ~Agent();

	void takeDamage(int damage);

	sf::Vector2i Agent::getPosVector2i() const;
	sf::Vector2f Agent::getPosVector2f() const;
	float getPosX() const;
	float getPosY() const;

	sf::Vector2i Agent::getPosIndex() const;
	int getPosXIndex() const;
	int getPosYIndex() const;

	int getHealth() const;
	int getArmour() const;
	float getSpeed() const;
	int getBallisticSkill() const;
	std::string getUnitType() const;

	bool isDirectionalSprite() const;
	sf::Vector2i getCurrentDirection() const;
	bool isPathfinderAgent = false;

	void setHealth(int newHealth);
	void setArmour(int newArmour);
	void setSpeed(float newSpeed);
	void setBallisticSkill(int newBallisticSkill);
	void setUnitType(std::string unit);

	std::string getSpriteString()
	{
		return unitType;
	}
	int getSpriteIndex()
	{
		return spriteIndex;
	}
};
