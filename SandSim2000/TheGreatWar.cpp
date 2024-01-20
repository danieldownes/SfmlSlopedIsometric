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

#include "GameState.h"
#include "GridGenerator.h"
#include <iostream>

class Camera {
public:
    Camera();

    void Run();
private:
    int count = 0;

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

    sf::Texture GrassTexture[3];

    void Pan(sf::Event& event);
    void Zoom(sf::Event& event);
    void WorldToScreen(float worldX, float worldY, int& screenX, int& screenY);
    void ScreenToWorld(int screenX, int screenY, float& worldX, float& worldY);
    void Draw(GameState* gameState);
    void drawRectFromQuadTreeNode(QuadTree* node, unsigned int maxDepth, sf::FloatRect& viewBounds,
        GridGenerator& gridGenerator, int& centerOffsetX, int& OffsetY);
    void fillRectWithDuplicateSprites(
        sf::FloatRect rect, TerrainTile terrain, unsigned int depth, unsigned int maxDepth,
        sf::FloatRect& viewBounds, GridGenerator& gridGenerator, int& centerOffsetX, int& OffsetY);
    void initialiseGrassTextures();
};

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "Pan and Zoom", sf::Style::Fullscreen) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);

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
    } else {
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

    //Clamp the offset so we can't pan off to infinity and beyond
    /*if (offsetX > 1500) offsetX = 1500;
    if (offsetX < -3000) offsetX = -3000;
    if (offsetY > 1000) offsetY = 1000;
    if (offsetY < -2500) offsetY = -2500;*/
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

        bool scaleChanged = false;

        //Clamp the zoom and prevent weird panning behaviour when zooming at these bounds
        if (scaleX > 4.0f) scaleX = 4.0f;
        else if (scaleX < 0.25f) scaleX = 0.25f; 
        else scaleChanged = true;

        if (scaleY > 4.0f) scaleY = 4.0f;
        else if (scaleY < 0.25f) scaleY = 0.25f; 
        else scaleChanged = true;

        if (scaleChanged) {
            float worldXAfterZoom, worldYAfterZoom;
            ScreenToWorld(mousePos.x, mousePos.y, worldXAfterZoom, worldYAfterZoom);

            offsetX += worldXBeforeZoom - worldXAfterZoom;
            offsetY += worldYBeforeZoom - worldYAfterZoom;

            //Clamp the offset so we can't pan off to infinity and beyond
            /*if (offsetX > 1500) offsetX = 1500;
            if (offsetX < -3000) offsetX = -3000;
            if (offsetY > 1000) offsetY = 1000;
            if (offsetY < -2500) offsetY = -2500;*/
        }
    }
}


void Camera::Draw(GameState* gameState) {
    count = 0;
    window.clear(sf::Color::Black);

    sf::FloatRect viewBounds(0, 0, window.getSize().x, window.getSize().y);

    GridGenerator gridGenerator;
    int centerOffsetX = window.getSize().x / 2;
    int OffsetY = 150;
    unsigned int maxDepth = (unsigned int)std::log2(gameState->mapSize);

    drawRectFromQuadTreeNode(gameState->getMapData(), maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
 
    window.display();

    std::cout << count << std::endl;
}

void Camera::drawRectFromQuadTreeNode(
    QuadTree* node, unsigned int maxDepth, sf::FloatRect& viewBounds, GridGenerator& gridGenerator, 
    int& centerOffsetX, int& OffsetY
) {
    sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(node->getQuadRect().getPosition().x / 100.f, node->getQuadRect().getPosition().y / 100.f));
    int screenX, screenY;
    WorldToScreen(isometricPosition.x + centerOffsetX, isometricPosition.y, screenX, screenY);

    sf::FloatRect isometricNodeRect(screenX - node->getQuadRect().getSize().x / 2, screenY, node->getQuadRect().getSize().x, node->getQuadRect().getSize().y);

    if (!viewBounds.intersects(isometricNodeRect))
        return;

    if (typeid(*node) == typeid(QuadTreeLeaf)) {
        fillRectWithDuplicateSprites(((QuadTreeLeaf*)node)->getQuadRect(), ((QuadTreeLeaf*)node)->getTerrainInfo(), ((QuadTreeLeaf*)node)->getDepth(), maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
    } else {
        std::array<QuadTree*, 4> children = ((QuadTreeInternal*)node)->getChildren();
        for (QuadTree* child : children)
            drawRectFromQuadTreeNode(child, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
    }
}

void Camera::fillRectWithDuplicateSprites(
    sf::FloatRect rect, TerrainTile terrain, unsigned int depth, unsigned int maxDepth, 
    sf::FloatRect& viewBounds, GridGenerator& gridGenerator, int& centerOffsetX, int& OffsetY
) {
    if (depth == maxDepth) {
        sf::Sprite sprite = sf::Sprite();

        //Sets the texture of the sprite to the corresponding Grass tile
        sprite.setTexture(GrassTexture[terrain.height]);
        sprite.setTextureRect(sf::IntRect(0, 0,
            rect.getSize().x, rect.getSize().y + (terrain.height * 50)
        ));

        // Set the sprite position
        sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(rect.getPosition().x / 100.f, rect.getPosition().y / 100.f));

        int screenX, screenY;
        WorldToScreen(isometricPosition.x + centerOffsetX, (isometricPosition.y * terrain.z) + OffsetY - 50 * terrain.height, screenX, screenY);

        sprite.setPosition(static_cast<float>(screenX - rect.getSize().x / 2), static_cast<float>(screenY));
        sprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));

        // Culling
        //if (viewBounds.intersects(sprite.getGlobalBounds())) {
            count++;
            window.draw(sprite);
        //}
    } else {
        float posX = rect.getPosition().x;
        float posY = rect.getPosition().y;

        float newSizeX = rect.getSize().x / 2;
        float newSizeY = rect.getSize().y / 2;

        fillRectWithDuplicateSprites(sf::FloatRect(posX,            posY,            newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
        fillRectWithDuplicateSprites(sf::FloatRect(posX + newSizeX, posY,            newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
        fillRectWithDuplicateSprites(sf::FloatRect(posX,            posY + newSizeY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
        fillRectWithDuplicateSprites(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
    }
}

void Camera::initialiseGrassTextures() {
    const std::string presetFilePath = "../resources/images/Terrain/Grass/grass";
    for (int i = 1; i < 4; i++)
    {
        const std::string filePath = presetFilePath + std::to_string(i) + ".png";
        if (!GrassTexture[i - 1].loadFromFile(filePath))
        {
            std::cerr << "[TEXTURE][GRASS][FAILURE] File Path: " << filePath << std::endl;
            return;
        }
    }
}

void Camera::Run() {
    GameState gameState = GameState();
    initialiseGrassTextures();

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
        Draw(&gameState);
    }
}


int main() {
    Camera camera;
    camera.Run();
    return 0;
}
