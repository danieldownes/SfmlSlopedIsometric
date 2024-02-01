#include "InputStateManager.h"

InputStateManager::InputStateManager() {}

InputStateManager::~InputStateManager() {}

InputStateManager& InputStateManager::getInstance() {
    static InputStateManager instance;
    return instance;
}

void InputStateManager::updateInputState(sf::Window& window) {
    state.isEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    state.isSpaceBarPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);


    state.mousePosition = sf::Mouse::getPosition(window);
    state.isLeftMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    state.isRightMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    state.isMiddleMouseButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Middle);


}

const InputState& InputStateManager::getInputState() const {
    return state;
}
