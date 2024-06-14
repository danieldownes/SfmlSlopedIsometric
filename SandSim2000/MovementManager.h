#pragma once

#include <cmath>
#include <set>
#include <typeinfo>
#include <unordered_set>
#include <queue>
#include <functional>

#include "PathfinderUtilities.h"
#include "PathfinderAgent.h"
#include "GameStateManager.h"
#include "Scene.h"


class MovementManager
{
public:
	// pass a PathfinderAgent by reference and the goal battlefieldCell
	// This function then runs the pathfinding and sets the agents path
	void SetUnitPath(PathfinderAgent* agent, BattlefieldCell* goal, GameStateManager* gameStateManager, InputState& state, Scene& scene);

	std::vector<BattlefieldCell*>* getPath() { return &pathList; }
private:
	std::priority_queue<BattlefieldCell*, std::vector<BattlefieldCell*>, LowestScoreSorter> openList;
	std::vector<BattlefieldCell*> closedList;
	std::vector<BattlefieldCell*> pathListChildrenGrid;
	std::vector<BattlefieldCell*> pathList;

	std::vector<std::vector<BattlefieldCell*>> GhostGrid;

	void generateGhostGrid(GameState* state, BattlefieldCell* start, BattlefieldCell* goal, int level);
	void cleanHeuristics();
	void propagateWaveFrontHeuristics(BattlefieldCell* goal, GameState* state);
	int AStar(BattlefieldCell* start, BattlefieldCell* goal);

	void ExploreNeighbours(BattlefieldCell* current, BattlefieldCell* goal);
	void ReconstructPath(BattlefieldCell* goal);

	BattlefieldCell* getCellFromGhost(int BattlefieldCellX, int BattlefieldCellY);

	// The current target cell for pathfinding
	BattlefieldCell* targetCell = nullptr;
	//Ghost Grid Rect
	int left; int right; int top; int bottom;
};