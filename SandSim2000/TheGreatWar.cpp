#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MapEditor.h"
#include <string>

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
    if (!font.loadFromFile("C:\\Users\\User\\Desktop\\The_Great_War\\Resouces\\Fonts\\WorldAtWar.ttf")) std::cerr << "Failed to load font!" << std::endl; 
    sf::Text title("The Great War", font);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setPosition((window.getSize().x - title.getLocalBounds().width) / 2, 50);
    window.draw(title);

    sf::Texture backgroundImgTexture;
    if (!backgroundImgTexture.loadFromFile("C:\\Users\\User\\Desktop\\The_Great_War\\Resouces\\Images\\Utilities\\OpeningImage.jpg")) {
        std::cerr << "Failed to load Opening Image texture!" << std::endl;
    }

    sf::Sprite backgroundImgSprite(backgroundImgTexture);
    backgroundImgSprite.setOrigin(backgroundImgSprite.getLocalBounds().width / 2, backgroundImgSprite.getLocalBounds().height / 2);
    backgroundImgSprite.setPosition(window.getSize().x / static_cast<float>(2), window.getSize().y / static_cast<float>(2));
    window.draw(backgroundImgSprite);

    sf::RectangleShape play(sf::Vector2f(350, 150));
    sf::RectangleShape mapEditor(sf::Vector2f(350, 150));

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("C:\\Users\\User\\Desktop\\The_Great_War\\Resouces\\Images\\Utilities\\MenuButtonBorder.png")) {
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
    if (!cursorImage.loadFromFile("C:\\Users\\User\\Desktop\\The_Great_War\\Resouces\\Images\\Utilities\\cursorIcon.png"))
    {
        throw std::runtime_error("Failed to load cursor image");
    }
    sf::Cursor cursor;
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
    window.setMouseCursor(cursor);
}

/*
int main() 
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "The Great War");
    window.setFramerateLimit(60);
    sf::RectangleShape redRectangle(sf::Vector2f(100, 50));
    redRectangle.setFillColor(sf::Color::Transparent); 
    redRectangle.setOutlineColor(sf::Color::Red);
    redRectangle.setOutlineThickness(2);
    //Mouse to screen troubleshooting text
    sf::Font font;
    if (!font.loadFromFile("C:\\WINDOWS\\FONTS\\DIAMOND GOTHIC.ttf")) 
    {
        std::cerr << "Error loading font file." << std::endl;
        return -1;
    }
    sf::Text cartesianGridText("", font, 20);
    sf::Text mousePositionText("", font, 20);
    sf::Text isoGridText("", font, 20);
    cartesianGridText.setPosition(10, 510);
    mousePositionText.setPosition(10, 540);
    isoGridText.setPosition(10, 570);

    //Drag select
    sf::RectangleShape selectionBox;
    selectionBox.setFillColor(sf::Color(100, 100, 255, 50));
    selectionBox.setOutlineColor(sf::Color::White);
    selectionBox.setOutlineThickness(2.0f);
    sf::Vector2f dragSelectStartPos;
    sf::Vector2f dragSelectStopPos;
    sf::Vector2f tempSelectionPos;
    bool isDragSelecting = false;

    sf::Texture terrainTexture;
    if (!terrainTexture.loadFromFile("C:\\Users\\User\\Desktop\\The_Great_War\\Resouces\\Images\\Terrain\\ground.png")) return -1;
    std::vector<std::vector<sf::Sprite>> sprites(4, std::vector<sf::Sprite>(4));

    sf::Texture selectedTileTexture;
    if (!selectedTileTexture.loadFromFile("C:\\Users\\User\\Desktop\\The_Great_War\\Resouces\\Images\\Terrain\\selected.png")) return -1;
    sf::Sprite selectedTileSprite;
    selectedTileSprite.setTexture(selectedTileTexture);

    const int gridDimension = 4;
    for (int i = 0; i < gridDimension; i++)
        for (int j = 0; j < gridDimension; j++)
            sprites[i][j].setTexture(terrainTexture);

    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            float x = j;
            float y = i;
            sf::Vector2f cartesianPosition(x, y);
            sf::Vector2f isometricPosition = cartesianToIsometricTransform(cartesianPosition);
            isometricPosition.x += 350;
            sprites[i][j].setPosition(isometricPosition.x, isometricPosition.y);
            isometricPosition.x -= 400;
            isometricPosition.y += 50.0f;
            sf::Vector2f cartesianPositionOutput = isometricToCartesianTransform(isometricPosition);
        }
    }

    while (window.isOpen()) 
    {
        
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            //if (event.type == sf::Event::Closed) window.close();
            //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
            {
                isDragSelecting = true;
                dragSelectStartPos = sf::Vector2f(sf::Mouse::getPosition(window));
                tempSelectionPos = dragSelectStartPos;

            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragSelecting = false;
                dragSelectStopPos = sf::Vector2f(sf::Mouse::getPosition(window));
            }

            if(isDragSelecting) tempSelectionPos = sf::Vector2f(sf::Mouse::getPosition(window));
           
            sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
            mouseCoords.x -= 250;
            mouseCoords.x /= 100;
            mouseCoords.y /= 50;
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            int snappedX = (((mousePosition.x + 50) / 100) * 100) - 50;
            int snappedY = (mousePosition.y / 50) * 50;
                
            sf::Vector2f mouseCoordsFloat(static_cast<float>(mouseCoords.x), static_cast<float>(mouseCoords.y));
            sf::Vector2f mousePositionFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            sf::Vector2f mouseIsometric = cartesianToIsometricTransform(mouseCoordsFloat);
            sf::Vector2f mouseCellPosition = mouseCellCalc(mousePositionFloat);
            sf::Vector2f mouseCart = isometricToCartesianTransform(mouseIsometric);
            int selectedCorner = isInsideTriangle(mouseCellPosition);
            sf::Vector2f selectedCell = cellSelector(mouseCoordsFloat, selectedCorner);

            cartesianGridText.setString("Cartesian Cell X: " + std::to_string(mouseCoords.x) +
                ", Y: " + std::to_string(mouseCoords.y));
            mousePositionText.setString("Mouse X: " + std::to_string(mouseCellPosition.x ) +
                ", Y: " + std::to_string(mouseCellPosition.y));
                
            isoGridText.setString("Isometric Cell X: " + std::to_string(selectedCell.x) +
                ", Y: " + std::to_string(selectedCell.y));
            redRectangle.setPosition(sf::Vector2f(snappedX, snappedY));

            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f screenPosition = isometricToScreenPosition(selectedCell);
                selectedTileSprite.setPosition(screenPosition.x + 350, screenPosition.y);
            }
            
        }
        window.clear(sf::Color::Black);
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                window.draw(sprites[y][x]);
            }
        }
        
        sf::Vector2f selectionSize = tempSelectionPos - dragSelectStartPos;
        selectionBox.setSize(selectionSize);
        selectionBox.setPosition(dragSelectStartPos);
        
        window.draw(selectionBox);

        window.draw(cartesianGridText);
        window.draw(mousePositionText);
        window.draw(isoGridText);
        window.draw(selectedTileSprite);
        

        //window.display();
    }
    //MapEditor mapEditor(100.0f);
    //mapEditor.run();
    return 0;
}
*/

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
            std::cout << "Play" << std::endl;
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

