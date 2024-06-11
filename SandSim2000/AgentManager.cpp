#include "AgentManager.h"

/*                        +++++++++++++ Agent Manager +++++++++++++                             */
/* Method: UpdateImpassableTerrainNodes - Sets selected nodes as impassable terrain             */
/* Method: PropagateWaveFrontHeuristics - Sets heuristics for nodes in a wave out from target   */
/* Method: AStar - Performs main loop of AStar on a grid with heuristics preset from WFP        */
/* Method: ExploreNeighbours - Neighbours of current cell passed to it                          */
/* Method: ReconstructPath - Builds list of path nodes based on parent nodes in path            */
/*                        +++++++++++++ Debug Methods +++++++++++++                             */
/* Method: PrintGhostGrid - Prints the ghost grid, has commented out code to print the hScore   */
/*             +++++++++++++     +++++++++++++        +++++++++++++                             */

void AgentManager::onUpdate(
    InputState& state,
    std::set<std::vector<BattlefieldCell>::iterator>* gameScene,
    GameStateManager& gameStateManager,
    Camera& camera,
    Scene& scene)
{

    if (pathfinderAgent != nullptr)
    {
        pathfinderAgent->update();
    }

    if (state.isLeftMouseButtonPressed && leftClick == false)
    {
        targetCell = gameStateManager.getState().quadTree->getCell(gameStateManager.state.quadTree, state.selectedCell.x * 100, state.selectedCell.y * 100, 4);

        UpdatePathfindingGoals(&gameStateManager, state, scene);

        leftClick = true;
    }
    else if (state.isRightMouseButtonPressed && rightClick == false)
    {
        rightClick = true;
    }
    else if (state.isLeftMouseButtonPressed == false)
    {
        leftClick = false;
    }
    else if (state.isRightMouseButtonPressed == false)
    {
        rightClick = false;
    }
}

void AgentManager::UpdatePathfindingGoals(GameStateManager* gameStateManager, InputState& state, Scene& scene)
{
    if (targetCell != nullptr)
    {
        BattlefieldCell* startCell = gameStateManager->getState().quadTree->getCell(gameStateManager->state.quadTree, pathfinderAgent->getPosX() * 100, pathfinderAgent->getPosY() * 100, 4);

        generateGhostGrid(&gameStateManager->getState(), startCell, targetCell, 4);
        propagateWaveFrontHeuristics(targetCell, &gameStateManager->state);


        if (AStar(startCell, targetCell) == 1)
        {
            printPathGrid(&gameStateManager->getState());
            printGhostGrid();

            std::vector<BattlefieldCell*>* path = getPath();

            /*
            for (int i = 0; i < path->size(); i++)
            {
                sf::Vector2i cellPosition = sf::Vector2i(path->at(i)->x, path->at(i)->y);
                Tree tree(10, 10);

                placeScenery(cellPosition, &scene.gameScene, tree, *gameStateManager);
            }
            */
            pathfinderAgent->setPath(path);
        }
        cleanHeuristics();
    }
}


void AgentManager::placeScenery(sf::Vector2i isometricCell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Scenery sceneObject, GameStateManager& gameStateManager)
{
    if (sceneObject.getUnitType() == "Tree")
    {
        Tree* tree = new Tree(isometricCell.x, isometricCell.y);

        gameStateManager.getState().Units.push_back(tree);
        gameStateManager.getState().quadTree->insert(tree, 100);
    }
}

void AgentManager::placeAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gameScene, Agent agent, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(cell);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);


    Agent* newAgent = new Agent(agent);

    gameStateManager.getState().Units.push_back(newAgent);
    gameStateManager.getState().quadTree->insert(newAgent, 100);
}

void AgentManager::placePathfinderAgent(sf::Vector2i cell, std::set<std::vector<BattlefieldCell>::iterator>* gamesScene, PathfinderAgent agent, GameStateManager& gameStateManager)
{
    GridGenerator gridgen = GridGenerator();
    sf::Vector2f EuclideanPos = gridgen.isometricToCartesianTransform(cell);

    sf::Vector2i intEuclidianPos = sf::Vector2i(static_cast<int>(EuclideanPos.x) - 11, static_cast<int>(EuclideanPos.y) + 9);

    PathfinderAgent* newAgent = new PathfinderAgent(agent);
    newAgent->setStartingCell(gameStateManager.getState().quadTree->getCell(gameStateManager.getState().quadTree, intEuclidianPos.x * 100, intEuclidianPos.y * 100, 4));

    gameStateManager.getState().Units.push_back(newAgent);
    gameStateManager.getState().quadTree->insert(newAgent, 100);
    pathfinderAgent = newAgent;
}

void AgentManager::cleanHeuristics()
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

void AgentManager::propagateWaveFrontHeuristics(BattlefieldCell* target, GameState* state)
{
    struct NeibourListHash {
        size_t operator() (const BattlefieldCell* node) const {
            return std::hash<const BattlefieldCell*>{} (node);
        }
    };

    std::vector<BattlefieldCell*> waveFrontNodes;
    std::unordered_set<BattlefieldCell*, NeibourListHash> neighbourNodes;

    target->hScore = 10;
    waveFrontNodes.push_back(target);

    while (!waveFrontNodes.empty())
    {
        for (BattlefieldCell* node : waveFrontNodes)
        {
            int x = node->x; int y = node->y;
            // Z is the depth of the node in the quadtree, 
            // however we only have the one layer and dont store its depth
            int z = 4;


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

int AgentManager::AStar(BattlefieldCell* start, BattlefieldCell* goal)
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

void AgentManager::ExploreNeighbours(BattlefieldCell* current, BattlefieldCell* goal)
{
    int dx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int dy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    BattlefieldCell* bestNeighbour = nullptr;
    int bestFScore = std::numeric_limits<int>::max();

    for (int i = 0; i < 8; ++i)
    {
        int nx = current->x + dx[i];
        int ny = current->y + dy[i];
        int levelInt = 4;

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

void AgentManager::ReconstructPath(BattlefieldCell* goal)
{
    BattlefieldCell* current = goal;
    while (current != nullptr)
    {
        pathList.push_back(current);
        current = current->pathParent;
    }

    std::reverse(pathList.begin(), pathList.end());
}


int min(int value_1, int value_2)
{
    if (value_1 < value_2)
        return value_1;
    return value_2;
}
int max(int value_1, int value_2)
{
    if (value_1 > value_2)
        return value_1;
    return value_2;
}

#define PADDING 2
void AgentManager::generateGhostGrid(GameState* state, BattlefieldCell* start, BattlefieldCell* goal, int level)
{
    int gridSize = std::sqrt(std::pow(4, level));
    int cellWidth = (state->quadTree->quadRect.getSize().x / std::pow(2, level));
    int cellHeight = (state->quadTree->quadRect.getSize().y / std::pow(2, level));

    left = max(min(start->x - PADDING, goal->x - PADDING), 0);
    right = min(max(start->x + PADDING + 1, goal->x + PADDING + 1), gridSize);
    top = max(min(start->y - PADDING, goal->y - PADDING), 0);
    bottom = min(max(start->y + PADDING + 1, goal->y + PADDING + 1), gridSize);

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

BattlefieldCell* AgentManager::getCellFromGhost(int BattlefieldCellX, int BattlefieldCellY)
{
    if (BattlefieldCellX >= left && BattlefieldCellX < right && BattlefieldCellY >= top && BattlefieldCellY < bottom)
        return GhostGrid[BattlefieldCellY - top][BattlefieldCellX - left];
    return nullptr;
}

bool checkInList2(BattlefieldCell* cell, std::vector<BattlefieldCell*>* list)
{
    for (int i = 0; i < list->size(); i++)
    {
        if (cell == list->at(i))
            return true;
    }
    return false;
}

void AgentManager::printGhostGrid()
{
    std::cout << "\n\n\n";
    std::vector<BattlefieldCell*>* path = getPath();
    for (int i = 0; i < GhostGrid.size(); i++)
    {
        for (int j = 0; j < GhostGrid[0].size(); j++)
            std::cout << "--";
        std::cout << "-\n";

        for (int j = 0; j < GhostGrid[0].size(); j++)
        {
            std::cout << "|";
            if (checkInList2(GhostGrid[i][j], path))
                std::cout << "#";
            else
                std::cout << " ";
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < GhostGrid[0].size(); j++)
        std::cout << "--";
    std::cout << "-\n";


    /* HSCORE Printing
    std::cout << "\n\n\n";
    for (int i = 0; i < GhostGrid.size(); i++)
    {
        for (int j = 0; j < GhostGrid[0].size(); j++)
            std::cout << "--";
        std::cout << "-\n";

        for (int j = 0; j < GhostGrid[0].size(); j++)
        {
            std::cout << "|";
            std::cout << GhostGrid[i][j]->hScore << "\t";
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < GhostGrid[0].size(); j++)
        std::cout << "--";
    std::cout << "-\n";
    */
}

void AgentManager::printPathGrid(GameState* state)
{
    std::cout << "\n\n\n";
    std::vector<BattlefieldCell*>* path = getPath();
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            std::cout << "--";
        std::cout << "-\n";

        for (int j = 0; j < 16; j++)
        {
            std::cout << "|";
            if (checkInList2(state->quadTree->getCell(state->quadTree, j * 100, i * 100, 4), path))
                std::cout << "#";
            else
                std::cout << " ";
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < 16; j++)
        std::cout << "--";
    std::cout << "-\n";
}