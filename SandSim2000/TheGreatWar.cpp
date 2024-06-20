#include "TheGreatWar.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");

    MenuOption selectedOption = displayMenu(window);
    if (selectedOption == MenuOption::Exit)
        return 0;

    // Initialize Components
    unsigned int mapSize = 16;
    SpriteManager sprites = SpriteManager();
    GameStateManager gameStateManager = GameStateManager(mapSize * mapSize);
    AgentManager agentManager = AgentManager();
    InputState inputState = InputState();
    Camera camera;
    Scene scene;

    if (selectedOption == MenuOption::MapEditor)
        std::cout << "Map Editor selected\n";
    
    else if (selectedOption == MenuOption::Skirmish)
        agentManager.placePathfinderAgent(sf::Vector2i(8, 8), &scene.gameScene,
            PathfinderAgent(8, 8, "PathfinderAgent"), gameStateManager);

    while (window.isOpen())
    {
        inputState = InputStateManager::getInstance().updateInputState(window, inputState);

        agentManager.onUpdate(inputState, &scene.gameScene, gameStateManager, camera, scene);

        if (!camera.Update(inputState))
            break;

        scene.UpdateGameScene(camera, gameStateManager.getState(), inputState);
        camera.Draw(scene.buildGameScene(), inputState);

        window.display();
    }
    return 0;
}
