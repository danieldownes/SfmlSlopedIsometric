#include "Camera.h"

Camera::Camera() : window(sf::VideoMode::getDesktopMode(), "The Great War", sf::Style::Fullscreen)
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorGrabbed(true);

    screenSize = window.getSize();
    SetOffset(sf::Vector2f(screenSize.x / 2.0, screenSize.y / 2.0f));
}

void Camera::Update(float deltaTime, InputState& state)
{
    sf::Event event;
    while (window.pollEvent(event))
    { }
    const InputState& inputState = state;

    clickPan(inputState);
    scrollPan(deltaTime, inputState);
}

void Camera::Zoom(sf::Event& event)
{
    if (event.type != sf::Event::MouseWheelScrolled)
        return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float worldXBeforeZoom, worldYBeforeZoom;
    ScreenToWorld(mousePos.x, mousePos.y, worldXBeforeZoom, worldYBeforeZoom);

    if (event.mouseWheelScroll.delta > 0)
        Scale *= 1.05f;

    else if (event.mouseWheelScroll.delta < 0)
        Scale *= 0.95f;

    bool scaleChanged = false;

    if (Scale.x > 2.0f)
        Scale.x = 2.0f;
    else if (Scale.x < 0.5f)
        Scale.x = 0.5f;
    else
        scaleChanged = true;

    if (Scale.y > 2.0f)
        Scale.y = 2.0f;
    else if (Scale.y < 0.5f)
        Scale.y = 0.5f;
    else
        scaleChanged = true;

    if (scaleChanged)
    {
        float worldXAfterZoom, worldYAfterZoom;
        ScreenToWorld(mousePos.x, mousePos.y, worldXAfterZoom, worldYAfterZoom);

        Offset.x += worldXBeforeZoom - worldXAfterZoom;
        Offset.y += worldXBeforeZoom - worldXAfterZoom;
    }
}

void Camera::SetOffset(sf::Vector2f offset)
{
    this->Offset = offset;
}

void Camera::WorldToScreen(float worldX, float worldY, int& outScreenX, int& outScreenY)
{
    outScreenX = (int)((worldX - Offset.x) * Scale.x);
    outScreenY = (int)((worldY - Offset.y) * Scale.y);
}

void Camera::ScreenToWorld(int screenX, int screenY, float& outWorldX, float& outWorldY)
{
    // TODO: Remove hard coded resolution
    outWorldX = (((float)screenX / Scale.x) + Offset.x) + ((1920.f - screenSize.x) / 2.f);
    outWorldY = (((float)screenY / Scale.y) + Offset.y) - ((1080.f - screenSize.y) / 32.f);
}

void Camera::clickPan(const InputState& inputState)
{
    sf::Vector2i mousePos = inputState.mousePosition;
    sf::Vector2u windowSize = window.getSize();

    if (inputState.isMiddleMouseButtonPressed)
    {
        if (!mouseButtonPanning)
        {
            mouseButtonPanning = true;
            panStartDrag.x = mousePos.x;
            panStartDrag.y = mousePos.y;
        }
        else
        {
            Offset.x -= (mousePos.x - panStartDrag.x) / Scale.x;
            Offset.y -= (mousePos.y - panStartDrag.y) / Scale.y;

            panStartDrag.x = mousePos.x;
            panStartDrag.y = mousePos.y;
        }
    }
    else
    {
        mouseButtonPanning = false;
    }
}

void Camera::scrollPan(float deltaTime, const InputState& inputState)
{
    const int edgeThreshold = 150;
    sf::Vector2i mousePos = inputState.mousePosition;
    sf::Vector2u windowSize = window.getSize();

    float panSpeedX = 0.0f;
    float panSpeedY = 0.0f;
    int edgeX = static_cast<int>(windowSize.x) - edgeThreshold;
    int edgeY = static_cast<int>(windowSize.y) - edgeThreshold;
    float fEdgeThreshold = static_cast<float>(edgeThreshold);

    if (mousePos.x <= edgeThreshold)
        panSpeedX = (edgeThreshold - mousePos.x) / (fEdgeThreshold * Scale.x);
    else if (mousePos.x >= edgeX)
        panSpeedX = -(mousePos.x - (edgeX)) / (fEdgeThreshold * Scale.x);

    if (mousePos.y <= edgeThreshold)
        panSpeedY = (edgeThreshold - mousePos.y) / (fEdgeThreshold * Scale.y);
    else if (mousePos.y >= edgeY)
        panSpeedY = -(mousePos.y - (edgeY)) / (fEdgeThreshold * Scale.y);

    if (panSpeedX != 0.0f || panSpeedY != 0.0f)
    {
        Offset.x -= panSpeedX * 500 * deltaTime;
        Offset.y -= panSpeedY * 500 * deltaTime;
    }
}

void Camera::Draw(std::vector<sf::Sprite> sprites, const InputState& inputState)
{
    window.clear(sf::Color::Black);
    int centerOffsetX = window.getSize().x / 2;

    for (sf::Sprite s : sprites)
    {
        WorldToScreen(s.getPosition().x + centerOffsetX, s.getPosition().y, screenX, screenY);
        s.setPosition(static_cast<float>(screenX), static_cast<float>(screenY));
        s.setScale(static_cast<float>(Scale.x), static_cast<float>(Scale.y));

        window.draw(s);
    }

    ScreenToWorld(inputState.mousePosition.x - (window.getSize().x / 2) - 50, inputState.mousePosition.y - 100, worldX,
                  worldY);

    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/Diamond Gothic.ttf"))
        std::cerr << "Failed to load font!" << std::endl;

    sf::Text text1;
    text1.setFont(font);

    text1.setString("Mouse Grid (X: " + std::to_string(inputState.selectedCell.x) +
                    ", Y: " + std::to_string(inputState.selectedCell.y) + ")");
    text1.setCharacterSize(24);
    text1.setFillColor(sf::Color::White);
    text1.setPosition(10, 10);

    window.draw(text1);

    window.display();
}