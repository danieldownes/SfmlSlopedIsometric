#include "Scene.h"
#define MAX_TILE_DEPTH 5
#define TILE_SIZE 100

Scene::Scene() {}

void Scene::UpdateGameScene(Camera& cam, GameState& gameState, InputState& inputState) {
	GridGenerator gridGenerator;
	sf::IntRect viewbounds(0, 0, cam.window.getSize().x, cam.window.getSize().y);

	gameScene.clear();
	findViewportIterators(gameState.quadTree, cam, gridGenerator, viewbounds);
	getBattlefieldCellFromMouseClick(cam);

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

sf::Vector2i Scene::getBattlefieldCellFromMouseClick(Camera& cam) {
	sf::Vector2i placeholder(-1, -1);

	if (gameScene.empty()) {
		std::cout << "No cells in viewport." << std::endl;
		return placeholder;
	}

	float worldX = 0.0f; 
	float worldY = 0.0f; 

	int screenX, screenY;

	int centerOffsetX = cam.window.getSize().x / 2;

	// Use WorldToScreen to convert world coordinates to screen coordinates
	cam.WorldToScreen(worldX + centerOffsetX, worldY, screenX, screenY);

	// Output the screen coordinates of the battlefield cell
	std::cout << "Screen coordinates of the battlefield cell: (" << screenX + 50 << ", " << screenY + 100 << ")" << std::endl;

	return sf::Vector2i(screenX, screenY);
}