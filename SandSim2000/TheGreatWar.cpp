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