#pragma once
#include <SFML/Window.hpp>

struct InputState
{
    bool isEscapePressed;
    bool isSpaceBarPressed;
    bool isQPressed;
    bool isWPressed;
    bool isEPressed;
    bool isRPressed;
    bool isAPressed;
    bool isSPressed;
    bool isDPressed;
    bool isFPressed;
    bool isZPressed;
    bool isXPressed;
    bool isCPressed;
    bool isVPressed;

    sf::Vector2i mousePosition;
    sf::Vector2i selectedCell;
    bool isLeftMouseButtonPressed;
    bool isRightMouseButtonPressed;
    bool isMiddleMouseButtonPressed;
};
