#pragma once
#include <SFML/Window/Mouse.hpp>  
#include <SFML/Window/Keyboard.hpp>
#include "InputState.h"
#include <iostream>

class InputStateManager {
public:
    static InputStateManager& getInstance();

    InputState& updateInputState(sf::Window& window, InputState& state);

private:
    InputStateManager();
    ~InputStateManager();

    InputStateManager(const InputStateManager&) = delete;
    InputStateManager& operator=(const InputStateManager&) = delete;
    InputStateManager(InputStateManager&&) = delete;
    InputStateManager& operator=(InputStateManager&&) = delete;
};
