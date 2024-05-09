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

    Camera camera;
    Scene scene;

    InputState state;

    while (camera.window.isOpen()) {
        state = InputStateManager::getInstance().updateInputState(camera.window, state);

        sf::Event event;
        while (camera.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                camera.window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                camera.Zoom(event);
            }
        }
        agentManager.onUpdate(state, &scene.gameScene, gameStateManager, camera, scene);

        if (!camera.Update(state)) { break; }
        scene.UpdateGameScene(camera, gameStateManager.getState());
        camera.Draw(scene.buildGameScene());
    }
    return 0;
}