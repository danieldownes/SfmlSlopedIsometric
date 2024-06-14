#pragma once
#include <set>
#include <functional>

#include "BattlefieldCell.h"
#include "Camera.h"
#include "GameState.h"
#include "GridGenerator.h"
#include "InputState.h"
#include "GlobalConstants.h"

class Scene {
public:
	Scene();

	void UpdateGameScene(Camera& cam, GameState& gameState, InputState& inputState);
	std::vector<sf::Sprite> buildGameScene();
	sf::Vector2i getScreenPositionOfCell(const BattlefieldCell& cell, Camera& cam, GridGenerator& gridGenerator);
	void getBattlefieldCellFromMouseClick(Camera& cam, GridGenerator& gridGenerator, InputState& inputState);

	bool pointInPolygon(const sf::Vector2i& point, const std::vector<sf::Vector2i>& vertices);

	//Create setter method and props for args

	void generateGhostGridFromScene(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds);

	std::set<std::vector<BattlefieldCell>::iterator> gameScene;
	std::vector<std::vector<BattlefieldCell*>> GhostGrid;



	int tileSize = GlobalConstants::cellSize;
	int quadTreeDepth = GlobalConstants::quadTreeDepth;
private:
	void findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds);
};