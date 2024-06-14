#include "MovementManager.h"

void MovementManager::SetUnitPath(PathfinderAgent* agent, BattlefieldCell* goal, GameStateManager* gameStateManager, InputState& state, Scene& scene)
{
    if (goal != nullptr)
    {
        targetCell = goal;

        BattlefieldCell* startCell = gameStateManager->getState().quadTree->getCell(gameStateManager->state.quadTree, agent->getPosX() * 100, agent->getPosY() * 100, 4);

        generateGhostGrid(&gameStateManager->getState(), startCell, targetCell, 4);
        propagateWaveFrontHeuristics(targetCell, &gameStateManager->state);

        if (AStar(startCell, targetCell) == 1)
        {
            std::vector<BattlefieldCell*>* path = getPath();

            agent->setPath(path);
        }
        cleanHeuristics();
    }
}

#define GHOST_PADDING 2
void MovementManager::generateGhostGrid(GameState* state, BattlefieldCell* start, BattlefieldCell* goal, int level)
{
    int gridSize = std::sqrt(std::pow(4, level));
    int cellWidth = (state->quadTree->quadRect.getSize().x / std::pow(2, level));
    int cellHeight = (state->quadTree->quadRect.getSize().y / std::pow(2, level));

    left = max(min(start->x - GHOST_PADDING, goal->x - GHOST_PADDING), 0);
    right = min(max(start->x + GHOST_PADDING + 1, goal->x + GHOST_PADDING + 1), gridSize);
    top = max(min(start->y - GHOST_PADDING, goal->y - GHOST_PADDING), 0);
    bottom = min(max(start->y + GHOST_PADDING + 1, goal->y + GHOST_PADDING + 1), gridSize);

    for (int i = top; i < bottom; ++i) {
        std::vector<BattlefieldCell*> line;
        for (int j = left; j < right; ++j)
        {
            line.push_back(state->quadTree->getCell(state->quadTree, j * cellWidth, i * cellHeight, level));
        }
        GhostGrid.push_back(line);
    }
    std::cout << "X:" << GhostGrid[0].size() << std::endl;
    std::cout << "Y:" << GhostGrid.size() << std::endl;

    std::cout << GhostGrid[0][0]->x << ":" << GhostGrid[0][0]->y << std::endl;
    std::cout << GhostGrid[GhostGrid.size() - 1][GhostGrid[0].size() - 1]->x << ":" << GhostGrid[GhostGrid.size() - 1][GhostGrid[0].size() - 1]->y << std::endl;
}


void MovementManager::propagateWaveFrontHeuristics(BattlefieldCell* goal, GameState* state)
{
    std::vector<BattlefieldCell*> waveFrontNodes;
    std::unordered_set<BattlefieldCell*, NeibourListHash> neighbourNodes;

    goal->hScore = 10;
    waveFrontNodes.push_back(goal);

    while (!waveFrontNodes.empty())
    {
        for (BattlefieldCell* node : waveFrontNodes)
        {
            int x = node->x; int y = node->y;
            // Z is the depth of the node in the quadtree, 
            // however we only have the one layer and dont store its depth
            int z = constants.quadTreeDepth;


            BattlefieldCell* northNeighbour = getCellFromGhost(x, y - 1);
            BattlefieldCell* eastNeighbour = getCellFromGhost(x + 1, y);
            BattlefieldCell* southNeighbour = getCellFromGhost(x, y + 1);
            BattlefieldCell* westNeighbour = getCellFromGhost(x - 1, y);

            if (northNeighbour != nullptr && northNeighbour->hScore == 0 && !northNeighbour->impassableTerrain) {
                northNeighbour->hScore = node->hScore + 10;
                neighbourNodes.insert(northNeighbour);
            }

            if (eastNeighbour != nullptr && eastNeighbour->hScore == 0 && !eastNeighbour->impassableTerrain) {
                eastNeighbour->hScore = node->hScore + 10;
                neighbourNodes.insert(eastNeighbour);
            }

            if (southNeighbour != nullptr && southNeighbour->hScore == 0 && !southNeighbour->impassableTerrain) {
                southNeighbour->hScore = node->hScore + 10;
                neighbourNodes.insert(southNeighbour);
            }

            if (westNeighbour != nullptr && westNeighbour->hScore == 0 && !westNeighbour->impassableTerrain) {
                westNeighbour->hScore = node->hScore + 10;
                neighbourNodes.insert(westNeighbour);
            }
        }

        waveFrontNodes.clear();

        for (BattlefieldCell* neighbourNode : neighbourNodes) {
            waveFrontNodes.push_back(neighbourNode);
        }

        neighbourNodes.clear();
    }
}


int MovementManager::AStar(BattlefieldCell* start, BattlefieldCell* goal)
{
    if (start == nullptr || goal == nullptr)
    {
        std::cerr << "[ERROR][PATHFINDING]--> Start or goal is nullptr" << std::endl;
        return 0;
    }

    openList.push(start);

    while (!openList.empty())
    {
        BattlefieldCell* current = openList.top();
        openList.pop();

        current->inClosedList = true;
        closedList.push_back(current);

        if (current == goal)
        {
            std::cout << "path found" << std::endl;
            ReconstructPath(goal);
            return 1;
        }
        ExploreNeighbours(current, goal);
    }
    std::cout << "no path found" << std::endl;
    return -1;
}

void MovementManager::ExploreNeighbours(BattlefieldCell* current, BattlefieldCell* goal)
{
    int dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int dy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    BattlefieldCell* bestNeighbour = nullptr;
    int bestFScore = std::numeric_limits<int>::max();

    for (int i = 0; i < 8; ++i)
    {
        int nx = current->x + dx[i];
        int ny = current->y + dy[i];
        int levelInt = constants.quadTreeDepth;

        BattlefieldCell* neighbour = getCellFromGhost(nx, ny);
        if (neighbour != nullptr && !neighbour->impassableTerrain && !neighbour->inClosedList)
        {
            int gScore = current->gScore + ((i % 2 == 0) ? 10 : 14);
            int fScore = neighbour->hScore + gScore;
            neighbour->gScore = gScore;
            neighbour->fScore = fScore;

            if (neighbour->pathParent == nullptr || current->fScore < neighbour->pathParent->fScore)
            {
                neighbour->pathParent = current;
            }

            if (fScore < bestFScore) {
                bestNeighbour = neighbour;
                bestFScore = fScore;
            }
        }
    }
    if (bestNeighbour != nullptr) {
        openList.push(bestNeighbour);
    }
}

BattlefieldCell* MovementManager::getCellFromGhost(int BattlefieldCellX, int BattlefieldCellY)
{
    if (BattlefieldCellX >= left && BattlefieldCellX < right && BattlefieldCellY >= top && BattlefieldCellY < bottom)
        return GhostGrid[BattlefieldCellY - top][BattlefieldCellX - left];
    return nullptr;
}

void MovementManager::ReconstructPath(BattlefieldCell* goal)
{
    BattlefieldCell* current = goal;
    while (current != nullptr)
    {
        pathList.push_back(current);
        current = current->pathParent;
    }

    std::reverse(pathList.begin(), pathList.end());
}


void MovementManager::cleanHeuristics()
{
    targetCell = nullptr;

    pathList.clear();
    closedList.clear();

    while (!openList.empty())
        openList.pop();

    for (int i = top; i < bottom; i++)
    {
        for (int j = left; j < right; j++)
        {
            BattlefieldCell* current = getCellFromGhost(j, i);

            current->hScore = 0;
            current->gScore = 0;
            current->fScore = 0;
            current->pathParent = nullptr;
            current->inClosedList = false;
        }
    }

    for (int i = 0; i < GhostGrid.size(); i++)
        GhostGrid[i].clear();
    GhostGrid.clear();
}