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
	std::vector<std::vector<BattlefieldCell>::iterator> findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator);

	std::vector<std::vector<BattlefieldCell>::iterator> gameScene;
};