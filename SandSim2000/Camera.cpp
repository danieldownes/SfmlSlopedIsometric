#include "Camera.h"

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "Pan and Zoom", sf::Style::Fullscreen) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);

    sf::Vector2u screenSize = window.getSize();
    offsetX = -(screenSize.x / 2.0f);
    offsetY = -(screenSize.y / 2.0f);

    initialiseGrassTextures();
}

bool Camera::Update() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return false;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            return false;
        }
        Zoom(event);
    }
    Pan(event);
}

void Camera::WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY) 
{
    outScreenX = (int)((worldX - offsetX) * scaleX);
    outScreenY = (int)((worldY - offsetY) * scaleY);
}

void Camera::ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY)
{
    outWorldX = ((float)screenX / scaleX) + offsetX;
    outWorldY = ((float)screenY / scaleY) + offsetY;
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
    else {
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
    /*if (offsetX > 12000) offsetX = 12000;
    if (offsetX < -12000) offsetX = -12000;
    if (offsetY > 10500) offsetY = 10500;
    if (offsetY < -500) offsetY = -500;*/
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
        if (scaleX > 3.0f) scaleX = 3.0f;
        else if (scaleX < 0.5f) scaleX = 0.5f;
        else scaleChanged = true;

        if (scaleY > 3.0f) scaleY = 3.0f;
        else if (scaleY < 0.5f) scaleY = 0.5f;
        else scaleChanged = true;

        if (scaleChanged) {
            float worldXAfterZoom, worldYAfterZoom;
            ScreenToWorld(mousePos.x, mousePos.y, worldXAfterZoom, worldYAfterZoom);

            offsetX += worldXBeforeZoom - worldXAfterZoom;
            offsetY += worldYBeforeZoom - worldYAfterZoom;

            //Clamp the offset so we can't pan off to infinity and beyond
            /*if (offsetX > 12000) offsetX = 12000;
            if (offsetX < -12000) offsetX = -12000;
            if (offsetY > 10500) offsetY = 10500;
            if (offsetY < -500) offsetY = -500;*/
        }
    }
}


void Camera::Draw(std::vector<std::vector<BattlefieldCell>::iterator>& gameScene) {
    window.clear(sf::Color::Black);

    GridGenerator gridGenerator;
    int centerOffsetX = window.getSize().x / 2;

    for (auto iter = gameScene.begin(); iter != gameScene.end(); iter++) {
        BattlefieldCell cell = **iter;

        sf::Sprite sprite = sf::Sprite();

        //Sets the texture of the sprite to the corresponding Grass tile
        sprite.setTexture(GrassTexture[(2 - cell.terrain.depth)]);
        sprite.setTextureRect(sf::IntRect(0, 0, 100, 100 + 50 * (2 - cell.terrain.depth)));
        
        // Get the sprite position
        int screenX, screenY;
        sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(cell.x, cell.y));
        WorldToScreen(isometricPosition.x + centerOffsetX, isometricPosition.y - 50 * (2 - cell.terrain.depth), screenX, screenY);
        
        sprite.setPosition(static_cast<float>(screenX), static_cast<float>(screenY));
        sprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
        
        window.draw(sprite);
    }

    window.display();
}

//void Camera::drawRectFromQuadTreeNode(
//    QuadTree* node, unsigned int maxDepth, sf::FloatRect& viewBounds, GridGenerator& gridGenerator, 
//    int& centerOffsetX, int& OffsetY
//) {
//
//    if (typeid(*node) == typeid(QuadTreeLeaf)) {
//        fillRectWithDuplicateSprites((QuadTreeLeaf*)node, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
//    } else {
//        std::array<QuadTree*, 4> children = ((QuadTreeInternal*)node)->getChildren();
//        for (QuadTree* child : children)
//            drawRectFromQuadTreeNode(child, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
//    }
//}
//
//void Camera::fillRectWithDuplicateSprites(
//    sf::FloatRect rect, TerrainTile terrain, unsigned int depth, unsigned int maxDepth, 
//    sf::FloatRect& viewBounds, GridGenerator& gridGenerator, int& centerOffsetX, int& OffsetY
//) {
//    if (depth == maxDepth) {
//        sf::Sprite sprite = sf::Sprite();
//
//        //Sets the texture of the sprite to the corresponding Grass tile
//        sprite.setTexture(GrassTexture[terrain.height]);
//        sprite.setTextureRect(sf::IntRect(0, 0,
//            rect.getSize().x, rect.getSize().y + (terrain.height * 50)
//        ));
//
//        // Get the sprite position
//        int screenX, screenY;
//        sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(rect.getPosition().x / 100.f, rect.getPosition().y / 100.f));
//        WorldToScreen(isometricPosition.x + centerOffsetX, (isometricPosition.y * terrain.z) + OffsetY - 50 * terrain.height, screenX, screenY);
//
//        sprite.setPosition(static_cast<float>(screenX - (rect.getSize().x / 2) * scaleX), static_cast<float>(screenY));
//        sprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
//
//        window.draw(sprite);
//    } else {
//        float posX = rect.getPosition().x;
//        float posY = rect.getPosition().y;
//
//        float newSizeX = rect.getSize().x / 2;
//        float newSizeY = rect.getSize().y / 2;
//
//        fillRectWithDuplicateSprites(sf::FloatRect(posX,            posY,            newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
//        fillRectWithDuplicateSprites(sf::FloatRect(posX + newSizeX, posY,            newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
//        fillRectWithDuplicateSprites(sf::FloatRect(posX,            posY + newSizeY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
//        fillRectWithDuplicateSprites(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY);
//    }
//}
//
//void Camera::fillRectWithDuplicateSprites(
//    QuadTreeLeaf* node, unsigned int maxDepth, sf::FloatRect& viewBounds,
//    GridGenerator& gridGenerator, int& centerOffsetX, int& OffsetY, GameState& gameState)
//{
//    sf::FloatRect rect = node->getQuadRect();
//    BattlefieldCell cell = *node->getIterator();
//    unsigned int depth = node->getDepth();
//
//    if (depth == maxDepth) {
//        int screenX, screenY;
//        sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(rect.getPosition().x / 100.f, rect.getPosition().y / 100.f));
//        WorldToScreen(isometricPosition.x + centerOffsetX, isometricPosition.y + OffsetY, screenX, screenY);
//
//        if (cell.terrain.terrain == "default") {
//            sf::Sprite sprite = sf::Sprite();
//
//            sprite.setTexture(GrassTexture[0]);
//            sprite.setTextureRect(sf::IntRect(0, 0,
//                rect.getSize().x, rect.getSize().y
//            ));
//
//            sprite.setPosition(static_cast<float>(screenX - (rect.getSize().x / 2) * scaleX), static_cast<float>(screenY));
//            sprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
//
//            window.draw(sprite);
//        }
//
//        /*if (!node->getAgents().empty()) {
//            sf::Sprite agentSprite = sf::Sprite();
//
//            agentSprite.setTexture(AgentTexture);
//            agentSprite.setTextureRect(sf::IntRect(0, 0,
//                rect.getSize().x, rect.getSize().y
//            ));
//
//            agentSprite.setPosition(static_cast<float>(screenX - (rect.getSize().x / 2) * scaleX), static_cast<float>(screenY));
//            agentSprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
//
//            window.draw(agentSprite);
//        }*/
//    }
//    else {
//        float posX = rect.getPosition().x;
//        float posY = rect.getPosition().y;
//
//        float newSizeX = rect.getSize().x / 2;
//        float newSizeY = rect.getSize().y / 2;
//
//        fillRectWithDuplicateSprites(sf::FloatRect(posX, posY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY, gameState);
//        fillRectWithDuplicateSprites(sf::FloatRect(posX + newSizeX, posY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY, gameState);
//        fillRectWithDuplicateSprites(sf::FloatRect(posX, posY + newSizeY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY, gameState);
//        fillRectWithDuplicateSprites(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), terrain, depth + 1, maxDepth, viewBounds, gridGenerator, centerOffsetX, OffsetY, gameState);
//    }
//}

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

//void Camera::initialiseAgentTexture() {
//    //TEMP: Use red selection square to show agent positions
//    const std::string filePath = "../resources/images/Terrain/selected.png";
//    if (!AgentTexture.loadFromFile(filePath))
//    {
//        std::cerr << "[TEXTURE][AGENT][FAILURE] File Path: " << filePath << std::endl;
//        return;
//    }
//}
