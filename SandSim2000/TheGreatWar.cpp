#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include "SpriteManager.h"

//Test

int main() {
    SpriteManager sprites = SpriteManager();

    unsigned int mapSize = 16;
    GameStateManager gameStateManager = GameStateManager(mapSize * mapSize);

    Camera camera;
    Scene scene;

    while (camera.window.isOpen()) {
        InputStateManager::getInstance().updateInputState(camera.window);

        sf::Event event;
        while (camera.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                camera.window.close();
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                camera.Zoom(event);
            }
        }
        if (!camera.Update()) { break; }
        scene.UpdateGameScene(camera, gameStateManager.getState());
        camera.Draw(scene.gameScene);
    }
    return 0;
}

