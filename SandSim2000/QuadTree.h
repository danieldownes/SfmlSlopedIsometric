#pragma once
#include <array>
#include <vector>
#include <iostream>
#include "SFML/Graphics/Rect.hpp"
#include "TerrainTile.h"
#include "Agent.h"

class QuadTree {
public:
    QuadTree(const sf::FloatRect& rect, const unsigned int& depth);

    virtual std::vector<Agent*> getAgents() const = 0;

    unsigned int getDepth() const { return depth; }
    sf::FloatRect getQuadRect() const { return quadRect; }
protected:
    unsigned int depth;
    sf::FloatRect quadRect;
};

class QuadTreeInternal : public QuadTree {
public:
    QuadTreeInternal(const sf::FloatRect& rect, const unsigned int& depth);
    ~QuadTreeInternal();

    std::vector<Agent*> getAgents() const override;

    std::array<QuadTree*, 4> createChildren(std::array<bool, 4> childldrenIsLeaf);
    std::array<QuadTree*, 4> createChildren(std::array<TerrainTile*, 4> childrenTerrain);
    std::array<QuadTree*, 4> createChildren() { return createChildren({ nullptr, nullptr, nullptr, nullptr }); }

    std::array<QuadTree*, 4> getChildren() const { return children; }
private:
    std::array<QuadTree*, 4> children;
};

class QuadTreeLeaf : public QuadTree {
public:
    QuadTreeLeaf(const sf::FloatRect& rect, const unsigned int& depth, TerrainTile terrain);
    QuadTreeLeaf(const sf::FloatRect& rect, const unsigned int& depth);
    ~QuadTreeLeaf();

    void setTerrainInfo(const TerrainTile terrain) { terrainInfo = terrain; }

    TerrainTile getTerrainInfo() const { return terrainInfo; }
    std::vector<Agent*> getAgents() const override { return agents; }
private:
    TerrainTile terrainInfo;
    std::vector<Agent*> agents;
};