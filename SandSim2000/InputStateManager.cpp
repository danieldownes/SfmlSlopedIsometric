#include "InputStateManager.h"

InputStateManager::InputStateManager() {}

InputStateManager::~InputStateManager() {}

InputStateManager& InputStateManager::getInstance() {
    static InputStateManager instance;
    return instance;
}

void InputStateManager::updateInputState() {
    state.isEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    state.isSpaceBarPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

const InputState& InputStateManager::getInputState() const {
    return state;
}
