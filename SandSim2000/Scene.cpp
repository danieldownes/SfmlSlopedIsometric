#include "Scene.h"

#define MAX_TILE_DEPTH 5
#define TILE_SIZE 100

Scene::Scene() {}

void Scene::UpdateGameScene(Camera& cam, GameState& gameState) {
	GridGenerator gridGenerator;
	sf::IntRect viewbounds(0, 0, cam.window.getSize().x, cam.window.getSize().y);

	gameScene.clear();
	findViewportIterators(gameState.quadTree, cam, gridGenerator, viewbounds);
}

void Scene::findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds) {

	int screenX, screenY;
	sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(root->quadRect.getPosition().x / TILE_SIZE, root->quadRect.getPosition().y / TILE_SIZE));
	cam.WorldToScreen(isometricPosition.x + cam.window.getSize().x / 2, isometricPosition.y, screenX, screenY);

	int sizeX = root->quadRect.getSize().x * cam.scaleX;
	int sizeY = (root->quadRect.getSize().y / 2 + (TILE_SIZE / 2) * MAX_TILE_DEPTH) * cam.scaleY;

	sf::IntRect isometricNodeRect(screenX - sizeX / 2, screenY, sizeX, sizeY);

	if (!viewbounds.intersects(isometricNodeRect))
		return;

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
		sf::Sprite sprite = *currentCell.sprite;

		sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(currentCell.x, currentCell.y));
		sprite.setPosition(isometricPosition.x, isometricPosition.y - currentCell.YOffset);

		sprites.push_back(sprite);

		if (currentCell.Objects.size() != 0)
		{
			for (int i = 0; i < currentCell.Objects.size(); i++)
			{
				sf::Sprite _sprite = *currentCell.Objects[i].getSprite();

				sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(currentCell.Objects[i].getPosX(), currentCell.Objects[i].getPosY()));
				_sprite.setPosition(isometricPosition.x, isometricPosition.y - currentCell.YOffset);

				sprites.push_back(_sprite);
			}
		}
	}
	std::cout << sprites.size() << std::endl;
	return sprites;
}