#include "Camera.h"

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "Pan and Zoom", sf::Style::Fullscreen) {
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);

    sf::Vector2u screenSize = window.getSize();
    offsetX = -(screenSize.x / 2.0f);
    offsetY = -(screenSize.y / 2.0f);
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
        if (scaleX > 2.0f) scaleX = 2.0f;
        else if (scaleX < 0.5f) scaleX = 0.5f;
        else scaleChanged = true;

        if (scaleY > 2.0f) scaleY = 2.0f;
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

void Camera::Draw(std::set<std::vector<BattlefieldCell>::iterator>& gameScene) {
    window.clear(sf::Color::Black);

    GridGenerator gridGenerator;
    int centerOffsetX = window.getSize().x / 2;

    for (auto iter = gameScene.begin(); iter != gameScene.end(); iter++) {
        BattlefieldCell cell = **iter;

        sf::Sprite sprite = sf::Sprite();

        sprite.setTexture(*cell.texture);
        
        int screenX, screenY;
        sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(cell.x, cell.y));
        WorldToScreen(isometricPosition.x + centerOffsetX, isometricPosition.y - cell.YOffset, screenX, screenY);
        
        sprite.setPosition(static_cast<float>(screenX - 50 * scaleX), static_cast<float>(screenY));
        sprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
        
        window.draw(sprite);
    }

    window.display();
}