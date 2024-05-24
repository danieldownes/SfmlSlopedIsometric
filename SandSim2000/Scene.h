#pragma once
#include <set>
#include "BattlefieldCell.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"
#include "InputState.h"

class Scene {
public:
	Scene();

	void UpdateGameScene(Camera& cam, GameState& gameState, InputState& inputState);
	std::vector<sf::Sprite> buildGameScene();
	sf::Vector2i getBattlefieldCellFromMouseClick(Camera& cam);

	std::set<std::vector<BattlefieldCell>::iterator> gameScene;
private:
	void findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds);
};