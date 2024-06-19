#pragma once

#include <vector>

#include "BattlefieldCell.h"

struct GhostGrid
{
	std::vector<std::vector<BattlefieldCell*>> ghostGridBuffer;
	int left = 0; int right = 0; int top = 0; int bottom = 0;

	BattlefieldCell* getCell(int BattlefieldCellX, int BattlefieldCellY)
	{
		if (BattlefieldCellX >= left && BattlefieldCellX < right && BattlefieldCellY >= top && BattlefieldCellY < bottom)
			return ghostGridBuffer[BattlefieldCellX - left][BattlefieldCellY - top];
		return nullptr;
	}

	void calculateRect()
	{
		left = ghostGridBuffer[0][0]->x;	
		right = ghostGridBuffer[ghostGridBuffer.size() - 1][0]->x;
		top = ghostGridBuffer[0][0]->y;		
		bottom = ghostGridBuffer[0][ghostGridBuffer[0].size() - 1]->y;
	}

	void cleanHeuristics()
	{
		for (int i = top; i < bottom; i++)
		{
			for (int j = left; j < right; j++)
			{
				BattlefieldCell* current = getCell(j, i);

				current->hScore = 0;
				current->gScore = 0;
				current->fScore = 0;
				current->pathParent = nullptr;
				current->inClosedList = false;
			}
		}

		for (int i = 0; i < ghostGridBuffer.size(); i++)
			ghostGridBuffer[i].clear();
		ghostGridBuffer.clear();
	}
};