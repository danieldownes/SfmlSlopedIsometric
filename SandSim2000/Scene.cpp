#include "Scene.h"

#define MAX_TILE_DEPTH 5
#define TILE_SIZE 100
#define CAMERA_BORDER_WIDTH 0

Scene::Scene() {}

void Scene::UpdateGameScene(Camera& cam, GameState& gameState) {
	GridGenerator gridGenerator;
	sf::IntRect viewbounds(CAMERA_BORDER_WIDTH, CAMERA_BORDER_WIDTH, cam.window.getSize().x - 2 * CAMERA_BORDER_WIDTH, cam.window.getSize().y - 3 * CAMERA_BORDER_WIDTH);

	gameScene.clear();
	findViewportIterators(gameState.quadTree, cam, gridGenerator, viewbounds);
}

void Scene::findViewportIterators(QuadTree* root, Camera& cam, GridGenerator& gridGenerator, sf::IntRect& viewbounds) {
	//Ensure first that the current QuadTree node is actually onscreen
	int screenX, screenY;
	sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(root->quadRect.getPosition().x / TILE_SIZE, root->quadRect.getPosition().y / TILE_SIZE));
	cam.WorldToScreen(isometricPosition.x + cam.window.getSize().x / 2, isometricPosition.y - (TILE_SIZE / 2) * MAX_TILE_DEPTH, screenX, screenY);

	int sizeX = root->quadRect.getSize().x * cam.scaleX;
	int sizeY = (root->quadRect.getSize().y + (TILE_SIZE / 2) * MAX_TILE_DEPTH) * cam.scaleY;

	sf::IntRect isometricNodeRect(screenX - sizeX / 2, screenY, sizeX, sizeY);

	if (!viewbounds.intersects(isometricNodeRect))
		return;

	//If we are still going, dive into children to find iterators
	if (typeid(*root) == typeid(QuadTreeLeaf)) {
		gameScene.push_back(((QuadTreeLeaf*)root)->iter);
	} else {
		for (QuadTree* child : ((QuadTree*)root)->children)
			findViewportIterators(child, cam, gridGenerator, viewbounds);
	}
}