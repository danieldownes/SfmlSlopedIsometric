/*
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MapEditor.h"
#include "Agent.h"
#include "VehicleAgent.h"
#include "InfantryAndCavalryAgent.h"
#include <string>
#include "GameState.h"
#include "AnimationManager.h"
#include "MovementManager.h"

constexpr double PI = 3.14159265358979323846;
const float windowWidth = 800.0f;
const float windowHeight = 600.0f;

struct MainMenuOptions
{
    bool mainMenu = true;
    bool play = false;
    bool editMap = false;
};

void mainMenu(sf::RenderWindow& window, MainMenuOptions& options) {
    std::string selectedMenuOption = "";
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
    }

    window.clear(sf::Color::Black);

    sf::Font font;
    if (!font.loadFromFile("../resources/Fonts/WorldAtWar.ttf")) std::cerr << "Failed to load font!" << std::endl;
    sf::Text title("The Great War", font);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition((window.getSize().x - title.getLocalBounds().width) / 2, 50);
    window.draw(title);

    sf::Texture backgroundImgTexture;
    if (!backgroundImgTexture.loadFromFile("../resources/images/Utilities/OpeningImage.jpg")) {
        std::cerr << "Failed to load Opening Image texture!" << std::endl;
    }

    sf::Sprite backgroundImgSprite(backgroundImgTexture);
    backgroundImgSprite.setOrigin(backgroundImgSprite.getLocalBounds().width / 2, backgroundImgSprite.getLocalBounds().height / 2);
    backgroundImgSprite.setPosition(window.getSize().x / static_cast<float>(2), window.getSize().y / static_cast<float>(2));
    window.draw(backgroundImgSprite);

    sf::RectangleShape play(sf::Vector2f(350, 150));
    sf::RectangleShape mapEditor(sf::Vector2f(350, 150));

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("../resources/images/Utilities/MenuButtonBorder.png")) {
        std::cerr << "Failed to load button texture!" << std::endl;
        return;
    }
    play.setPosition((window.getSize().x - 2 * play.getSize().x) / 3, window.getSize().y - 200);
    play.setTexture(&buttonTexture);
    sf::FloatRect playButtonBounds = play.getGlobalBounds();
    window.draw(play);

    mapEditor.setPosition((window.getSize().x - 2 * mapEditor.getSize().x) / 3, window.getSize().y - 200);
    mapEditor.setTexture(&buttonTexture);
    mapEditor.setPosition(2 * (window.getSize().x - 2 * mapEditor.getSize().x) / 3 + mapEditor.getSize().x, window.getSize().y - 200);
    sf::FloatRect mapEditorButtonBounds = mapEditor.getGlobalBounds();
    window.draw(mapEditor);

    sf::Text playText("Play", font);
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(play.getPosition().x + (play.getSize().x - playText.getLocalBounds().width) / 2,
        play.getPosition().y + (play.getSize().y - playText.getLocalBounds().height) / 2);
    window.draw(playText);

    sf::Text mapEditorText("Map Editor", font);
    mapEditorText.setCharacterSize(30);
    mapEditorText.setFillColor(sf::Color::White);
    mapEditorText.setPosition(mapEditor.getPosition().x + (mapEditor.getSize().x - mapEditorText.getLocalBounds().width) / 2,
        mapEditor.getPosition().y + (mapEditor.getSize().y - mapEditorText.getLocalBounds().height) / 2);
    window.draw(mapEditorText);



    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    bool wasLeftButtonPressedLastFrame = false;
    bool isLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (playButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        if (isLeftButtonPressed && !wasLeftButtonPressedLastFrame) {
            options = { false, true, false };
            window.clear(sf::Color::Black);
        }
    }

    if (mapEditorButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        if (isLeftButtonPressed && !wasLeftButtonPressedLastFrame) {
            options = { false, false, true };
            window.clear(sf::Color::Black);
        }
    }

    window.display();
}

void setInitialCursorIcon(sf::RenderWindow& window)
{
    sf::Image cursorImage;
    if (!cursorImage.loadFromFile("../resources/images/Utilities/cursorIcon.png"))
    {
        throw std::runtime_error("Failed to load cursor image!");
    }
    sf::Cursor cursor;
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
    window.setMouseCursor(cursor);
}

void TemporaryTestPathfinding(MovementManager movementManager)
{
    sf::Vector2i sourcePosition(7, 10);
    std::cout << "Source position: " << sourcePosition.x << ", " << sourcePosition.y << std::endl;

    sf::Vector2i targetPosition(2, 2);
    std::cout << "Target position: " << targetPosition.x << ", " << targetPosition.y << std::endl;

    std::vector<sf::Vector2i> path = movementManager.AStarPathFind(sourcePosition, targetPosition);
    if (!path.empty()) {
        std::cout << "Path found: " << std::endl;
        for (sf::Vector2i v : path)
            if (v == path.front())
                std::cout << v.x << "," << v.y;
            else
                std::cout << " -> " << v.x << "," << v.y;
    }

    sourcePosition = sf::Vector2i(3, 4);
    std::cout << "Source position: " << sourcePosition.x << ", " << sourcePosition.y << std::endl;

    targetPosition = sf::Vector2i(11, 10);
    std::cout << "Target position: " << targetPosition.x << ", " << targetPosition.y << std::endl;

    path = movementManager.AStarPathFind(sourcePosition, targetPosition);
    if (!path.empty()) {
        std::cout << "Path found: " << std::endl;
        for (sf::Vector2i v : path)
            if (v == path.front())
                std::cout << v.x << "," << v.y;
            else
                std::cout << " -> " << v.x << "," << v.y;
    }
}

void TemporaryPlayFunction(sf::RenderWindow* window)
{
    GameState gameState = GameState();
    AnimationManager animationManager = AnimationManager();
    MovementManager movementManager = MovementManager(gameState.mapSize);

    gameState.clearAndInitializeMap();

    std::cout << "initialized game" << std::endl;

    TemporaryTestPathfinding(movementManager);

    while (window->isOpen())
    {
        sf::Event e;

        while (window->pollEvent(e))
        {
            if (e.type == sf::Event::Closed) window->close();
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) window->close();

        }

        window->clear(sf::Color::Black);

        animationManager.renderTerrainMap(window, &gameState);

        window->display();
    }
}

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height), "The Great War", sf::Style::Fullscreen);
    setInitialCursorIcon(window);

    MainMenuOptions options;

    while (window.isOpen())
    {
        if (options.mainMenu)
        {
            mainMenu(window, options);
        }
        else if (options.play)
        {
            TemporaryPlayFunction(&window);
        }
        else if (options.editMap)
        {
            window.clear();
            MapEditor mapEditor;
            mapEditor.run(window);
        }
    }
    return 0;
}
*/

#include <SFML/Graphics.hpp>


class Camera {
public:
    Camera();

private:
    sf::RenderWindow window;
    sf::View view;

    float offsetX = 0.0f;
    float offsetY = 0.0f;

    float scaleX = 1.0f;
    float scaleY = 1.0f;

    bool mouseButtonPanning = false;
    bool edgePanning = false;


    float startPanX = 0.0f;
    float startPanY = 0.0f;

    float worldX = 0.0f;
    float worldY = 0.0f;

    int screenX = 0.0f;
    int screenY = 0.0f;

    void Pan(sf::Event& event);
    void Zoom(sf::Event& event);
    void WorldToScreen(float worldX, float worldY, int& screenX, int& screenY);
    void ScreenToWorld(int screenX, int screenY, float& worldX, float& worldY);
    void Draw();

public:
    void Run();
};

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "Pan and Zoom", sf::Style::Fullscreen) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Vector2u screenSize = window.getSize();
    offsetX = -(screenSize.x / 2.0f);
    offsetY = -(screenSize.y / 2.0f);
}


void Camera::WorldToScreen(float worldX, float worldY, int& screenX, int& screenY)
{
    screenX = (int)((worldX - offsetX) * scaleX);
    screenY = (int)((worldY - offsetY) * scaleY);
}

void Camera::ScreenToWorld(int screenX, int screenY, float& worldX, float& worldY)
{
    worldX = ((float)screenX / scaleX) + offsetX;
    worldY = ((float)screenY / scaleY) + offsetY;
}



void Camera::Pan(sf::Event& event) {
    const int edgeThreshold = 150;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2u windowSize = window.getSize();

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle) {
        mouseButtonPanning = true;
        startPanX = mousePos.x;
        startPanY = mousePos.y;
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle) {
        mouseButtonPanning = false;
    }

    if (mouseButtonPanning) {
        offsetX -= (mousePos.x - startPanX) / scaleX;
        offsetY -= (mousePos.y - startPanY) / scaleY;

        startPanX = mousePos.x;
        startPanY = mousePos.y;
    }


    float panSpeedX = 0.0f;
    float panSpeedY = 0.0f;

    if (mousePos.x <= edgeThreshold)
        panSpeedX = (edgeThreshold - mousePos.x) / (static_cast<float>(edgeThreshold) * scaleX);
    else if (mousePos.x >= static_cast<int>(windowSize.x) - edgeThreshold)
        panSpeedX = -(mousePos.x - (static_cast<int>(windowSize.x) - edgeThreshold)) / (static_cast<float>(edgeThreshold) * scaleX);

    if (mousePos.y <= edgeThreshold)
        panSpeedY = (edgeThreshold - mousePos.y) / (static_cast<float>(edgeThreshold) * scaleY);
    else if (mousePos.y >= static_cast<int>(windowSize.y) - edgeThreshold)
        panSpeedY = -(mousePos.y - (static_cast<int>(windowSize.y) - edgeThreshold)) / (static_cast<float>(edgeThreshold) * scaleY);

    if (panSpeedX != 0.0f || panSpeedY != 0.0f) {
        offsetX -= panSpeedX * 10;
        offsetY -= panSpeedY * 10;
    }
}




void Camera::Zoom(sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        float worldXBeforeZoom, worldYBeforeZoom;
        ScreenToWorld(mousePos.x, mousePos.y, worldXBeforeZoom, worldYBeforeZoom);

        if (event.mouseWheelScroll.delta > 0) {
            scaleX *= 1.05f;
            scaleY *= 1.05f;
        }
        else if (event.mouseWheelScroll.delta < 0) {
            scaleX *= 0.95f;
            scaleY *= 0.95f;
        }

        float worldXAfterZoom, worldYAfterZoom;
        ScreenToWorld(mousePos.x, mousePos.y, worldXAfterZoom, worldYAfterZoom);

        offsetX += worldXBeforeZoom - worldXAfterZoom;
        offsetY += worldYBeforeZoom - worldYAfterZoom;
    }
}


void Camera::Draw() {
    window.clear(sf::Color::Black);

    sf::RectangleShape square;
    square.setSize(sf::Vector2f(100 * scaleX, 100 * scaleY));
    square.setFillColor(sf::Color::Green);

    WorldToScreen(worldX, worldY, screenX, screenY);

    square.setPosition(static_cast<float>(screenX), static_cast<float>(screenY));

    window.draw(square);
    window.display();
}





void Camera::Run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            Zoom(event);
        }
        Pan(event);
        Draw();
    }
}


int main() {

    Camera camera;
    camera.Run();
    return 0;
}
