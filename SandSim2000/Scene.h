#pragma once
#include <vector>
#include "BattlefieldCell.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"

class Scene {
public:
	Scene();

	std::vector<std::vector<BattlefieldCell>::iterator>& getGameScene() { return gameScene; }
	void UpdateGameScene(Camera& cam, GameState& gameState);
private:
	void findViewportIterators(GameState::QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds);

	std::vector<std::vector<BattlefieldCell>::iterator> gameScene;
};