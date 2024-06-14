#pragma once
#include <set>
#include "BattlefieldCell.h"
#include "AnimationManager.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"
#include "InputState.h"

class Scene {
public:
	Scene();

	void UpdateGameScene(Camera& cam, GameState& gameState, InputState& inputState);
	std::vector<sf::Sprite> buildGameScene(AnimationManager* animationManager);
	sf::Vector2i getScreenPositionOfCell(const BattlefieldCell& cell, Camera& cam, GridGenerator& gridGenerator);
	void getBattlefieldCellFromMouseClick(Camera& cam, GridGenerator& gridGenerator, InputState& inputState);

	bool pointInPolygon(const sf::Vector2i& point, const std::vector<sf::Vector2i>& vertices);

	std::set<std::vector<BattlefieldCell>::iterator> gameScene;
private:
	void findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds);
};