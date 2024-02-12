#pragma once

class Agent {
protected:
    int posX, posY;
    int health;
    int armour;
    int speed;
    int ballisticSkill;

public:
    Agent(int initialPosX, int initialPosY, int initialHealth, int initialArmour, int initialSpeed, int initialBallisticSkill);
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
};
