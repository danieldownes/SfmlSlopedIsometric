#include "Camera.h"

Camera::Camera()
    : window(sf::VideoMode::getDesktopMode(), "The Great War", sf::Style::Fullscreen) {
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
        Zoom(event);
    }
    const InputState& inputState = InputStateManager::getInstance().getInputState();

    if (inputState.isEscapePressed) {
        return false;
    }

    clickPan(inputState);
    scrollPan(inputState);
    snapPan(inputState);

    return true;
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

void Camera::clickPan(const InputState& inputState) {
    sf::Vector2i mousePos = inputState.mousePosition;
    sf::Vector2u windowSize = window.getSize();

    if (inputState.isMiddleMouseButtonPressed) {
        if (!mouseButtonPanning) {
            mouseButtonPanning = true;
            startPanX = mousePos.x;
            startPanY = mousePos.y;
        }
        else {
            offsetX -= (mousePos.x - startPanX) / scaleX;
            offsetY -= (mousePos.y - startPanY) / scaleY;

            startPanX = mousePos.x;
            startPanY = mousePos.y;
        }
    }
    else {
        mouseButtonPanning = false;
    }
}

void Camera::scrollPan(const InputState& inputState) {
    const int edgeThreshold = 150;
    sf::Vector2i mousePos = inputState.mousePosition;
    sf::Vector2u windowSize = window.getSize();

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


void Camera::snapPan(const InputState& inputState)
{
    //Once there are scenery and units on the battlefield, snap panning will be possible via hotkeys, snapping the camera to the position of a unit.
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
        }
    }
}

void Camera::Draw(std::set<std::vector<BattlefieldCell>::iterator>& gameScene) {
    window.clear(sf::Color::Black);

    GridGenerator gridGenerator;
    int centerOffsetX = window.getSize().x / 2;

    for (auto iter = gameScene.begin(); iter != gameScene.end(); iter++) {
        BattlefieldCell cell = **iter;

        sf::Sprite sprite = *cell.sprite;

        int screenX, screenY;
        sf::Vector2f isometricPosition = gridGenerator.cartesianToIsometricTransform(sf::Vector2f(cell.x, cell.y));
        WorldToScreen(isometricPosition.x + centerOffsetX, isometricPosition.y - cell.YOffset, screenX, screenY);
        
        sprite.setPosition(static_cast<float>(screenX - 50 * scaleX), static_cast<float>(screenY));
        sprite.setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
        
        window.draw(sprite);
    }

    window.display();
}