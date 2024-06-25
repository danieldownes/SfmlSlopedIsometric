#pragma once

#include <SFML/Graphics.hpp>

#include "AgentManager.h"
#include "AnimationManager.h"
#include "Camera.h"
#include "InputState.h"
#include "InputStateManager.h"
#include "MainMenu.h"
#include "Scene.h"
#include "SpriteManager.h"
#include "Tree.h"

void placeTree(sf::Vector2i isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
			   Scenery sceneObject, GameStateManager& gameStateManager);