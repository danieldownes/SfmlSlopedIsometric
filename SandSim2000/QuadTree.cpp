#include "QuadTree.h"

QuadTree::QuadTree(const sf::FloatRect& rect, const unsigned int& depth)
    : depth(depth), quadRect(rect) {
}

QuadTreeInternal::QuadTreeInternal(const sf::FloatRect& rect, const unsigned int& depth)
    : QuadTree(rect, depth), children{ nullptr, nullptr, nullptr, nullptr } {
}

QuadTreeInternal::~QuadTreeInternal() {
    for (QuadTree* child : children)
        delete[] child;
    delete this;
}

std::vector<Agent*> QuadTreeInternal::getAgents() const {
    std::vector<Agent*> agents;
    for (QuadTree* child : children) {
        std::vector<Agent*> childAgents = child->getAgents();
        agents.insert(agents.end(), childAgents.begin(), childAgents.end());
    }
    return agents;
}

std::array<QuadTree*, 4> QuadTreeInternal::createChildren(std::array<bool, 4> childldrenIsLeaf) {
    float posX = quadRect.getPosition().x;
    float posY = quadRect.getPosition().y;

    float newSizeX = quadRect.getSize().x / 2;
    float newSizeY = quadRect.getSize().y / 2;

    if (childldrenIsLeaf[0]) children[0] = new QuadTreeLeaf(sf::FloatRect(posX, posY, newSizeX, newSizeY), depth + 1);
    else                     children[0] = new QuadTreeInternal(sf::FloatRect(posX, posY, newSizeX, newSizeY), depth + 1);
    if (childldrenIsLeaf[1]) children[1] = new QuadTreeLeaf(sf::FloatRect(posX + newSizeX, posY, newSizeX, newSizeY), depth + 1);
    else                     children[1] = new QuadTreeInternal(sf::FloatRect(posX + newSizeX, posY, newSizeX, newSizeY), depth + 1);
    if (childldrenIsLeaf[2]) children[2] = new QuadTreeLeaf(sf::FloatRect(posX, posY + newSizeY, newSizeX, newSizeY), depth + 1);
    else                     children[2] = new QuadTreeInternal(sf::FloatRect(posX, posY + newSizeY, newSizeX, newSizeY), depth + 1);
    if (childldrenIsLeaf[3]) children[3] = new QuadTreeLeaf(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), depth + 1);
    else                     children[3] = new QuadTreeInternal(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), depth + 1);

    return children;
}

std::array<QuadTree*, 4> QuadTreeInternal::createChildren(std::array<TerrainTile*, 4> childrenTerrain) {
    float posX = quadRect.getPosition().x;
    float posY = quadRect.getPosition().y;

    float newSizeX = quadRect.getSize().x / 2;
    float newSizeY = quadRect.getSize().y / 2;

    if (childrenTerrain[0] != nullptr) children[0] = new QuadTreeLeaf(sf::FloatRect(posX, posY, newSizeX, newSizeY), depth + 1, *childrenTerrain[0]);
    else                               children[0] = new QuadTreeInternal(sf::FloatRect(posX, posY, newSizeX, newSizeY), depth + 1);
    if (childrenTerrain[1] != nullptr) children[1] = new QuadTreeLeaf(sf::FloatRect(posX + newSizeX, posY, newSizeX, newSizeY), depth + 1, *childrenTerrain[1]);
    else                               children[1] = new QuadTreeInternal(sf::FloatRect(posX + newSizeX, posY, newSizeX, newSizeY), depth + 1);
    if (childrenTerrain[2] != nullptr) children[2] = new QuadTreeLeaf(sf::FloatRect(posX, posY + newSizeY, newSizeX, newSizeY), depth + 1, *childrenTerrain[2]);
    else                               children[2] = new QuadTreeInternal(sf::FloatRect(posX, posY + newSizeY, newSizeX, newSizeY), depth + 1);
    if (childrenTerrain[3] != nullptr) children[3] = new QuadTreeLeaf(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), depth + 1, *childrenTerrain[3]);
    else                               children[3] = new QuadTreeInternal(sf::FloatRect(posX + newSizeX, posY + newSizeY, newSizeX, newSizeY), depth + 1);

    return children;
}

//QuadTreeLeaf with random height terrain and possible agent
QuadTreeLeaf::QuadTreeLeaf(const sf::FloatRect& rect, const unsigned int& depth)
    : QuadTreeLeaf(rect, depth, (TerrainTile)[]() {
    TerrainTile randTerrain;
    randTerrain.z = 1;
    randTerrain.height = rand() % 3;
    randTerrain.facing = 0.0f;
    randTerrain.terrain = "default";
    return randTerrain;
        } ())
{}

//QuadTreeLeaf with its passed terrain and possible agent
QuadTreeLeaf::QuadTreeLeaf(const sf::FloatRect& rect, const unsigned int& depth, TerrainTile terrain) 
    : QuadTree(rect, depth), terrainInfo(terrain) {
    //TEMP: Randomly spawn some agents
    if (rand() % 100 < 1)
        agents.push_back(new Agent());
}

QuadTreeLeaf::~QuadTreeLeaf() {
    delete this;
}