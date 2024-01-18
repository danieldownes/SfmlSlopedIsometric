#pragma once
#include "InputState.h"

class InputStateManager {
public:
    static InputStateManager& getInstance();

    void updateInputState();
    const InputState& getInputState() const;

private:
    InputState state;
    InputStateManager();

    InputStateManager(const InputStateManager&) = delete;
    InputStateManager& operator=(const InputStateManager&) = delete;
    InputStateManager(InputStateManager&&) = delete;
    InputStateManager& operator=(InputStateManager&&) = delete;
};
