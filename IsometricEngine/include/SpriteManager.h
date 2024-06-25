#pragma once

#include "SFML/Graphics.hpp"

#include <vector>
#include <list>

#include "SpriteSheet.h"

class SpriteManager
{
public:
    SpriteManager();

    sf::Sprite* GetSprite(std::string spriteSheetID, int spriteIndex);
    SpriteSheet& GetSpriteSheet(std::string spriteSheetID);

    static SpriteManager* GetInstance();
    void operator=(const SpriteManager&) = delete;


private:
    static SpriteManager* _instance;

    std::list<std::pair<std::string, SpriteSheet>> spriteSheetList;
};