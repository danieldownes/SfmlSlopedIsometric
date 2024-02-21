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


// Alpha Team Suggestions: An additional method should be added here that checks the objects within 
// the viewPort, gets their sprite using the SpriteManager and inserts them into the game scene.
// Right now the Camera::Draw() method bypasses the SpriteManager and gets terrain sprites directly.
// That will need refactored so that it only draws the sprites it receives from the Scene::gameScene property, 
// not get and draw like it currently does. 
// 
// Some boilerplate pseudo code to accomplish this below:


/*
void Scene::buildGameScene(take iterators from "findViewportIterators")
{
	// Build game scene based on the objects who's interators are covered by the viewport.
	// Pass Agent::unitType property to a new method in the SpriteManager which selects the correct 
	// spritesheet based on the unitType value.
	// Those sprite textures are inserted into the gameScene which the Camera::Draw() method will draw. 
}
*/