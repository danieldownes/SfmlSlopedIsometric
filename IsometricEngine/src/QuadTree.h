#pragma once

#include <array>
#include <iostream>
#include <vector>

#include "GlobalConstants.h"
#include "SFML/Graphics/Rect.hpp"

struct QuadTree
{
	virtual void f(){};

	unsigned int depth;
	GlobalConstants constants;

	sf::IntRect quadRect;
	std::array<QuadTree*, 4> children;

	int offsetX[4] = {0, 1, 0, 1};
	int offsetY[4] = {0, 0, 1, 1};

	virtual void insert(Agent* agent, int multiplier)
	{
		for (int i = 0; i < 4; i++)
		{
			if (children[i] == nullptr)
				continue;

			auto v = sf::Vector2i(static_cast<int>(agent->getPosX()), static_cast<int>(agent->getPosX()));
			if (children[i]->quadRect.contains(v * multiplier))
			{
				children[i]->insert(agent, multiplier);
				return;
			}
		}
	}

	QuadTree* getNode(QuadTree* node, int targetX, int targetY, int targetLevel)
	{
		if (node == nullptr)
			return nullptr;

		if (node->quadRect.getPosition().x == targetX && node->quadRect.getPosition().y == targetY &&
			node->depth == targetLevel)
			return node;

		for (int i = 0; i < 4; ++i)
		{
			int childX = node->quadRect.getPosition().x * 2 + offsetX[i];
			int childY = node->quadRect.getPosition().y * 2 + offsetY[i];
			QuadTree* result = getNode(node->children[i], targetX, targetY, targetLevel);
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

	virtual BattlefieldCell* getCell(QuadTree* node, int targetX, int targetY, int targetLevel)
	{
		if (node == nullptr)
			return nullptr;

		for (int i = 0; i < 4; ++i)
		{
			int childX = node->quadRect.getPosition().x * 2 + offsetX[i];
			int childY = node->quadRect.getPosition().y * 2 + offsetY[i];
			BattlefieldCell* result = node->children[i]->getCell(node->children[i], targetX, targetY, targetLevel);
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

	bool CircleInRect(float circleX, float circleY, float radius, QuadTree* node)
	{
		int pX;
		int pY;

		if (circleX < node->quadRect.getPosition().x)
			pX = node->quadRect.getPosition().x;
		else if (circleX < node->quadRect.getPosition().x)
			pX = node->quadRect.getPosition().x + node->quadRect.getSize().x;
		if (circleY < node->quadRect.getPosition().y)
			pY = node->quadRect.getPosition().y;
		else if (circleY < node->quadRect.getPosition().y)
			pY = node->quadRect.getPosition().y + node->quadRect.getSize().y;

		float testX = static_cast<float>(pX);
		float testY = static_cast<float>(pY);

		float distanceX = circleX - testX;
		float distanceY = circleY - testY;

		float distance = std::sqrt((distanceX * distanceX) + (distanceY * distanceY));
		return (distance <= radius);
	}

	virtual void getAgentsInRadius(QuadTree* node, float targetX, float targetY, float radius, int targetLevel,
								   std::vector<Agent*>* agents)
	{
		if (node == nullptr)
			return;

		for (int i = 0; i < 4; ++i)
		{
			bool ishit = CircleInRect(targetX, targetY, radius, node->children[i]);
			if (ishit)
				node->children[i]->getAgentsInRadius(node->children[i], targetX, targetY, radius, targetLevel, agents);
		}
	}

	QuadTree(const sf::IntRect& rect, const unsigned int& depth)
		: depth(depth), quadRect(rect), children{nullptr, nullptr, nullptr, nullptr}
	{
	}

	~QuadTree()
	{
		for (QuadTree* child : children) delete[] child;
	}
};

struct QuadTreeLeaf : public QuadTree
{
	std::vector<BattlefieldCell>::iterator iter;

	void insert(Agent* agent, int multiplier) override
	{
		iter->Objects.push_back(agent);
	}

	BattlefieldCell* getCell(QuadTree* node, int targetX, int targetY, int targetLevel) override
	{
		if (node->quadRect.getPosition().x == targetX && node->quadRect.getPosition().y == targetY &&
			node->depth == targetLevel)
			return iter._Unwrapped();

		return nullptr;
	}

	void getAgentsInRadius(QuadTree* node, float targetX, float targetY, float radius, int targetLevel,
						   std::vector<Agent*>* agents)
	{
		if (node == nullptr)
			return;

		for (int i = 0; i < iter->Objects.size(); i++)
		{
			float differenceX = abs(targetX - iter->Objects[i]->getPosX() * constants.cellSize);
			float differenceY = abs(targetY - iter->Objects[i]->getPosY() * constants.cellSize);
			float distance = std::sqrt((differenceX * differenceX) + (differenceY * differenceY));

			if (distance <= radius)
				agents->push_back(iter->Objects[i]);
		}
	}

	QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<BattlefieldCell>::iterator& _iter)
		: QuadTree(rect, depth), iter(_iter)
	{
	}

   private:
	sf::IntRect calculateChildRect(int index) const
	{
		int halfWidth = quadRect.width / 2;
		int halfHeight = quadRect.height / 2;
		int childLeft = quadRect.left + (index % 2) * halfWidth;
		int childTop = quadRect.top + (index / 2) * halfHeight;
		return sf::IntRect(childLeft, childTop, halfWidth, halfHeight);
	}
};