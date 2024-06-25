#pragma once

#include <cmath>
#include <functional>
#include <queue>
#include <set>
#include <typeinfo>
#include <unordered_set>

#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "PathfinderAgent.h"
#include "PathfinderUtilities.h"
#include "Scene.h"

class MovementManager
{
   public:
	// pass a PathfinderAgent by reference and the goal battlefieldCell
	// This function then runs the pathfinding and sets the agents path
	void SetUnitPath(PathfinderAgent* agent, BattlefieldCell* goal, GameStateManager* gameStateManager,
					 InputState& state, Scene& scene, Camera* camera);

	std::vector<BattlefieldCell*>* getPath()
	{
		return &pathList;
	}

   private:
	std::priority_queue<BattlefieldCell*, std::vector<BattlefieldCell*>, LowestScoreSorter> openList;
	std::vector<BattlefieldCell*> closedList;
	std::vector<BattlefieldCell*> pathListChildrenGrid;
	std::vector<BattlefieldCell*> pathList;

	GhostGrid* ghostGrid;

	void cleanHeuristics();
	void propagateWaveFrontHeuristics(BattlefieldCell* goal, GameState* state);
	int AStar(BattlefieldCell* start, BattlefieldCell* goal);

	void ExploreNeighbours(BattlefieldCell* current, BattlefieldCell* goal);
	void ReconstructPath(BattlefieldCell* goal);

	// The current target cell for pathfinding
	BattlefieldCell* targetCell = nullptr;
};