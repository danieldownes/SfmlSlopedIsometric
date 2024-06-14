#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include "InputState.h"
#include "SpriteManager.h"
#include "Tree.h"
#include "AgentManager.h"


int main() {
    SpriteManager sprites = SpriteManager();

    unsigned int mapSize = 16;
    GameStateManager gameStateManager = GameStateManager(mapSize * mapSize);

    AgentManager agentManager;

    InputState inputState;
    Camera camera;
    Scene scene;

    // Liam: Instead of setting the sprite to the Pathfinder Agent, please set the Red Baron sprite. 
    // I'm not fully tracking how you're updating the position of the Pathfinder Agent but 
    // in the Animation Manager please create functionality to pick the right part of the sprite sheet
    // depending on which direction the sprite is facing. This will require adding a "direction" property 
    // to the Agent class, 0-7 for directions. Then make sure the Pathfinder Agent Red Baron sprite
    // is facing in the right direction as it follows the path. 
    agentManager.placePathfinderAgent(sf::Vector2i(8, 8), &scene.gameScene, PathfinderAgent(8, 8, "PathfinderAgent"), gameStateManager);

    while (camera.window.isOpen()) {
        inputState = InputStateManager::getInstance().updateInputState(camera.window, inputState);
        /*
        sf::Event event;
        while (camera.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                camera.window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                camera.Zoom(event);
            }
        }
        */
        agentManager.onUpdate(inputState, &scene.gameScene, gameStateManager, camera, scene);

        if (!camera.Update(inputState)) { break; }
        scene.UpdateGameScene(camera, gameStateManager.getState(), inputState);
        camera.Draw(scene.buildGameScene(), inputState);
    }
    return 0;
}