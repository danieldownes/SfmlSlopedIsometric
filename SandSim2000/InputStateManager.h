#pragma once
#include <SFML/Window/Mouse.hpp>  
#include <SFML/Window/Keyboard.hpp>
#include "InputState.h"
#include <iostream>

class InputStateManager {
public:
    static InputStateManager& getInstance();

    void updateInputState(sf::Window& window);
    const InputState& getInputState() const;

private:
    InputState state;
    InputStateManager();
    ~InputStateManager();

    InputStateManager(const InputStateManager&) = delete;
    InputStateManager& operator=(const InputStateManager&) = delete;
    InputStateManager(InputStateManager&&) = delete;
    InputStateManager& operator=(InputStateManager&&) = delete;
};
