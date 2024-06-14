#include "AnimationManager.h"

sf::Sprite AnimationManager::getAgentSpriteFromDirection(Agent* agent)
{
	if (agent->isDirectionalSprite())
	{
		int index = getIndexFromDirection(agent->getCurrentDirection());
		if (index == -1)
		{
			std::cerr << "invalid directions used for [" << agent->getUnitType() << "]" << std::endl;
			return *SpriteManager::GetInstance()->GetSprite(agent->getSpriteString(), agent->getSpriteIndex());
		}
		return *SpriteManager::GetInstance()->GetSprite(agent->getSpriteString(), index);
	}
	return *SpriteManager::GetInstance()->GetSprite(agent->getSpriteString(), agent->getSpriteIndex());
}

int AnimationManager::getIndexFromDirection(sf::Vector2i direction)
{
	for (int i = 0; i < 8; i++)
	{
		if (direction == directions[i])
			return i;
	}
	return -1;
}