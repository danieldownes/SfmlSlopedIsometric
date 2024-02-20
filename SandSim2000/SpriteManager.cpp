#include "SpriteManager.h"
#include <iostream>


SpriteManager::SpriteManager(const char* filePath)
{
	spriteSheetList.push_back(std::make_pair("RedBaron", SpriteSheet(filePath, 3, 3)));
}

//gets the sprite from the spritesheet
sf::Sprite* SpriteManager::GetSprite(std::string spriteSheetID, int spriteIndex)
{
	for (auto it = spriteSheetList.begin(); it != spriteSheetList.end(); ++it) 
	{
		if (it->first == spriteSheetID) 
		{
			return it->second.getSprite(spriteIndex);
		}
	}
	std::cerr << "[INVALID SPRITE NOT IN LIST]" << std::endl;
}

//gets the spritesheet
SpriteSheet& SpriteManager::GetSpriteSheet(std::string spriteSheetID)
{
	for (auto it = spriteSheetList.begin(); it != spriteSheetList.end(); ++it)
	{
		if (it->first == spriteSheetID)
		{
			return it->second;
		}
	}
	std::cerr << "[INVALID SPRITE NOT IN LIST]" << std::endl;
}

