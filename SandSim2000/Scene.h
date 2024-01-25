#pragma once
#include <vector>
#include "BattlefieldCell.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"

class Scene {
public:
	Scene();

	void UpdateGameScene(Camera& cam, GameState& gameState);

	std::vector<std::vector<BattlefieldCell>::iterator> gameScene;
private:
	void findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds, unsigned int& index);
};