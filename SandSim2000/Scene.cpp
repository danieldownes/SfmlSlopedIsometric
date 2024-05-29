#include "Scene.h"
#define MAX_TILE_DEPTH 5
#define TILE_SIZE 100

Scene::Scene() {}

void Scene::UpdateGameScene(Camera& cam, GameState& gameState, InputState& inputState) {
	GridGenerator gridGenerator;
	sf::IntRect viewbounds(0, 0, cam.window.getSize().x, cam.window.getSize().y);

	gameScene.clear();
	findViewportIterators(gameState.quadTree, cam, gridGenerator, viewbounds);
	getBattlefieldCellFromMouseClick(cam, gridGenerator, inputState);

}

void Scene::findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds) {
	int screenX, screenY;
	sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(root->quadRect.getPosition().x / TILE_SIZE, root->quadRect.getPosition().y / TILE_SIZE));
	cam.WorldToScreen(isometricPosition.x + static_cast<float>(cam.window.getSize().x) / 2, isometricPosition.y, screenX, screenY);

	int sizeX = root->quadRect.getSize().x * cam.scaleX;
	int sizeY = static_cast<float>(root->quadRect.getSize().y) / 2 * cam.scaleY
		+ static_cast<float>(TILE_SIZE) / 2 * MAX_TILE_DEPTH * cam.scaleY;

	sf::IntRect isometricNodeRect(screenX - sizeX / 2, screenY, sizeX, sizeY);

	if (!viewbounds.intersects(isometricNodeRect)) return;

	if (typeid(*root) == typeid(QuadTreeLeaf)) {
		gameScene.insert(((QuadTreeLeaf*)root)->iter);
	} else {
		for (QuadTree* child : ((QuadTree*)root)->children)
			findViewportIterators(child, cam, gridGenerator, viewbounds);
	}
}

std::vector<sf::Sprite> Scene::buildGameScene()
{
	std::vector<sf::Sprite> sprites = std::vector<sf::Sprite>();
	GridGenerator gridGenerator;

	for (auto iter = gameScene.begin(); iter != gameScene.end(); iter++)
	{
		BattlefieldCell currentCell = **iter;
		sf::Sprite terrainSprite = *currentCell.terrainSprite;

		sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(currentCell.x, currentCell.y));

		terrainSprite.setPosition(isometricPosition.x, isometricPosition.y - currentCell.YOffset);
		sprites.push_back(terrainSprite);

		if (currentCell.Objects.size() != 0)
		{
			for (int i = 0; i < currentCell.Objects.size(); i++)
			{
				std::string spriteString = currentCell.Objects[i].getSpriteString();
				int spriteIndex = currentCell.Objects[i].getSpriteIndex();

				sf::Sprite objectSprite = *SpriteManager::GetInstance()->GetSprite(spriteString, spriteIndex);
				objectSprite.setTexture(SpriteManager::GetInstance()->GetSpriteSheet(spriteString).texture);

				sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(currentCell.Objects[i].getPosX(), currentCell.Objects[i].getPosY()));
				objectSprite.setPosition(isometricPosition.x, isometricPosition.y - currentCell.YOffset);

				sprites.push_back(objectSprite);
			}
		}
	}
	return sprites;
}

sf::Vector2i Scene::getScreenPositionOfCell(const BattlefieldCell& cell, Camera& cam, GridGenerator& gridGenerator) {
	sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(cell.x, cell.y));

	int screenX, screenY;
	cam.WorldToScreen(isometricPosition.x + cam.window.getSize().x / 2, isometricPosition.y, screenX, screenY);

	screenX += 50;  
	screenY += 100;

	return sf::Vector2i(screenX, screenY);
}


sf::Vector2i Scene::getBattlefieldCellFromMouseClick(Camera& cam, GridGenerator& gridGenerator, InputState& inputState) {
	sf::Vector2i placeholder(-1, -1);

	if (gameScene.empty()) {
		std::cout << "No cells in viewport." << std::endl;
		return placeholder;
	}

	int cellsToCheck = 24;
	int count = 0;

	for (auto iter = gameScene.begin(); iter != gameScene.end() && count < cellsToCheck; ++iter, ++count) {
		BattlefieldCell& cell = *(*iter);

		sf::Vector2i screenPosition = getScreenPositionOfCell(cell, cam, gridGenerator);

		
		std::vector<sf::Vector2i> screenVertices;
		for (const auto& vertex : cell.vertices) {
			screenVertices.emplace_back(screenPosition.x + vertex.x, screenPosition.y + vertex.y);
		}
		
		std::cout << "Screen vertices of cell (" << cell.x << ", " << cell.y << "):" << std::endl;
		for (const auto& vertex : screenVertices) {
			std::cout << "(" << vertex.x << ", " << vertex.y << ")" << std::endl;
		}

		
		//std::vector<sf::Vector2i> screenVertices;
		for (const auto& vertex : cell.vertices) {
			screenVertices.emplace_back(screenPosition.x + vertex.x, screenPosition.y + vertex.y);
		}

		if (pointInPolygon(inputState.mousePosition, screenVertices)) {
			//std::cout << "Mouse cursor is inside the cell at (" << cell.x << ", " << cell.y << ")" << std::endl;
			return sf::Vector2i(cell.x, cell.y);
		}
		
	}

	//std::cout << "Mouse cursor is not inside any cell." << std::endl;

	return placeholder;
}

bool Scene::pointInPolygon(const sf::Vector2i& point, const std::vector<sf::Vector2i>& vertices) {
    int i, j, nvert = vertices.size();
    bool c = false;

    for (i = 0, j = nvert - 1; i < nvert; j = i++) {
        if (((vertices[i].y > point.y) != (vertices[j].y > point.y)) &&
            (point.x < (vertices[j].x - vertices[i].x) * (point.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x)) {
            c = !c;
        }
    }

    return c;
}

/*
	// For 1 Cell

sf::Vector2i Scene::getBattlefieldCellFromMouseClick(Camera& cam, InputState& inputState) {
	sf::Vector2i placeholder(-1, -1);

	if (gameScene.empty()) {
		std::cout << "No cells in viewport." << std::endl;
		return placeholder;
	}

	int centerOffsetX = cam.window.getSize().x / 2;

	for (auto iter = gameScene.begin(); iter != gameScene.end(); ++iter) {
		BattlefieldCell& cell = *(*iter);

		std::vector<sf::Vector2i> screenVertices;
		for (const auto& vertex : cell.vertices) {
			int screenX, screenY;
			cam.WorldToScreen(vertex.x + centerOffsetX, vertex.y, screenX, screenY);
			screenVertices.emplace_back(screenX + 50, screenY + 100);
		}

		if (pointInPolygon(inputState.mousePosition, screenVertices)) {
			std::cout << "Mouse cursor is inside the cell at (" << cell.x << ", " << cell.y << ")" << std::endl;
			return sf::Vector2i(cell.x, cell.y);
		}
	}

	std::cout << "Mouse cursor is not inside any cell." << std::endl;
	return placeholder;
}

*/