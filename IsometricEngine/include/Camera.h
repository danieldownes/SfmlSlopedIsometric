#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <set>

#include "BattlefieldCell.h"
#include "GameStateManager.h"
#include "GridGenerator.h"
#include "InputState.h"
#include "InputStateManager.h"

class Camera
{
   public:
    Camera();

    void Update(float deltaTime, InputState& state);
    void Draw(std::vector<sf::Sprite> sprites, const InputState& state);

    void WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY);
    void ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY);

    void Zoom(sf::Event& event);
    void SetOffset(sf::Vector2f offset);

    sf::RenderWindow window;

    sf::Vector2f Offset;
    sf::Vector2f Scale = sf::Vector2f(1.f, 1.f);

    sf::Vector2u screenSize;
    sf::Vector2f selectedCell;

   private:
    sf::View view;

    bool mouseButtonPanning = false;
    bool edgePanning = false;

    sf::Vector2f panStartDrag;

    float worldX = 0.f;
    float worldY = 0.f;

    int screenX = 0;
    int screenY = 0;

    void clickPan(const InputState& inputState);
    void scrollPan(float deltaTime, const InputState& inputState);
};
