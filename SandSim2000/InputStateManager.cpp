#include "InputStateManager.h"

InputStateManager::InputStateManager() {}
InputStateManager::~InputStateManager() {}

InputStateManager& InputStateManager::getInstance() {
    static InputStateManager instance;
    return instance;
}

InputState& InputStateManager::updateInputState(sf::Window& window, InputState& inputState) {
    inputState.isEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    inputState.isSpaceBarPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    inputState.isTPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::T);


    inputState.mousePosition = sf::Mouse::getPosition(window);
    inputState.isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    inputState.isRightMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    inputState.isMiddleMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

    return inputState;
}
