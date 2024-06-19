#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"
#include "Scene.h"
#include "InputStateManager.h"
#include "InputState.h"
#include "SpriteManager.h"
#include "Tree.h"
#include "AgentManager.h"

enum class MenuOption { MapEditor, Skirmish, Option3, Option4, Exit };

MenuOption displayMenu(sf::RenderWindow& window) {
    while (window.isOpen()) {
        window.clear();
        // Display menu options
        // This is a placeholder, you would typically render text or buttons here
        std::cout << "1. Map Editor\n2. Skirmish\n3. Option 3\n4. Option 4\n5. Exit\n";
        std::cout << "Select an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: return MenuOption::MapEditor;
        case 2: return MenuOption::Skirmish;
        case 3: return MenuOption::Option3;
        case 4: return MenuOption::Option4;
        case 5: return MenuOption::Exit;
        default: std::cout << "Invalid option, please try again.\n";
        }
    }
    return MenuOption::Exit;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");

    // Display menu and get selected option
    MenuOption selectedOption = displayMenu(window);
    if (selectedOption == MenuOption::Exit) {
        return 0;
    }

    SpriteManager sprites = SpriteManager();
    unsigned int mapSize = 16;
    GameStateManager gameStateManager = GameStateManager(mapSize * mapSize);
    AgentManager agentManager;
    InputState inputState;
    Camera camera;
    Scene scene;

    // Initialize based on selected option
    if (selectedOption == MenuOption::MapEditor) {
        // Initialize map editor
        // For now, we'll just print a message
        std::cout << "Map Editor selected\n";
    }
    else if (selectedOption == MenuOption::Skirmish) {
        // Initialize skirmish
        agentManager.placePathfinderAgent(sf::Vector2i(8, 8), &scene.gameScene, PathfinderAgent(8, 8, "PathfinderAgent"), gameStateManager);
    }

    while (window.isOpen()) {
        inputState = InputStateManager::getInstance().updateInputState(window, inputState);

        agentManager.onUpdate(inputState, &scene.gameScene, gameStateManager, camera, scene);

        if (!camera.Update(inputState)) { break; }
        scene.UpdateGameScene(camera, gameStateManager.getState(), inputState);
        camera.Draw(scene.buildGameScene(), inputState);

        window.display();
    }
    return 0;
}
