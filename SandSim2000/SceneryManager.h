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
public:
	void placeScenery(sf::Vector2f mouseWorldPosition, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager& gameStateManager);
	void setX(int xPosition);
	void setY(int yPosition);

private:
};

