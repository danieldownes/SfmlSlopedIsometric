#include "MainMenu.h"
#include <iostream>

MenuOption displayMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/Diamond Gothic.ttf")) {
        std::cerr << "Error loading font\n";
        return MenuOption::Exit;
    }

    const int optionCount = 5;
    sf::Text menuOptions[optionCount];
    sf::RectangleShape borders[optionCount];
    std::string optionsText[] = { "1. Map Editor", "2. Skirmish", "3. Option 3", "4. Option 4", "5. Exit" };

    for (int i = 0; i < optionCount; ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setString(optionsText[i]);
        menuOptions[i].setCharacterSize(30);
        menuOptions[i].setFillColor(sf::Color::White);
        menuOptions[i].setPosition(100.0f, 100.0f + i * 50.0f);

        borders[i].setSize(sf::Vector2f(menuOptions[i].getGlobalBounds().width + 20, menuOptions[i].getGlobalBounds().height + 20));
        borders[i].setFillColor(sf::Color::Transparent);
        borders[i].setOutlineColor(sf::Color::White);
        borders[i].setOutlineThickness(2);
        borders[i].setPosition(menuOptions[i].getPosition().x - 10, menuOptions[i].getPosition().y - 10);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return MenuOption::Exit;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < optionCount; ++i) {
                        if (borders[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            return static_cast<MenuOption>(i);
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Num1:
                    return MenuOption::MapEditor;
                case sf::Keyboard::Num2:
                    return MenuOption::Skirmish;
                case sf::Keyboard::Num3:
                    return MenuOption::Option3;
                case sf::Keyboard::Num4:
                    return MenuOption::Option4;
                case sf::Keyboard::Num5:
                    return MenuOption::Exit;
                default:
                    break;
                }
            }
        }

        window.clear();
        for (int i = 0; i < optionCount; ++i) {
            window.draw(borders[i]);
            window.draw(menuOptions[i]);
        }
        window.display();
    }
    return MenuOption::Exit;
}
