#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include "SpriteManager.h"
#include "Tree.h"
#include "SceneryManager.h"


int main() {
    SpriteManager sprites = SpriteManager();

    unsigned int mapSize = 16;
    GameStateManager gameStateManager = GameStateManager(mapSize * mapSize);

    SceneryManager sceneManager;

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
            //Josh: please move these conditions listening for events to the sceneryManager. Check my comments over there next. 
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousepos = InputStateManager::getInstance().getInputState().mousePosition;

                    float x; float y;

                    camera.ScreenToWorld(mousepos.x, mousepos.y, x, y);

                    gameStateManager.placeUnit(sf::Vector2f(x, y), &scene.gameScene, "RedBaron");
                }

                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2i mousepos = InputStateManager::getInstance().getInputState().mousePosition;

                    float x; float y;

                    camera.ScreenToWorld(mousepos.x, mousepos.y, x, y);

                    Tree tree(10,10);

                    sceneManager.placeScenery(sf::Vector2f(x, y), &scene.gameScene, tree, gameStateManager);
                }
            }
        }

        if (!camera.Update()) { break; }
        scene.UpdateGameScene(camera, gameStateManager.getState());
        camera.Draw(scene.buildGameScene());
    }
    return 0;
}

