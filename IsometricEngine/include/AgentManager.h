#pragma once
#include <cmath>
#include <functional>
#include <queue>
#include <set>
#include <typeinfo>
#include <unordered_set>

#include "Camera.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "InputState.h"
#include "MobileAgent.h"
#include "MovementManager.h"
#include "PathfinderAgent.h"
#include "Scene.h"
#include "Scenery.h"
#include "Tree.h"

class AgentManager
{
   public:
	void onUpdate(InputState& state, std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
				  GameStateManager& gameStateManager, Camera& camera, Scene& scene);

	void placeAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Agent agent,
					GameStateManager& gameStateManager);

	void placeMobileAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
						  MobileAgent agent, GameStateManager& gameStateManager);

	void placePathfinderAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gamesScene,
							  PathfinderAgent agent, GameStateManager& gameStateManager);

	PathfinderAgent* pathfinderAgent = nullptr;
	MobileAgent* mobileAgent = nullptr;

   private:
	bool leftClick = false;
	bool rightClick = false;

	MovementManager movementManager;
	GlobalConstants constants;
};
