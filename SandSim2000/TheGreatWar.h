#pragma once

#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include "InputState.h"
#include "SpriteManager.h"
#include "Tree.h"
#include "AgentManager.h"
#include "MainMenu.h"

void initializeGameComponents(unsigned int mapSize,
	SpriteManager& sprites,
	GameStateManager& gameStateManager,
	AgentManager& agentManager,
	InputState& inputState,
	Camera& camera,
	Scene& scene,
	MenuOption selectedOption);
