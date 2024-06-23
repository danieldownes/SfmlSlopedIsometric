#pragma once
#include <SFML/System.hpp>

class GridGenerator
{
public:
    GridGenerator();
    sf::Vector2f cartesianToIsometricTransform(const sf::Vector2f& cartesianPosition);
    sf::Vector2f isometricToCartesianTransform(const sf::Vector2i& isometricPosition);
    sf::Vector2f mouseToIsometric(const sf::Vector2i& mouseCoords);
    sf::Vector2f transformToIsometric(const float worldX, const float worldY);
    sf::Vector2f isometricFromMouse(const sf::Vector2i& mouseCoords);
    sf::Vector2f transformToIsometricGrid(const float worldX, const float worldY);
    sf::Vector2f cellSelector(const sf::Vector2i cartesianCell);

    sf::Vector2f mouseCellCalc(const sf::Vector2i mouseCoord);
    int isInsideTriangle(sf::Vector2f mousePos);
    sf::Vector2f isometricToScreenPosition(sf::Vector2f isometricPosition);
private:

};


