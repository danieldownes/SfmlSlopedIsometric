#pragma once
#include "BattlefieldCell.h"

static int min(int value_1, int value_2)
{
	if (value_1 < value_2)
		return value_1;
	return value_2;
}
static int max(int value_1, int value_2)
{
	if (value_1 > value_2)
		return value_1;
	return value_2;
}

static bool checkInList(BattlefieldCell* cell, std::vector<BattlefieldCell*>* list)
{
	for (int i = 0; i < list->size(); i++)
	{
		if (cell == list->at(i))
			return true;
	}
	return false;
}

struct LowestScoreSorter
{
	bool operator()(BattlefieldCell* a, BattlefieldCell* b)
	{
		if (a->fScore != b->fScore)
		{
			return a->fScore < b->fScore;
		}
		return a->hScore < b->hScore;
	}
};

struct NeibourListHash
{
	size_t operator()(const BattlefieldCell* node) const
	{
		return std::hash<const BattlefieldCell*>{}(node);
	}
};
