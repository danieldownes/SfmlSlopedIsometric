#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "InputState.h"

class InputStateManager
{
   public:
	static InputStateManager& getInstance();

	InputState& updateInputState(sf::Window& window, InputState& inputState);

   private:
	InputStateManager();
	~InputStateManager();

	InputStateManager(const InputStateManager&) = delete;
	InputStateManager& operator=(const InputStateManager&) = delete;
	InputStateManager(InputStateManager&&) = delete;
	InputStateManager& operator=(InputStateManager&&) = delete;
};
