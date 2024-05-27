#pragma once
#include <cmath>
#include <set>
#include <typeinfo>
#include "GameState.h"
#include "BattlefieldMap.h"
#include "BattlefieldCell.h"
#include "Agent.h"
#include "InputStateManager.h"
#include "InputState.h"
#include "GridGenerator.h"
#include "Scenery.h"
#include "Tree.h"
#include "GameStateManager.h"
#include "Camera.h"
#include "Scene.h"

class AgentManager
{
public:
	void onUpdate(
		InputState& state, 
		std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
		GameStateManager& gameStateManager, 
		Camera& camera, 
		Scene& scene);
	void placeScenery(sf::Vector2f isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager& gameStateManager);
	void placeAgent(sf::Vector2f cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Agent 
		agent, GameStateManager& gameStateManager);
	void updateAgentPosition();
	void setX(int xPosition);
	void setY(int yPosition);

private:
	bool leftClick = false;
	bool rightClick = false;
};