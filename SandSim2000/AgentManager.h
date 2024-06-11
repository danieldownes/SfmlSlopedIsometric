#pragma once
#include <cmath>
#include <set>
#include <typeinfo>
#include <unordered_set>
#include <queue>
#include <functional>

#include "GameStateManager.h"
#include "InputState.h"
#include "Scenery.h"
#include "Tree.h"
#include "Camera.h"
#include "Scene.h"
#include "PathfinderAgent.h"

struct LowestScoreSorter {
	bool operator()(BattlefieldCell* a, BattlefieldCell* b) {
		if (a->fScore != b->fScore) {
			return a->fScore < b->fScore;
		}
		return a->hScore < b->hScore;
	}
};

class AgentManager
{
public:

	void onUpdate(
		InputState& state,
		std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
		GameStateManager& gameStateManager,
		Camera& camera,
		Scene& scene);
	void placeScenery(sf::Vector2i isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery scenObject, GameStateManager& gameStateManager);
	void placeAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Agent agent, GameStateManager& gameStateManager);
	void placePathfinderAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gamesScene, PathfinderAgent agent, GameStateManager& gameStateManager);

	void updateAgentPosition();
	void setX(int xPosition);
	void setY(int yPosition);

	void UpdatePathfindingGoals(GameStateManager* gameStateManager, InputState& state, Scene& scene);

	PathfinderAgent* pathfinderAgent = nullptr;

	// DEBUG method only
	void printGhostGrid();
	void printPathGrid(GameState* state);

	std::vector<BattlefieldCell*>* getPath() { return &pathList; }
private:
	bool leftClick = false;
	bool rightClick = false;

	std::priority_queue<BattlefieldCell*, std::vector<BattlefieldCell*>, LowestScoreSorter> openList;
	std::vector<BattlefieldCell*> closedList;
	std::vector<BattlefieldCell*> pathListChildrenGrid;
	std::vector<BattlefieldCell*> pathList;

	std::vector<std::vector<BattlefieldCell*>> GhostGrid;

	// -----Pathfinding---- //
	// call these function in this order
	void generateGhostGrid(GameState* state, BattlefieldCell* start, BattlefieldCell* goal, int level);
	void cleanHeuristics();
	void propagateWaveFrontHeuristics(BattlefieldCell* target, GameState* state);
	int AStar(BattlefieldCell* start, BattlefieldCell* goal);

	void ExploreNeighbours(BattlefieldCell* current, BattlefieldCell* goal);
	void ReconstructPath(BattlefieldCell* goal);

	BattlefieldCell* getCellFromGhost(int BattlefieldCellX, int BattlefieldCellY);

	BattlefieldCell* targetCell = nullptr;


	// Ghost Grid Rect
	int left; int right; int top; int bottom;
};
