#pragma once

#include <vector>

#include "BattlefieldCell.h"

struct GhostGrid
{
	std::vector<std::vector<BattlefieldCell*>> ghostGridBuffer;
	int left = 0; int right = 0; int top = 0; int bottom = 0;

	BattlefieldCell* getCell(int BattlefieldCellX, int BattlefieldCellY)
	{
		for(std::vector<BattlefieldCell*> line : ghostGridBuffer)
		{
			for (BattlefieldCell* current : line)
			{
				if (current != nullptr)
				{
					if (current->x == BattlefieldCellX && current->y == BattlefieldCellY)
						return current;
				}
			}
		}
		return nullptr;
	}

	void cleanHeuristics()
	{
		for (std::vector<BattlefieldCell*> line : ghostGridBuffer)
		{
			for (BattlefieldCell* current : line)
			{
				if(current != nullptr)
				{
					current->hScore = 0;
					current->gScore = 0;
					current->fScore = 0;
					current->pathParent = nullptr;
					current->inClosedList = false;
				}
			}
		}

		for (int i = 0; i < ghostGridBuffer.size(); i++)
			ghostGridBuffer[i].clear();
		ghostGridBuffer.clear();
	}
};