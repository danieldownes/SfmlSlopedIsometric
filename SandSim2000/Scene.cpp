#include "Scene.h"

#define MAX_TILE_DEPTH 5
#define TILE_SIZE 100
#define CAMERA_BORDER_WIDTH 300

Scene::Scene() {}

void Scene::UpdateGameScene(Camera& cam, GameState& gameState) {
	GridGenerator gridGenerator;
	gameScene = findViewportIterators(gameState.quadTree, cam, gridGenerator);
}

std::vector<std::vector<BattlefieldCell>::iterator> Scene::findViewportIterators(GameState::QuadTree* root, Camera& cam, GridGenerator& gridGenerator) {
	//Ensure first that the current QuadTree node is actually onscreen
	int screenX, screenY;
	sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(root->getQuadRect().getPosition().x / TILE_SIZE, root->getQuadRect().getPosition().y / TILE_SIZE));
	cam.WorldToScreen(isometricPosition.x + cam.window.getSize().x / 2, isometricPosition.y - (TILE_SIZE / 2) * MAX_TILE_DEPTH, screenX, screenY);

	int sizeX = root->getQuadRect().getSize().x * cam.scaleX;
	int sizeY = (root->getQuadRect().getSize().y + (TILE_SIZE / 2) * MAX_TILE_DEPTH) * cam.scaleY;

	sf::IntRect isometricNodeRect(screenX - sizeX / 2, screenY, sizeX, sizeY);
	sf::IntRect viewbounds(CAMERA_BORDER_WIDTH, CAMERA_BORDER_WIDTH, cam.window.getSize().x - 2 * CAMERA_BORDER_WIDTH, cam.window.getSize().y - 3 * CAMERA_BORDER_WIDTH);

	if (!viewbounds.intersects(isometricNodeRect))
		return std::vector<std::vector<BattlefieldCell>::iterator>();

	//If we are still going, dive into children to find iterators
	if (typeid(*root) == typeid(GameState::QuadTreeLeaf))
		return std::vector<std::vector<BattlefieldCell>::iterator>({ ((GameState::QuadTreeLeaf*)root)->getIterator() });
	else {
		std::vector<std::vector<BattlefieldCell>::iterator> iters;
		for (GameState::QuadTree* child : ((GameState::QuadTree*)root)->getChildren()) {
			std::vector<std::vector<BattlefieldCell>::iterator> childIters = findViewportIterators(child, cam, gridGenerator);
			iters.insert(iters.end(), childIters.begin(), childIters.end());
		}
		return iters;
	}
}