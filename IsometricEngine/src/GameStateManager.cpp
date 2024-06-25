#include "GameStateManager.h"

#define CELLSIZE 100

GameStateManager::GameStateManager(unsigned int numCells)
{
	initializeBattlefieldVector(numCells);
}

void GameStateManager::initialiseQuadTree(unsigned int battlefieldSize, unsigned int& index)
{
	battlefieldMap.initMap(static_cast<unsigned int>(battlefieldSize / 100));
	state.quadTree = new QuadTree(sf::IntRect(0, 0, battlefieldSize, battlefieldSize), 0);
	generateQuadTree((QuadTree*)state.quadTree, index);
}

void GameStateManager::generateQuadTree(QuadTree* root, unsigned int& index)
{
	auto size = root->quadRect.getSize().x / 2;
	if (size > CELLSIZE)
	{
		std::array<QuadTree*, 4> children;

		for (int i = 0; i < 4; i++)
		{
			children[i] =
				new QuadTree(sf::IntRect(static_cast<int>(root->quadRect.getPosition().x + size * (i % 2)),
										 static_cast<int>(root->quadRect.getPosition().y + size * ((int)(i > 1))),
										 static_cast<int>(size), static_cast<int>(size)),
							 root->depth + 1);

			generateQuadTree((QuadTree*)children[i], index);
		}
		root->children = children;
	}
	else
	{
		std::array<QuadTree*, 4> children;

		for (int i = 0; i < 4; i++)
		{
			auto x = root->quadRect.getPosition().x + size * (i % 2);
			auto y = root->quadRect.getPosition().y + size * ((int)(i > 1));

			state.BattlefieldVector[index] = generateCell(x / CELLSIZE, y / CELLSIZE);

			std::vector<BattlefieldCell>::iterator iter = state.BattlefieldVector.begin() + (index++);

			children[i] = new QuadTreeLeaf(sf::IntRect(x, y, size, size), root->depth + 1, iter);
		}
		root->children = children;
	}
}

BattlefieldCell GameStateManager::generateCell(int x, int y)
{
	BattlefieldCell newCell;
	newCell.x = x;
	newCell.y = y;
	newCell.vertices = battlefieldMap.getVertices(x, y);
	newCell.terrainSprite = battlefieldMap.getSpriteAtPosition({x, y});
	newCell.YOffset = battlefieldMap.getHeightAtPosition({x, y}) * CELLSIZE / 4;

	return newCell;
}

BattlefieldCell* GameStateManager::getCell(int x, int y)
{
	for (auto& cell : state.BattlefieldVector)
	{
		if (cell.x == x && cell.y == y)
		{
			return &cell;
		}
	}
	return nullptr;
}

void GameStateManager::initializeBattlefieldVector(unsigned int numCells)
{
	state.BattlefieldVector.clear();
	state.BattlefieldVector.resize(numCells);
	unsigned int index = 0;
	initialiseQuadTree(static_cast<int>(std::floor(std::sqrt(numCells))) * 100, index);
}
