#pragma once
#include <cmath>
#include <set>

#include "GameState.h"
#include "BattlefieldMap.h"
#include "BattlefieldCell.h"
#include "Agent.h"
#include "InputStateManager.h"
#include "GridGenerator.h"
#include "Scenery.h"
#include "Tree.h"
#include "GameStateManager.h"

class SceneryManager
{
	// This will be used to handle placing scenery
	// To accomplish this it will need to interact with the InputState and InputStateManager
	// to receive input from the player to place scenery on command. Start with the tree sprite. 
public:
	void placeScenery(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager gameStateManager);
	void setX(int xPosition);
	void setY(int yPosition);

private:
};

